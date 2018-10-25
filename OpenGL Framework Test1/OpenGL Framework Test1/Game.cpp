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

	
	#pragma region Scene Init Stuff
		enemies.push_back(new Model());
		enemies[0]->LoadFromFile("./Resources/Objects/Monkey/", "Monkey");
		//enemies[0]->GetTransform()->SetPos(glm::vec3(0.f, -0.5f, 2.f));
		//enemies[0]->GetTransform()->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

		lights.push_back(new Model());
		lights[0]->LoadFromFile("./Resources/Objects/Lamp/", "Lamp");
		lights[0]->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
#pragma endregion

	#pragma region Camera init stuff
		camera = new Camera();
		camera->Perspective(70.f, 800.f / 600.f, 0.001f, 1000.f);
		camera->SetPos(glm::vec3(0.f, 0.f, 5.0f));
#pragma endregion

	#pragma region Normal Shaders
		//Init the default shader
		Shader::InitDefault();

		//Pure White Shader
		lampShader = new Shader(
			"./Resources/Shaders/BasicPass.vert",
			"./Resources/Shaders/BasicPass.frag"
		);

		//Shader init stuff
		shaders.push_back(new Shader(
			"./Resources/Shaders/StaticGeometry.vert",
			"./Resources/Shaders/Phong.frag"
		));
#pragma endregion

	#pragma region Post processing Shaders
		postProcShaders.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/PostProcess/GreyScalePost.frag"
		));
		postProcShaders.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/PostProcess/SepiaPost.frag"
		));
		postProcShaders.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/PostProcess/FocusIn.frag"
		));
#pragma endregion
	
	InitUniforms();

	#pragma region Bloom stuffs
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/Bloom/BloomHighPass.frag"
		));
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/Bloom/BlurVertical.frag"
		));
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/Bloom/BlurHorizontal.frag"
		));
		bloomComponents.push_back(new Shader(
			"./Resources/Shaders/PassThrough.vert",
			"./Resources/Shaders/Bloom/BloomComposite.frag"
		));
#pragma endregion

	#pragma region FrameBuffers
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
#pragma endregion

	#pragma region Hooks for shaders and models
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
#pragma endregion
}

void Game::InitUniforms()
{
	postProcShaders.at(FOCUS_IN_POST)->Bind();
	postProcShaders.at(FOCUS_IN_POST)->SendUniform("windowWidth", static_cast<float>(WINDOW_WIDTH));
	postProcShaders.at(FOCUS_IN_POST)->SendUniform("windowHeight", static_cast<float>(WINDOW_HEIGHT));
	Shader::Unbind();
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

	shaders.at(PHONG_SHADER)->Bind();
	shaders.at(PHONG_SHADER)->SendUniform("light.position", glm::vec4(lights[0]->GetTransform()->GetPos(), 1.0f));
	Shader::Unbind();

	postProcShaders.at(FOCUS_IN_POST)->Bind();
	postProcShaders.at(FOCUS_IN_POST)->SendUniform("uTime", totalGameTime);
	Shader::Unbind();

	lights[0]->GetTransform()->SetPos(glm::vec3(glm::sin(updateTimer->GetTimeCurrent() / 1000.f) * 5.0f, 1.0f, 1.3f));
}

