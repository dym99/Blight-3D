#include "Game.h"
#include <iostream>

int indexWrap(int cur, int incr, int max) {
	return ((cur + incr) % max);
}


Game::Game() :
	mainBuffer(1), workBuffer1(1), workBuffer2(1), workBuffer3(1)
{}

Game::~Game()
{
	delete updateTimer;
	
	//Handle the models
	{
		delete player;
		for (int i = 0; i < enemies.size(); i++) {
			delete enemies[i];
		}
		for (int i = 0; i < environments.size(); i++) {
			delete environments[i];
		}
		for (int i = 0; i < lights.size(); i++) {
			delete lights[i];
		}
	}

	//Handle shaders
	{
		delete lampShader;
		for (int i = 0; i < shaders.size(); i++) {
			delete shaders[i];
		}
		for (int i = 0; i < postProcShaders.size(); i++) {
			delete postProcShaders[i];
		}
		for (int i = 0; i < bloomComponents.size(); i++) {
			delete bloomComponents[i];
		}
	}

	//Handle camera
	delete camera;
}

void Game::InitGame(bool* debug)
{
	//Hook from main for debug features
	debugFeatures = debug;

	//Inits the full screen quad for the framebuffer
	InitFullScreenQuad();

	//Init timer
	updateTimer = new Timer();

	//Init Scene stuffs
	{
		enemies.push_back(new Model());
		enemies[0]->LoadFromFile("./Resources/Objects/Monkey/", "Monkey");
		//enemies[0]->GetTransform()->SetPos(glm::vec3(0.f, -0.5f, 2.f));
		//enemies[0]->GetTransform()->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	}

	//Camera init stuff
	{
		camera = new Camera();
		camera->Perspective(70.f, 800.f / 600.f, 0.001f, 1000.f);
		camera->SetPos(glm::vec3(0.f, 0.f, 5.0f));
	}

	//Normal Shaders
	{
		//Pure White Shader
		lampShader = new Shader("./Resources/Shaders/BasicPass");

		//Shader init stuff
		shaders.push_back(new Shader(
			"./Resources/Shaders/StaticGeometry",
			"./Resources/Shaders/Phong"
		));
		{
			shaders.at(shaders.size() - 1)->Bind();
			shaders.at(shaders.size() - 1)->SetVec4("light.position", glm::vec4(3.0f, 0.f, 0.f, 1.0f));
			shaders.at(shaders.size() - 1)->SetVec3("light.ambience", 0.15f, 0.15f, 0.15f);
			shaders.at(shaders.size() - 1)->SetVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
			shaders.at(shaders.size() - 1)->SetVec3("light.specular", 0.8f, 0.8f, 0.8f);
			shaders.at(shaders.size() - 1)->SetFloat("light.constant", 1.0f);
			shaders.at(shaders.size() - 1)->SetFloat("light.linear", 0.1f);
			shaders.at(shaders.size() - 1)->SetFloat("light.quadratic", 0.01f);
			shaders.at(shaders.size() - 1)->SetFloat("light.shininess", 50.0f);
		}	
	}

	//Post processing Shaders
	{
		postProcShaders.push_back(new Shader(
			"./Resources/Shaders/PassThrough",
			"./Resources/Shaders/PostProcess/GreyScalePost"
		));
		postProcShaders.push_back(new Shader(
			"./Resources/Shaders/PassThrough",
			"./Resources/Shaders/PostProcess/SepiaPost"
		));
	}
	
	//Bloom stuffs
	{
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough",
			"./Resources/Shaders/Bloom/BloomHighPass"
		));
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough",
			"./Resources/Shaders/Bloom/BlurVertical"
		));
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough",
			"./Resources/Shaders/Bloom/BlurHorizontal"
		));
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough",
			"./Resources/Shaders/Bloom/BloomComposite"
		));
	}

	//FrameBuffers
	{
		mainBuffer.InitDepthTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
		mainBuffer.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

		if (!mainBuffer.CheckFBO()) {
			std::cout << "FBO1 failed to load.\n\n";
			system("pause");
			exit(0);
		}

		workBuffer1.InitColorTexture(0, WINDOW_WIDTH / BLOOM_DOWNSCALE, WINDOW_HEIGHT / BLOOM_DOWNSCALE, 
										GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE);

		if (!workBuffer1.CheckFBO()) {
			std::cout << "FBO2 failed to load.\n\n";
			system("pause");
			exit(0);
		}

		workBuffer2.InitColorTexture(0, WINDOW_WIDTH / BLOOM_DOWNSCALE, WINDOW_HEIGHT / BLOOM_DOWNSCALE, 
										GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE);

		if (!workBuffer2.CheckFBO()) {
			std::cout << "FBO3 failed to load.\n\n";
			system("pause");
			exit(0);
		}

		workBuffer3.InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

		if (!workBuffer3.CheckFBO()) {
			std::cout << "FBO4 Failed to load.\n\n";
			system("pause");
			exit(0);
		}
	}

	//Hooks for shaders and models
	{
		if (shaders.size() > 0)
			shaderHook = shaders.at(Interact::GetShaderIndex());

		if (postProcShaders.size() > 0)
			postProcShaderHook = shaders.at(postProcShaderIndex);

		if (enemies.size() > 0) {
			modelHook = enemies;
			std::cout << "You are now in control of the enemies model list.\n\n";
		}
		else if (environments.size() > 0) {
			modelHook = environments;
			std::cout << "You are now in control of the environment model list.\n\n";
		}
		else if (lights.size() > 0) {
			modelHook = lights;
			std::cout << "You are now in control of the lights model list.\n\n";
		}
	}
}

