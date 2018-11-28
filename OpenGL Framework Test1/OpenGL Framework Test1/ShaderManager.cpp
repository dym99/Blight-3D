#include "ShaderManager.h"


std::vector<Shader*> ShaderManager::m_shaders = std::vector<Shader*>();
std::vector<Shader*> ShaderManager::m_postShaders = std::vector<Shader*>();

void ShaderManager::loadShaders()
{
	m_shaders.push_back(new Shader(
			"./Resources/Shaders/StaticGeometry.vert",
			"./Resources/Shaders/Phong.frag"
		));
}

void ShaderManager::reloadShaders()
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		m_shaders[i]->Reload();
	}
	for (unsigned int i = 0; i < m_postShaders.size(); i++) {
		m_postShaders[i]->Reload();
	}
}

void ShaderManager::unloadShaders()
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		m_shaders[i]->Unload();
	}
	for (unsigned int i = 0; i < m_postShaders.size(); i++) {
		m_postShaders[i]->Unload();
	}
}

void ShaderManager::update(Camera & _camera)
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		m_shaders[i]->update(_camera);
	}
}

Shader* ShaderManager::getShader(int shader)
{
	return m_shaders[shader];
}
