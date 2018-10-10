#define _CRT_SECURE_NO_WARNINGS
#include "Scene.h"
#include <fstream>
#include <iostream>

#define CHAR_BUFFER_SIZE 128

enum ObjTypes {
	PLAYER,
	ENEMY,
	ENVIRONMENT,
	LIGHT
};

Scene::Scene(const std::string & file)
{
	fileName = file;
	ProcessFile(file);
}

Scene::~Scene()
{
}

bool Scene::ProcessFile(const std::string & file)
{
	std::ifstream input;
	input.open(file + ".scn");
	
	if (!input) {
		std::cout << "Scene file failed to open.\n"
					<< "Either it doesn't exist, or you loaded it wrong\n";
		return false;
	}

	char inputString[CHAR_BUFFER_SIZE];

	while (!input.eof()) {
		input.getline(inputString, CHAR_BUFFER_SIZE);

		if (inputString[0] == '#') {
			//This line is a comment
			continue;
		}
		else if (inputString[0] == 'E') {
			if (inputString[1] == 'v') {
				if (inputString[2] == 'p') {
					if (inputString[3] == 'a') {
						//This line is a new Environment object path
						char buf[CHAR_BUFFER_SIZE];

						std::strncpy(buf, &inputString[5], CHAR_BUFFER_SIZE);

						std::string temp = buf;
						
						environmentPaths.push_back(buf);
					}
					else {
						//This line holds environment position data
						glm::vec3 temp;

						std::sscanf(inputString, "Evpo %f %f %f", &temp.x, &temp.y, &temp.z);

						environmentPositions.push_back(temp);
					}
				}
				else if (inputString[2] == 'n') {
					if (inputString[3] == 'a') {
						//This line holds environment name data
						char buf[CHAR_BUFFER_SIZE];

						std::strncpy(buf, &inputString[5], CHAR_BUFFER_SIZE);

						std::string temp = buf;

						environmentNames.push_back(buf);
					}
					else {
						//This line holds environment number data
						unsigned int temp;

						std::sscanf(inputString, "Evn %u", &temp);

						environmentCount = temp;
					}

				}
				else if (inputString[2] == 'r') {
					//This line holds environment rotation data
					glm::vec3 temp;

					std::sscanf(inputString, "Evrt %f %f %f", &temp.x, &temp.y, &temp.z);

					environmentRotations.push_back(temp);
				}
				else if (inputString[2] == 's') {
					//This line holds environment scale data
					glm::vec3 temp;

					std::sscanf(inputString, "Evsc %f %f %f", &temp.x, &temp.y, &temp.z);

					environmentScales.push_back(temp);
				}
			}
			else if (inputString[1] == 'p') {
				if (inputString[2] == 'a') {
					//This line is a new enemy object path
					char buf[CHAR_BUFFER_SIZE];

					std::strncpy(buf, &inputString[4], CHAR_BUFFER_SIZE);

					std::string temp = buf;

					enemyPaths.push_back(buf);
				}
				else {
					//This line holds enemy position data
					glm::vec3 temp;

					std::sscanf(inputString, "Epo %f %f %f", &temp.x, &temp.y, &temp.z);

					enemyPositions.push_back(temp);
				}
			}
			else if (inputString[1] == 'n') {
				if (inputString[2] == 'a') {
					//This line holds enemy name data
					char buf[CHAR_BUFFER_SIZE];

					std::strncpy(buf, &inputString[4], CHAR_BUFFER_SIZE);

					std::string temp = buf;

					enemyNames.push_back(buf);
				}
				else {
					//This line holds enemy number data
					unsigned int temp;

					std::sscanf(inputString, "En %u", &temp);

					enemyCount = temp;
				}
			}
			else if (inputString[1] == 'r') {
				//This line holds enemy rotation data
				glm::vec3 temp;

				std::sscanf(inputString, "Ert %f %f %f", &temp.x, &temp.y, &temp.z);

				enemyRotations.push_back(temp);
			}
			else if (inputString[1] == 's') {
				//This line holds enemy scale data
				glm::vec3 temp;

				std::sscanf(inputString, "Esc %f %f %f", &temp.x, &temp.y, &temp.z);

				enemyScales.push_back(temp);
			}
		}
		else if (inputString[0] == 'L') {
			if (inputString[1] == 'p') {
				if (inputString[2] == 'a') {
					//This line is a new light object path
					char buf[CHAR_BUFFER_SIZE];

					std::strncpy(buf, &inputString[4], CHAR_BUFFER_SIZE);

					std::string temp = buf;

					lightPaths.push_back(buf);
				}
				else {
					//This line holds light position data
					glm::vec3 temp;

					std::sscanf(inputString, "Lpo %f %f %f", &temp.x, &temp.y, &temp.z);

					lightPositions.push_back(temp);
				}
			}
			else if (inputString[1] == 'n') {
				if (inputString[2] == 'a') {
					//This line holds light name data
					char buf[CHAR_BUFFER_SIZE];

					std::strncpy(buf, &inputString[4], CHAR_BUFFER_SIZE);

					std::string temp = buf;

					lightNames.push_back(buf);
				}
				else {
					//This line holds light number data
					unsigned int temp;

					std::sscanf(inputString, "Ln %u", &temp);

					lightCount = temp;
				}
			}
			else if (inputString[1] == 'r') {
				//This line holds light rotation data
				glm::vec3 temp;

				std::sscanf(inputString, "Lrt %f %f %f", &temp.x, &temp.y, &temp.z);

				lightRotations.push_back(temp);
			}
			else if (inputString[1] == 's') {
				//This line holds light scale data
				glm::vec3 temp;

				std::sscanf(inputString, "Lsc %f %f %f", &temp.x, &temp.y, &temp.z);

				lightScales.push_back(temp);
			}
		}
	}

	input.close();

	return true;
}

