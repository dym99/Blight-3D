#include "ShaderManager.h"


std::vector<Shader*> ShaderManager::m_shaders = std::vector<Shader*>();
std::vector<Shader*> ShaderManager::m_geomShaders = std::vector<Shader*>();
std::vector<Shader*> ShaderManager::m_postShaders = std::vector<Shader*>();
std::vector<Shader*> ShaderManager::m_bloomComponents = std::vector<Shader*>();

void ShaderManager::loadShaders()
{
	//Regular shaders
	m_shaders.push_back(new Shader(
		"./Resources/Shaders/StaticGeometry.vert",
		"./Resources/Shaders/Phong.frag"
	));

	m_shaders.push_back(new Shader(
		"./Resources/Shaders/StaticGeometry.vert",
		"./Resources/Shaders/GBufferPass.frag"
	));

	m_shaders.push_back(new Shader(
		"./Resources/Shaders/SkinnedMesh.vert",
		"./Resources/Shaders/GBufferPass.frag"
	));

	//Geometry shaders
	m_geomShaders.push_back(new Shader(
		"./Resources/Shaders/Particles/Billboard.vert",
		"./Resources/Shaders/Particles/Billboard.frag",
		"./Resources/Shaders/Particles/Billboard.geom"
	));

	//Post Processing shaders
	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/DeferredLighting.frag"
	));
	
	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/GreyScalePost.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/SepiaPost.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/FocusIn.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/InvertColor.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/InvertLuminence.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/Rainbow.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/UserInterface.frag"
	));

	m_postShaders.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/PostProcess/PassThrough.frag"
	));

	//Bloom components
	m_bloomComponents.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/Bloom/BloomHighPass.frag"
	));

	m_bloomComponents.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/Bloom/BlurVertical.frag"
	));

	m_bloomComponents.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/Bloom/BlurHorizontal.frag"
	));

	m_bloomComponents.push_back(new Shader(
		"./Resources/Shaders/PassThrough.vert",
		"./Resources/Shaders/Bloom/BloomComposite.frag"
	));
}

void ShaderManager::reloadShaders()
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		m_shaders[i]->Reload();
	}
	for (unsigned int i = 0; i < m_geomShaders.size(); i++) {
		m_geomShaders[i]->Reload();
	}
	for (unsigned int i = 0; i < m_postShaders.size(); i++) {
		m_postShaders[i]->Reload();
	}
	for (unsigned int i = 0; i < m_bloomComponents.size(); i++) {
		m_bloomComponents[i]->Reload();
	}
}

void ShaderManager::unloadShaders()
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		m_shaders[i]->Unload();
	}
	for (unsigned int i = 0; i < m_geomShaders.size(); i++) {
		m_geomShaders[i]->Unload();
	}
	for (unsigned int i = 0; i < m_postShaders.size(); i++) {
		m_postShaders[i]->Unload();
	}
	for (unsigned int i = 0; i < m_bloomComponents.size(); i++) {
		m_bloomComponents[i]->Unload();
	}
}

void ShaderManager::update(Camera & _camera)
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		m_shaders[i]->update(_camera);
	}

	//Have no idea why I need to bind this one, but the view and projection matrices
	//kept coming up as completely empty when I was debugging it
	for (unsigned int i = 0; i < m_geomShaders.size(); i++) {
		m_geomShaders[i]->bind();
		m_geomShaders[i]->update(_camera);
		m_geomShaders[i]->unbind();
	}
}

Shader* ShaderManager::getShader(int shader)
{
	return m_shaders[shader];
}

Shader * ShaderManager::getGeom(int geom)
{
	return m_geomShaders[geom];
}

Shader * ShaderManager::getPost(int post)
{
	return m_postShaders[post];
}

std::vector<Shader*>& ShaderManager::getBloom()
{
	return m_bloomComponents;
}
