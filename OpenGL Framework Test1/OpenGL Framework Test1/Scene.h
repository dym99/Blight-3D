#ifndef __SCENE_H__
#define __SCENE_H__
#define GLM_ENABLE_EXPERIMENTAL
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Model.h"


class Scene {
public:
	Scene(const std::string &file);
	~Scene();

	//Methods
		//processes the selected scene
		bool ProcessFile(const std::string &file);
		//Loads in the processed scene
		void Load(Model* player, std::vector<Model*> &enemies,
					std::vector<Model*> &environments, std::vector<Model*> &lights);
		//Saves over the currently selected file
		bool Save(const Model &player, const std::vector<Model*> &enemies,
					const std::vector<Model*> &environments, const std::vector<Model*> &lights);
		//Creates a brand new scene with the data in the scene when you call this method
		static std::string New(const Model &player, const std::vector<Model*> &enemies,
							const std::vector<Model*> &environments, const std::vector<Model*> &lights);

	//Helpers
		//Filename
		inline std::string& GetFileName() { return fileName; }

		//counts
		inline unsigned int& GetEnemyCount() { return enemyCount; }
		inline unsigned int& GetEnvironmentCount() { return environmentCount; };
		inline unsigned int& GetLightCount() { return lightCount; }

		//paths
		inline std::string& GetPlayerPath() { return playerPath; }
		inline std::vector<std::string>& GetEnemyPaths() { return enemyPaths; }
		inline std::vector<std::string>& GetEnvironmentPaths() { return environmentPaths; }
		inline std::vector<std::string>& GetLightPaths() { return lightPaths; }

		//names
		inline std::string& GetPlayerName() { return playerName; }
		inline std::vector<std::string>& GetEnemyNames() { return enemyNames; }
		inline std::vector<std::string>& GetEnvironmentNames() { return environmentNames; }
		inline std::vector<std::string>& GetLightNames() { return lightNames; }
			
		//positions
		inline glm::vec3& GetPlayerPosition() { return playerPosition; }
		inline std::vector<glm::vec3>& GetEnemyPositions() { return enemyPositions; }
		inline std::vector<glm::vec3>& GetEnvironmentPositions() { return environmentPositions; }
		inline std::vector<glm::vec3>& GetLightPositions() { return lightPositions; }
		
		//rotations
		inline glm::vec3& GetPlayerRotation() { return playerRotation; }
		inline std::vector<glm::vec3>& GetEnemyRotations() { return enemyRotations; }
		inline std::vector<glm::vec3>& GetEnvironmentRotations() { return environmentRotations; }
		inline std::vector<glm::vec3>& GetLightRotations() { return lightRotations; }
		
		//scales
		inline glm::vec3& GetPlayerScale() { return playerScale; }
		inline std::vector<glm::vec3>& GetEnemyScales() { return enemyScales; }
		inline std::vector<glm::vec3>& GetEnvironmentScales() { return environmentScales; }
		inline std::vector<glm::vec3>& GetLightScales() { return lightScales; }
	//!Helpers

private:
	std::string fileName;

	//Model counts
	unsigned int enemyCount;		//Eventually will have to split into individual enemy types
	unsigned int environmentCount;	//Eventually will need to split into collidable and non collidable
	unsigned int lightCount;

	//Model paths
	std::string playerPath;
	std::vector<std::string> enemyPaths;
	std::vector<std::string> environmentPaths;
	std::vector<std::string> lightPaths;

	//Model names
	std::string playerName;
	std::vector<std::string> enemyNames;
	std::vector<std::string> environmentNames;
	std::vector<std::string> lightNames;

	//Model positions
	glm::vec3 playerPosition;
	std::vector<glm::vec3> enemyPositions;
	std::vector<glm::vec3> environmentPositions;
	std::vector<glm::vec3> lightPositions;

	//Model rotations
	glm::vec3 playerRotation;
	std::vector<glm::vec3> enemyRotations;
	std::vector<glm::vec3> environmentRotations;
	std::vector<glm::vec3> lightRotations;

	//Model scales
	glm::vec3 playerScale;
	std::vector<glm::vec3> enemyScales;
	std::vector<glm::vec3> environmentScales;
	std::vector<glm::vec3> lightScales;
};


#endif // !__SCENE_H__