void Scene::Load(Model* player, std::vector<Model*>& enemies, std::vector<Model*>& environments, std::vector<Model*>& lights)
{
	if (playerPath != "") {
		player = new Model();
		player->LoadFromFile(getPlayerPath(), getPlayerName());
		player->GetTransform()->setPos(getPlayerPosition());
		player->GetTransform()->setRot(getPlayerRotation());
		player->GetTransform()->setScale(getPlayerScale());
	}
	for (int i = 0; i < getEnemyCount(); i++) {
		if (i > 0) {
			for (int j = i-1; j >= 0; j--) {
				if (getEnemyPaths().at(j) == getEnemyPaths().at(i)) {
					enemies.push_back(new Model(*enemies[j]));
					break;
				}
			}
			if (enemies.size() < i + 1) {
				enemies.push_back(new Model());
				enemies.at(i)->LoadFromFile(getEnemyPaths().at(i), getEnemyNames().at(i));
			}
		}
		else {
			enemies.push_back(new Model());
			enemies.at(i)->LoadFromFile(getEnemyPaths().at(i), getEnemyNames().at(i));
		}
		enemies.at(i)->GetTransform()->setPos(getEnemyPositions().at(i));
		enemies.at(i)->GetTransform()->setRot(getEnemyRotations().at(i));
		enemies.at(i)->GetTransform()->setScale(getEnemyScales().at(i));
	}
	for (int i = 0; i < getEnvironmentCount(); i++) {
		if (i > 0) {
			for (int j = i - 1; j >= 0; j--) {
				if (getEnvironmentPaths().at(j) == getEnvironmentPaths().at(i)) {
					environments.push_back(new Model(*environments[j]));
					break;
				}
			}
			if (environments.size() < i + 1) {
				environments.push_back(new Model());
				environments.at(i)->LoadFromFile(getEnvironmentPaths().at(i), getEnvironmentNames().at(i));
			}
		}
		else {
			environments.push_back(new Model());
			environments.at(i)->LoadFromFile(getEnvironmentPaths().at(i), getEnvironmentNames().at(i));
		}
		environments.at(i)->GetTransform()->setPos(getEnvironmentPositions().at(i));
		environments.at(i)->GetTransform()->setRot(getEnvironmentRotations().at(i));
		environments.at(i)->GetTransform()->setScale(getEnvironmentScales().at(i));
	}
	for (int i = 0; i < getLightCount(); i++) {
		if (i > 0) {
			for (int j = i - 1; j >= 0; j--) {
				if (getLightPaths().at(j) == getLightPaths().at(i)) {
					lights.push_back(new Model(*lights[j]));
					break;
				}
			}
			if (lights.size() < i + 1) {
				lights.push_back(new Model());
				lights.at(i)->LoadFromFile(getLightPaths().at(i), getLightNames().at(i));
			}
		}
		else {
			lights.push_back(new Model());
			lights.at(i)->LoadFromFile(getLightPaths().at(i), getLightNames().at(i));
		}
		lights.at(i)->GetTransform()->setPos(getLightPositions().at(i));
		lights.at(i)->GetTransform()->setRot(getLightRotations().at(i));
		lights.at(i)->GetTransform()->setScale(getLightScales().at(i));
	}
}