void Game::Draw()
{
	/// Clear Buffers ///
	mainBuffer.Clear();
	workBuffer1.Clear();
	workBuffer2.Clear();

	shaderHook = shaders.at(Interact::GetShaderIndex());
	postProcShaderHook = postProcShaders.at(postProcShaderIndex);

	shaderHook->Bind();
	shaderHook->Update(*camera);
	Shader::Unbind();
	lampShader->Bind();
	lampShader->Update(*camera);
	Shader::Unbind();

	//Camera 1
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		if (frameBuffer) {
			mainBuffer.Bind();
		}
		if (enemies.size() > 0) {
			for (int i = 0; i < enemies.size(); i++) {
				shaderHook->Bind();
				shaderHook->SendUniform("uModel", enemies[i]->GetTransform()->GetModel());
				enemies[i]->Draw(shaderHook);
				Shader::Unbind();
			}
		}
		if (environments.size() > 0) {
			for (int i = 0; i < environments.size(); i++) {
				shaderHook->Bind();
				shaderHook->SendUniform("uModel", environments[i]->GetTransform()->GetModel());
				environments[i]->Draw(shaderHook);
				Shader::Unbind();
			}
		}
		if (lights.size() > 0) {
			for (int i = 0; i < lights.size(); i++) {
				glEnable(GL_BLEND);
				//Light sources wouldn't be affected by other lights
				lampShader->Bind();
				lampShader->SendUniform("uModel", lights[i]->GetTransform()->GetModel());
				lights[i]->Draw(lampShader);
				glDisable(GL_BLEND);
				Shader::Unbind();
			}
		}
		mainBuffer.Unbind();

		if (frameBuffer) {
			ProcessFramebufferStuff(mainBuffer, workBuffer1, workBuffer2, workBuffer3, 
										bloomComponents, *postProcShaderHook, postProc, hasBloom);
		}
	}

	//Working for 4 viewports, just doesn't work as great with current framebuffer stuff as it'll draw
	//Smaller and smaller versions and triple the amounts on screen, I can fix it, but idk if it's worth it
	{
		////Camera 2
		//{
		//	glViewport(0, 0, WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

		//	if (frameBuffer) {
		//		mainBuffer.Bind();
		//	}
		//	if (enemies.size() > 0) {
		//		for (int i = 0; i < enemies.size(); i++) {
		//			shaderHook->Bind();
		//			shaderHook->Update(*enemies[i]->GetTransform(), *camera);
		//			enemies[i]->Draw(shaderHook);
		//			shaderHook->Unbind();

		//		}
		//	}
		//	if (environments.size() > 0) {
		//		for (int i = 0; i < environments.size(); i++) {
		//			shaderHook->Bind();
		//			shaderHook->Update(*environments[i]->GetTransform(), *camera);
		//			environments[i]->Draw(shaderHook);
		//			shaderHook->Unbind();
		//		}
		//	}
		//	if (lights.size() > 0) {
		//		for (int i = 0; i < lights.size(); i++) {
		//			glEnable(GL_BLEND);
		//			//Light sources wouldn't be affected by other lights
		//			lampShader->Bind();
		//			lampShader->Update(*lights[i]->GetTransform(), *camera);
		//			lights[i]->Draw(lampShader);
		//			glDisable(GL_BLEND);
		//			lampShader->Unbind();
		//		}
		//	}
		//	mainBuffer.Unbind();
		//	if (frameBuffer) {
		//		if (hasBloom) {
		//			ProcessBloom(mainBuffer, workBuffer1, workBuffer2, workBuffer3, bloomComponents, postProc);
		//		}
		//		if (postProc) {
		//			FrameBuffer* temp;
		//			if (hasBloom) {
		//				temp = &workBuffer3;
		//			}
		//			else {
		//				temp = &mainBuffer;
		//			}
		//			postProcShaderHook->Bind();
		//			postProcShaderHook->SetInt("uTex", 0);

		//			glBindTexture(GL_TEXTURE_2D, temp->GetColorHandle(0));
		//			DrawFullScreenQuad();
		//			glBindTexture(GL_TEXTURE_2D, GL_NONE);

		//			postProcShaderHook->Unbind();
		//		}
		//	}
		//}

		////Camera 3
		//{
		//	glViewport(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

		//	if (frameBuffer) {
		//		mainBuffer.Bind();
		//	}
		//	if (enemies.size() > 0) {
		//		for (int i = 0; i < enemies.size(); i++) {
		//			shaderHook->Bind();
		//			shaderHook->Update(*enemies[i]->GetTransform(), *camera);
		//			enemies[i]->Draw(shaderHook);
		//			shaderHook->Unbind();

		//		}
		//	}
		//	if (environments.size() > 0) {
		//		for (int i = 0; i < environments.size(); i++) {
		//			shaderHook->Bind();
		//			shaderHook->Update(*environments[i]->GetTransform(), *camera);
		//			environments[i]->Draw(shaderHook);
		//			shaderHook->Unbind();
		//		}
		//	}
		//	if (lights.size() > 0) {
		//		for (int i = 0; i < lights.size(); i++) {
		//			glEnable(GL_BLEND);
		//			//Light sources wouldn't be affected by other lights
		//			lampShader->Bind();
		//			lampShader->Update(*lights[i]->GetTransform(), *camera);
		//			lights[i]->Draw(lampShader);
		//			glDisable(GL_BLEND);
		//			lampShader->Unbind();
		//		}
		//	}
		//	mainBuffer.Unbind();
		//	if (frameBuffer) {
		//		if (hasBloom) {
		//			ProcessBloom(mainBuffer, workBuffer1, workBuffer2, workBuffer3, bloomComponents, postProc);
		//		}
		//		if (postProc) {
		//			FrameBuffer* temp;
		//			if (hasBloom) {
		//				temp = &workBuffer3;
		//			}
		//			else {
		//				temp = &mainBuffer;
		//			}
		//			postProcShaderHook->Bind();
		//			postProcShaderHook->SetInt("uTex", 0);

		//			glBindTexture(GL_TEXTURE_2D, temp->GetColorHandle(0));
		//			DrawFullScreenQuad();
		//			glBindTexture(GL_TEXTURE_2D, GL_NONE);

		//			postProcShaderHook->Unbind();
		//		}
		//	}
		//}

		////Camera 4
		//{
		//	glViewport(WINDOW_WIDTH / 2.f, 0, WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);

		//	if (frameBuffer) {
		//		mainBuffer.Bind();
		//	}
		//	if (enemies.size() > 0) {
		//		for (int i = 0; i < enemies.size(); i++) {
		//			shaderHook->Bind();
		//			shaderHook->Update(*enemies[i]->GetTransform(), *camera);
		//			enemies[i]->Draw(shaderHook);
		//			shaderHook->Unbind();

		//		}
		//	}
		//	if (environments.size() > 0) {
		//		for (int i = 0; i < environments.size(); i++) {
		//			shaderHook->Bind();
		//			shaderHook->Update(*environments[i]->GetTransform(), *camera);
		//			environments[i]->Draw(shaderHook);
		//			shaderHook->Unbind();
		//		}
		//	}
		//	if (lights.size() > 0) {
		//		for (int i = 0; i < lights.size(); i++) {
		//			glEnable(GL_BLEND);
		//			//Light sources wouldn't be affected by other lights
		//			lampShader->Bind();
		//			lampShader->Update(*lights[i]->GetTransform(), *camera);
		//			lights[i]->Draw(lampShader);
		//			glDisable(GL_BLEND);
		//			lampShader->Unbind();
		//		}
		//	}
		//	mainBuffer.Unbind();
		//	if (frameBuffer) {
		//		if (hasBloom) {
		//			ProcessBloom(mainBuffer, workBuffer1, workBuffer2, workBuffer3, bloomComponents, postProc);
		//		}
		//		if (postProc) {
		//			FrameBuffer* temp;
		//			if (hasBloom) {
		//				temp = &workBuffer3;
		//			}
		//			else {
		//				temp = &mainBuffer;
		//			}
		//			postProcShaderHook->Bind();
		//			postProcShaderHook->SetInt("uTex", 0);

		//			glBindTexture(GL_TEXTURE_2D, temp->GetColorHandle(0));
		//			DrawFullScreenQuad();
		//			glBindTexture(GL_TEXTURE_2D, GL_NONE);

		//			postProcShaderHook->Unbind();
		//		}
		//	}
		//}
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
	if (!Input::GetKey(KeyCode::Alt)) {
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
	}
	if (*debugFeatures) {
		if (postProc) {
			if (Input::GetKeyPress(KeyCode::PageUp)) {
				postProcShaderIndex = indexWrap(postProcShaderIndex, 1, postProcShaders.size());
				std::cout << "You are now using post processing shader" << postProcShaderIndex << "\n\n";
			}
		}
		if (Input::GetKeyPress(KeyCode::F1)) {
			postProc = !postProc;
			std::cout << "Post Processing effects are now ";
			postProc ? std::cout << "enabled\n\n" : std::cout << "disabled\n\n";

			if (!postProc && !hasBloom) {
				frameBuffer = false;
			}
			else {
				frameBuffer = true;
			}
		}
		if (Input::GetKeyPress(KeyCode::F2)) {
			//toggles bloom usage
			hasBloom = !hasBloom;
			std::cout << "Bloom effect is now ";
			hasBloom ? std::cout << "enabled\n\n" : std::cout << "disabled\n\n";

			if (!hasBloom && !postProc) {
				frameBuffer = false;
			}
			else {
				frameBuffer = true;
			}
		}
		if (Input::GetKeyPress(KeyCode::F5)) {
			for (int i = 0; i < shaders.size(); i++) {
				shaders[i]->Reload();
			}
			for (int i = 0; i < postProcShaders.size(); i++) {
				postProcShaders[i]->Reload();
			}
			for (int i = 0; i < bloomComponents.size(); i++) {
				bloomComponents[i]->Reload();
			}
			InitUniforms();
		}
	}
}
