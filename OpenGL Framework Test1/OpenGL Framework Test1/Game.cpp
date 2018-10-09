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
		scene = new Scene("./Resources/Scenes/TestNewSaveScene");
		scene->Load(player, enemies, environments, lights);
		/*player = new Model();
		//player->LoadFromFile(scene->getPlayerPath(), scene->getPlayerName());
		//player->GetTransform()->setPos(scene->getPlayerPosition());
		//player->GetTransform()->setRot(scene->getPlayerRotation());
		//player->GetTransform()->setScale(scene->getPlayerScale());
		//
		//for (int i = 0; i < scene->getEnemyCount(); i++) {
		//		enemies.push_back(new Model());
		//		enemies.at(i)->LoadFromFile(scene->getEnemyPaths().at(i), scene->getEnemyNames().at(i));
		//		enemies.at(i)->GetTransform()->setPos(scene->getEnemyPositions().at(i));
		//		enemies.at(i)->GetTransform()->setRot(scene->getEnemyRotations().at(i));
		//		enemies.at(i)->GetTransform()->setScale(scene->getEnemyScales().at(i));
		//}
		//for (int i = 0; i < scene->getEnvironmentCount(); i++) {
		//		environments.push_back(new Model());
		//		environments.at(i)->LoadFromFile(scene->getEnvironmentPaths().at(i), scene->getEnvironmentNames().at(i));
		//		environments.at(i)->GetTransform()->setPos(scene->getEnvironmentPositions().at(i));
		//		environments.at(i)->GetTransform()->setRot(scene->getEnvironmentRotations().at(i));
		//		environments.at(i)->GetTransform()->setScale(scene->getEnvironmentScales().at(i));
		//}
		//for (int i = 0; i < scene->getLightCount(); i++) {
		//		lights.push_back(new Model());
		//		lights.at(i)->LoadFromFile(scene->getLightPaths().at(i), scene->getLightNames().at(i));
		//		lights.at(i)->GetTransform()->setPos(scene->getLightPositions().at(i));
		//		lights.at(i)->GetTransform()->setRot(scene->getLightRotations().at(i));
		//		lights.at(i)->GetTransform()->setScale(scene->getLightScales().at(i));
		//}*/
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
		if (Input::GetKeyPress(KeyCode::S)) {
			scene->Save(*player, enemies, environments, lights);
			std::cout << "your scene at '" << scene->getFileName() << ".scn', was saved.\n"
						<< "You may now safely quit the program.\n";
		}
		else if (Input::GetKeyPress(KeyCode::N)) {
			delete scene;
			scene = new Scene(Scene::New(*player, enemies, environments, lights));
			std::cout << "New scene at '" << scene->getFileName() << ".scn', was created.\n"
						<< "All changes made to previously loaded scene have now been saved in this file.\n";
		}
	}
}

void Game::keyboardPress()
{
	if (Input::GetKeyPress(KeyCode::Insert)) {
		*debugFeatures ? std::cout << "Debug Features Disabled\n" : std::cout << "Debug Features Enabled\n";
		*debugFeatures ? *debugFeatures = false : *debugFeatures = true;
	}
	if (Input::GetKeyPress(KeyCode::Enter)) {
		std::cout << "Object: " << modelHook.at(Interact::GetModelIndex())->name << std::to_string(Interact::GetModelIndex()) << '\n';
		std::cout << "Position: " << "( " << modelHook.at(Interact::GetModelIndex())->GetTransform()->getPos().x <<
										" , " << modelHook.at(Interact::GetModelIndex())->GetTransform()->getPos().y <<
											" , " << modelHook.at(Interact::GetModelIndex())->GetTransform()->getPos().z << " )\n\n";
	}
	if (Input::GetKeyPress(KeyCode::Q)) {
		exit(1);
	}
	if (!(Input::GetKey(KeyCode::Alt))) {
		if (Input::GetKeyPress(KeyCode::Tab)) {
			if (modelHook == enemies) {
				std::cout << "You are now in control of the environments model list.\n\n";
					modelHook = environments;
			}
			else if (modelHook == environments) {
				std::cout << "You are now in control of the lights model list.\n\n";
					modelHook = lights;
			}
			else {
				std::cout << "You are now in control of the enemies model list.\n\n";
				modelHook = enemies;
			}
		}
	}
}
