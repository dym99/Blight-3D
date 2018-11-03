#ifndef __SCENE_H__
#define __SCENE_H__
#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Model.h"
#include "GameObject.h"

class Scene : public GameObject {
public:
	Scene(const std::string& _name) : GameObject(_name), m_fileName("") {}
	~Scene() {}

	void setFile(const std::string& _fileName);

	bool loadScene();
	bool unloadScene();
private:
	std::string m_fileName;
};


#endif // !__SCENE_H__

