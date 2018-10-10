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
}

void Game::initGame(bool* debug)
{
	//Hook from main for debug features
	debugFeatures = debug;

	//Init timer
	updateTimer = new Timer();

	//Once Scene class is in this is where i'd load in the scene and create everything
	{
		scene = new Scene("./Resources/Scenes/TestSave");
		scene->Load(player, enemies, environments, lights);
	}

	//Camera init stuff
	{
		camera = new Camera();
		camera->perspective(70.f, 800.f / 600.f, 0.001f, 1000.f);
		camera->setPos(glm::vec3(0.f, 0.f, 3.0f));
	}

	//Pure White Shader
	lampShader = new Shader("./Resources/Shaders/lampShader");

	//Shader init stuff
	shaders.push_back(new Shader("./Resources/Shaders/basicShader"));
	{
		shaders.at(shaders.size() - 1)->bind();
		shaders.at(shaders.size() - 1)->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		shaders.at(shaders.size() - 1)->setVec3("viewPosition", camera->getPos().x, camera->getPos().y, camera->getPos().z);
		shaders.at(shaders.size() - 1)->setVec3("light.position", 0.f, 1.f, 1.f);
		shaders.at(shaders.size() - 1)->setVec3("light.color", 0.0f, 1.0f, 0.0f);
		shaders.at(shaders.size() - 1)->setVec3("light.ambience", 0.5f, 0.5f, 0.5f);
		shaders.at(shaders.size() - 1)->setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
		shaders.at(shaders.size() - 1)->setVec3("light.specular", 1.f, 1.f, 1.f);
		shaders.at(shaders.size() - 1)->setFloat("light.constant", 1.0f);
		shaders.at(shaders.size() - 1)->setFloat("light.linear", 0.09f);
		shaders.at(shaders.size() - 1)->setFloat("light.quadratic", 0.032f);
		shaders.at(shaders.size() - 1)->setFloat("material.shininess", 32.0f);
	}

	if (shaders.size() > 0)
		shaderHook = shaders.at(Interact::GetShaderIndex());
	
	modelHook = enemies;
	std::cout << "You are now in control of the enemies model list.\n\n";
}

void Game::update()
{
	updateTimer->Tick();

	float deltaTime = updateTimer->getElapsedTimeSeconds();
	totalGameTime += deltaTime;

	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->GetTransform()->getRot().y += 1.0f * deltaTime;
		}
	}
}

void Game::draw()
{
	if (enemies.size() > 0) {
		for (int i = 0; i < enemies.size(); i++) {
			shaderHook->bind();
			shaderHook->update(*enemies[i]->GetTransform(), *camera);
			enemies[i]->Draw(shaderHook);
		}
	}
	if (environments.size() > 0) {
		for (int i = 0; i < environments.size(); i++) {
			shaderHook->bind();
			shaderHook->update(*environments[i]->GetTransform(), *camera);
			environments[i]->Draw(shaderHook);
		}
	}
	if (lights.size() > 0) {
		for (int i = 0; i < lights.size(); i++) {
			//Light sources wouldn't be affected by other lights
			lampShader->bind();
			lampShader->update(*lights[i]->GetTransform(), *camera);
			lights[i]->Draw(lampShader);
		}
	}
}

void Game::keyboardUp()
{
	//I can't even think of anything to put here tbh I never use keyboard up tbh
}

void Game::keyboardDown()
{
	if (Input::GetKey(KeyCode::Alt)) {
		if (Input::GetKeyPress(KeyCode::L)) {
			delete scene;
			scene = new Scene("./Resources/Scenes/lmao");
			scene->Load(player, enemies, environments, lights);
		}
	}
}

void Game::keyboardPress()
{
	
}
