#include "Game.h"
#include <iostream>

Game::Game()  
{}

Game::~Game()
{
	delete updateTimer;
	
	//Handle the models
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

	//Handle shaders
	delete lampShader;
	for (int i = 0; i < shaders.size(); i++) {
		delete shaders[i];
	}

	//Handle scene
	delete scene;

	//Handle camera
	delete camera;

	delete texture;
}

void Game::InitGame(bool* debug)
{
	//Hook from main for debug features
	debugFeatures = debug;

	//Init timer
	updateTimer = new Timer();

	//Once Scene class is in this is where i'd load in the scene and create everything
	/*{
		scene = new Scene("./Resources/Scenes/TestSave");
		scene->Load(player, enemies, environments, lights);
	}*/

	enemies.push_back(new Model());
	enemies[0]->LoadFromFile("./Resources/Objects/Crysis/", "nanosuit");
	enemies[0]->GetTransform()->SetPos(glm::vec3(0.f, 0.f, 0.f));
	enemies[0]->GetTransform()->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

	environments.push_back(new Model());
	environments[0]->LoadFromFile("./Resources/Objects/Ground/", "Ground");
	environments[0]->GetTransform()->SetPos(glm::vec3(0.f, -0.5f, 0.f));
	environments[0]->GetTransform()->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	lights.push_back(new Model());
	lights[0]->LoadFromFile("./Resources/Objects/Lamp/", "lamp");
	lights[0]->GetTransform()->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	lights[0]->GetTransform()->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));

	//Camera init stuff
	{
		camera = new Camera();
		camera->Perspective(70.f, 800.f / 600.f, 0.001f, 1000.f);
		camera->SetPos(glm::vec3(0.f, 0.f, 3.0f));
	}

	//Pure White Shader
	lampShader = new Shader("./Resources/Shaders/lampShader");

	//Shader init stuff
	shaders.push_back(new Shader("./Resources/Shaders/basicShader", "./Resources/Shaders/normalMap"));
	shaders.at(shaders.size() - 1)->setOptionalMessage("You are now viewing Model Normal Maps\n");
	shaders.push_back(new Shader("./Resources/Shaders/basicShader", "./Resources/Shaders/specularMap"));
	shaders.at(shaders.size() - 1)->setOptionalMessage("You are now viewing Model Specular Maps\n");
	shaders.push_back(new Shader("./Resources/Shaders/basicShader", "./Resources/Shaders/diffuseMap"));
	shaders.at(shaders.size() - 1)->setOptionalMessage("You are now viewing Model Diffuse Maps\n");
	//shaders.push_back(new Shader("./Resources/Shaders/basicShader", "./Resources/Shaders/norSpecMap"));
	//shaders.at(shaders.size() - 1)->setOptionalMessage("You are now viewing Model Normal and Specular Maps\n");
	//shaders.push_back(new Shader("./Resources/Shaders/basicShader", "./Resources/Shaders/difNorMap"));
	//shaders.at(shaders.size() - 1)->setOptionalMessage("You are now viewing Model Diffuse and Normal Maps\n");
	//shaders.push_back(new Shader("./Resources/Shaders/basicShader"));
	//{
	//	shaders.at(shaders.size() - 1)->Bind();
	//	shaders.at(shaders.size() - 1)->SetVec3("light.position", 1.0f, 1.0f, 1.0f);
	//	shaders.at(shaders.size() - 1)->SetVec3("light.ambience", 0.5f, 0.5f, 0.5f);
	//	shaders.at(shaders.size() - 1)->SetVec3("light.diffuse", 0.25f, 0.25f, 0.25f);
	//	shaders.at(shaders.size() - 1)->SetVec3("light.specular", 0.8f, 0.8f, 0.8f);
	//	shaders.at(shaders.size() - 1)->SetFloat("light.constant", 1.0f);
	//	shaders.at(shaders.size() - 1)->SetFloat("light.linear", 0.09f);
	//	shaders.at(shaders.size() - 1)->SetFloat("light.quadratic", 0.032f);
	//	shaders.at(shaders.size() - 1)->SetFloat("material.shininess", 32.0f);
	//}
	shaders.push_back(new Shader("./Resources/Shaders/passThrough"));
	{
		shaders.at(shaders.size() - 1)->Bind();
		shaders.at(shaders.size() - 1)->SetVec4("light.position", glm::vec4(0.0f, 0.f, 0.f, 1.0f));
		shaders.at(shaders.size() - 1)->SetVec3("light.ambience", 0.15f, 0.15f, 0.15f);
		shaders.at(shaders.size() - 1)->SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		shaders.at(shaders.size() - 1)->SetVec3("light.specular", 0.8f, 0.8f, 0.8f);
		shaders.at(shaders.size() - 1)->SetFloat("light.constant", 1.0f);
		shaders.at(shaders.size() - 1)->SetFloat("light.linear", 0.1f);
		shaders.at(shaders.size() - 1)->SetFloat("light.quadratic", 0.01f);
		shaders.at(shaders.size() - 1)->SetFloat("light.shininess", 50.0f);
	}

	if (shaders.size() > 0)
		shaderHook = shaders.at(Interact::GetShaderIndex());
	
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
	shaderHook = shaders.at(Interact::GetShaderIndex());
	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			shaderHook->Bind();
			shaderHook->Update(*enemies[i]->GetTransform(), *camera);
			enemies[i]->Draw(shaderHook);
		}
	}
	if (environments.size() > 0) {
		for (int i = 0; i < environments.size(); i++) {
			shaderHook->Bind();
			shaderHook->Update(*environments[i]->GetTransform(), *camera);
			environments[i]->Draw(shaderHook);
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
}