bool Scene::Save(const Model &player, const std::vector<Model*> &enemies,
					const std::vector<Model*> &environments, const std::vector<Model*> &lights)
{
	std::ofstream output;
	output.open(fileName + ".scn");

	if (!output) {
		std::cout << "Scene file failed to open for saving.\n"
			<< "Idk wtf you did to cause this tbch\n";
		return false;
	}

	output << "En " + std::to_string(enemies.size()) << std::endl;
	output << "Evn " + std::to_string(environments.size()) << std::endl;
	output << "Ln " + std::to_string(lights.size()) << std::endl;

	for (int i = 0; i < enemies.size(); i++) {
		output << "Epa " + enemies[i]->path << std::endl;
		output << "Ena " + enemies[i]->name << std::endl;
		output << "Epo " + std::to_string(enemies[i]->GetTransform()->getPos().x) + " " +
									std::to_string(enemies[i]->GetTransform()->getPos().y) + " " +
										std::to_string(enemies[i]->GetTransform()->getPos().z) << std::endl;
		output << "Ert " + std::to_string(enemies[i]->GetTransform()->getRot().x) + " " +
									std::to_string(enemies[i]->GetTransform()->getRot().y) + " " +
										std::to_string(enemies[i]->GetTransform()->getRot().z) << std::endl;
		output << "Esc " + std::to_string(enemies[i]->GetTransform()->getScale().x) + " " +
									std::to_string(enemies[i]->GetTransform()->getScale().y) + " " +
										std::to_string(enemies[i]->GetTransform()->getScale().z) << std::endl;
	}

	for (int i = 0; i < environments.size(); i++) {
		output << "Evpa " + environments[i]->path << std::endl;
		output << "Evna " + environments[i]->name << std::endl;
		output << "Evpo " + std::to_string(environments[i]->GetTransform()->getPos().x) + " " +
									std::to_string(environments[i]->GetTransform()->getPos().y) + " " +
										std::to_string(environments[i]->GetTransform()->getPos().z) << std::endl;
		output << "Evrt " + std::to_string(environments[i]->GetTransform()->getRot().x) + " " +
									std::to_string(environments[i]->GetTransform()->getRot().y) + " " +
										std::to_string(environments[i]->GetTransform()->getRot().z) << std::endl;
		output << "Evsc " + std::to_string(environments[i]->GetTransform()->getScale().x) + " " +
									std::to_string(environments[i]->GetTransform()->getScale().y) + " " +
										std::to_string(environments[i]->GetTransform()->getScale().z) << std::endl;
	}

	for (int i = 0; i < lights.size(); i++) {
		output << "Lpa " + lights[i]->path << std::endl;
		output << "Lna " + lights[i]->name << std::endl;
		output << "Lpo " + std::to_string(lights[i]->GetTransform()->getPos().x) + " " +
									std::to_string(lights[i]->GetTransform()->getPos().y) + " " +
										std::to_string(lights[i]->GetTransform()->getPos().z) << std::endl;
		output << "Lrt " + std::to_string(lights[i]->GetTransform()->getRot().x) + " " +
									std::to_string(lights[i]->GetTransform()->getRot().y) + " " +
										std::to_string(lights[i]->GetTransform()->getRot().z) << std::endl;
		output << "Lsc " + std::to_string(lights[i]->GetTransform()->getScale().x) + " " +
									std::to_string(lights[i]->GetTransform()->getScale().y) + " " +
										std::to_string(lights[i]->GetTransform()->getScale().z) << std::endl;
	}

	output.close();

	return true;
}