void Game::Update()
{
	updateTimer->Tick();

	float deltaTime = updateTimer->GetElapsedTimeSeconds();
	totalGameTime += deltaTime;

	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->GetTransform()->GetRot().y += 1.0f * deltaTime;
		}
	}
}

void Game::Draw()
{
	/// Clear Buffers ///
	mainBuffer.Clear();
	workBuffer1.Clear();
	workBuffer2.Clear();

	shaderHook = shaders.at(Interact::GetShaderIndex());
	postProcShaderHook = postProcShaders.at(postProcShaderIndex);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (frameBuffer) {
		mainBuffer.Bind();
	}
	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			shaderHook->Bind();
			shaderHook->Update(*enemies[i]->GetTransform(), *camera);
			enemies[i]->Draw(shaderHook);
			shaderHook->Unbind();
			
		}
	}
	if (environments.size() > 0) {
		for (int i = 0; i < environments.size(); i++) {
			shaderHook->Bind();
			shaderHook->Update(*environments[i]->GetTransform(), *camera);
			environments[i]->Draw(shaderHook);
			shaderHook->Unbind();
		}
	}
	if (lights.size() > 0) {
		for (int i = 0; i < lights.size(); i++) {
			glEnable(GL_BLEND);
			//Light sources wouldn't be affected by other lights
			lampShader->Bind();
			lampShader->Update(*lights[i]->GetTransform(), *camera);
			lights[i]->Draw(lampShader);
			glDisable(GL_BLEND);
			lampShader->Unbind();
		}
	}
	mainBuffer.Unbind();
	if (frameBuffer) {
		if (hasBloom) {
			ProcessBloom(mainBuffer, workBuffer1, workBuffer2, workBuffer3, bloomComponents, postProc);
		}
		if (postProc) {
			FrameBuffer* temp;
			if (hasBloom) {
				temp = &workBuffer3;
			}
			else {
				temp = &mainBuffer;
			}
			postProcShaderHook->Bind();
			postProcShaderHook->SetInt("uTex", 0);

			glBindTexture(GL_TEXTURE_2D, temp->GetColorHandle(0));
			DrawFullScreenQuad();
			glBindTexture(GL_TEXTURE_2D, GL_NONE);

			postProcShaderHook->Unbind();
		}
	}
}

void Game::KeyboardUp()
{
	//I can't even think of anything to put here tbh I never use keyboard up tbh
}

void Game::KeyboardDown()
{
	if (Input::GetKeyPress(KeyCode::Q)) {
		exit(0);
	}
}

void Game::KeyboardPress()
{
	if (Input::GetKeyPress(KeyCode::Insert)) {
		*debugFeatures = !*debugFeatures;
		std::cout << "Debug features are now ";
		*debugFeatures ? std::cout << "enabled\n\n" : std::cout << "disabled\n\n";
	}
	if (Input::GetKeyPress(KeyCode::Tab)) {
		if (modelHook == enemies) {
			if (environments.size() > 0) {
				modelHook = environments;
				std::cout << "Environments control\n\n";
			}
			else if (lights.size() > 0) {
				modelHook = lights;
				std::cout << "Lights control\n\n";
			}
			else {
				std::cout << "Unable to switch, Enemy Control\n\n";
			}
		}
		else if (modelHook == environments) {
			if (lights.size() > 0) {
				modelHook = lights;
				std::cout << "Lights control\n\n";
			}
			else if (enemies.size() > 0) {
				modelHook = enemies;
				std::cout << "Enemy control\n\n";
			}
			else {
				std::cout << "Unable to switch, Environments Control\n\n";
			}
		}
		else if (modelHook == lights) {
			if (enemies.size() > 0) {
				modelHook = enemies;
				std::cout << "Enemy control\n\n";
			}
			else if (environments.size() > 0) {
				modelHook = environments;
				std::cout << "Environments control\n\n";
			}
			else {
				std::cout << "Unable to switch, Lights Control\n\n";
			}
		}
	}
	if (*debugFeatures) {
		if (Input::GetKeyPress(KeyCode::PageUp)) {
			postProcShaderIndex = indexWrap(postProcShaderIndex, 1, postProcShaders.size());
			std::cout << "You are now using post processing shader" << postProcShaderIndex << "\n\n";
		}
		if (Input::GetKeyPress(KeyCode::F1)) {
			postProc = !postProc;
			std::cout << "Post Processing effects are now ";
			postProc ? std::cout << "enabled\n\n" : std::cout << "disabled\n\n";

			if (!hasBloom && !postProc) {
				//toggles framebuffer usage
				frameBuffer = false;
				std::cout << "Your frame buffer is now disabled\n\n";
			}
			else {
				frameBuffer = true;
				std::cout << "Your frame buffer is now enabled\n\n";
			}
		}
		if (Input::GetKeyPress(KeyCode::F2)) {
			//toggles bloom usage
			hasBloom = !hasBloom;
			std::cout << "Bloom effect is now ";
			hasBloom ? std::cout << "enabled\n\n" : std::cout << "disabled\n\n";

			if (!hasBloom && !postProc) {
				//toggles framebuffer usage
				frameBuffer = false;
				std::cout << "Your frame buffer is now disabled\n\n";
			}
			else {
				frameBuffer = true;
				std::cout << "Your frame buffer is now enabled\n\n";
			}
		}
	}
}
