#define _CRT_SECURE_NO_WARNINGS
#include "Scene.h"
#include <fstream>
#include <iostream>

void Scene::setFile(const std::string & _fileName)
{
	m_fileName = "Resources/scenes/"+_fileName+".scene";
}

bool Scene::loadScene()
{
	if (m_fileName=="")
		return false;


	return true;
}

bool Scene::unloadScene()
{
	for (unsigned int i = 0; i < m_children.size(); ++i) {
		delete m_children[i];
		m_children[i] = nullptr;
	}
	removeChildren();
	return false;
}
