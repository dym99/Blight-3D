#include "ParticleManager.h"
#include <iostream>

std::vector<ParticleEffect*> ParticleManager::m_particleEffects = std::vector<ParticleEffect*>();

void ParticleManager::loadParticles()
{
	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/Fog.png", 600, 10)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[0]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[0]->LerpSize = glm::vec2(0.0f, 5.0f);
	m_particleEffects[0]->RangeLifetime = glm::vec2(8.0f, 10.0f);
	m_particleEffects[0]->RangeVelocity = glm::vec2(0.33f, 0.4f);
	m_particleEffects[0]->RangeX = glm::vec2(0.2f, 0.3f);
	m_particleEffects[0]->RangeY = glm::vec2(0.2f, 0.3f);
	m_particleEffects[0]->RangeZ = glm::vec2(0.2f, 0.3f);

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[1]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[1]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[1]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[1]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[1]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[1]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[1]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[1]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[1]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[1]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[1]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[1]->transform.setPos(glm::vec3(3.f, 0.5f, 3.f));
	
	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[2]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[2]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[2]->LerpSize = glm::vec2(0.0f, 0.3f);
	m_particleEffects[2]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[2]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[2]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[2]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[2]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[2]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[2]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[2]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[2]->transform.setPos(glm::vec3(3.f, 0.5f, 3.f));
}					  

void ParticleManager::unloadParticles()
{
	for (unsigned int i = 0; i < m_particleEffects.size(); i++)
	{
		delete m_particleEffects[i];
		m_particleEffects[i] = nullptr;
	}
}

void ParticleManager::update(float dt)
{
	for (unsigned int i = 0; i < m_particleEffects.size(); i++)
	{
		m_particleEffects[i]->Update(dt);
	}
}

void ParticleManager::update(int index, float dt)
{
	m_particleEffects[index]->Update(dt);
}

void ParticleManager::render()
{
	for (unsigned int i = 0; i < m_particleEffects.size(); i++)
	{
		m_particleEffects[i]->Render();
	}
}

void ParticleManager::render(int index)
{
	m_particleEffects[index]->Render();
}

ParticleEffect * ParticleManager::getParticle(int index)
{
	return m_particleEffects[index];
}