std::string Scene::New(const Model &player, const std::vector<Model*> &enemies,
					const std::vector<Model*> &environments, const std::vector<Model*> &lights)
{
	//Choose a name for the new file
	bool input = true;
	std::string name;
	do {
		std::cout << "\n\n" << "Please select a name for your new scene:\n";
		std::cin >> name;
		if (std::strstr(name.c_str(), ".") != nullptr) {
			std::cout << "\n\n" << "Please try again without any periods";
		}
		else { input = false; }
	} while (input);

	std::ofstream output;

	output.open("./Resources/Scenes/" + name + ".scn");

	output << "En " + std::to_string(enemies.size()) << std::endl;
	output << "Evn " + std::to_string(environments.size()) << std::endl;
	output << "Ln " + std::to_string(lights.size()) << std::endl;

	for (int i = 0; i < enemies.size(); i++) {
		output << "Epa " + enemies[i]->path << std::endl;
		output << "Ena " + enemies[i]->name << std::endl;
		output << "Epo " + std::to_string(enemies[i]->GetTransform()->getPos().x) + " " +
									std::to_string(enemies[i]->GetTransform()->getPos().y) + " " +
										std::to_string(enemies[i]->GetTransform()->getPos().z) << std::endl;
		output << "Ert " + std::to_string(enemies[i]->GetTransform()->getRot().x) + " " +
									std::to_string(enemies[i]->GetTransform()->getRot().y) + " " +
										std::to_string(enemies[i]->GetTransform()->getRot().z) << std::endl;
		output << "Esc " + std::to_string(enemies[i]->GetTransform()->getScale().x) + " " +
									std::to_string(enemies[i]->GetTransform()->getScale().y) + " " +
										std::to_string(enemies[i]->GetTransform()->getScale().z) << std::endl;
	}

	for (int i = 0; i < environments.size(); i++) {
		output << "Evpa " + environments[i]->path << std::endl;
		output << "Evna " + environments[i]->name << std::endl;
		output << "Evpo " + std::to_string(environments[i]->GetTransform()->getPos().x) + " " +
									std::to_string(environments[i]->GetTransform()->getPos().y) + " " +
										std::to_string(environments[i]->GetTransform()->getPos().z) << std::endl;
		output << "Evrt " + std::to_string(environments[i]->GetTransform()->getRot().x) + " " +
									std::to_string(environments[i]->GetTransform()->getRot().y) + " " +
										std::to_string(environments[i]->GetTransform()->getRot().z) << std::endl;
		output << "Evsc " + std::to_string(environments[i]->GetTransform()->getScale().x) + " " +
									std::to_string(environments[i]->GetTransform()->getScale().y) + " " +
										std::to_string(environments[i]->GetTransform()->getScale().z) << std::endl;
	}

	for (int i = 0; i < lights.size(); i++) {
		output << "Lpa " + lights[i]->path << std::endl;
		output << "Lna " + lights[i]->name << std::endl;
		output << "Lpo " + std::to_string(lights[i]->GetTransform()->getPos().x) + " " +
									std::to_string(lights[i]->GetTransform()->getPos().y) + " " +
										std::to_string(lights[i]->GetTransform()->getPos().z) << std::endl;
		output << "Lrt " + std::to_string(lights[i]->GetTransform()->getRot().x) + " " +
									std::to_string(lights[i]->GetTransform()->getRot().y) + " " +
										std::to_string(lights[i]->GetTransform()->getRot().z) << std::endl;
		output << "Lsc " + std::to_string(lights[i]->GetTransform()->getScale().x) + " " +
									std::to_string(lights[i]->GetTransform()->getScale().y) + " " +
										std::to_string(lights[i]->GetTransform()->getScale().z) << std::endl;
	}

	output.close();

	return "./resources/Scenes/" + name;
}
