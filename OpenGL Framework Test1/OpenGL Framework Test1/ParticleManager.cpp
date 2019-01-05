#include "ParticleManager.h"
#include <iostream>

std::vector<ParticleEffect*> ParticleManager::m_particleEffects = std::vector<ParticleEffect*>();

void ParticleManager::loadParticles()
{
	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/Fog.png", 1200, 10)) {
		std::cout << "Particle effect failed to initializie.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[0]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[0]->LerpSize = glm::vec2(0.0f, 5.0f);
	m_particleEffects[0]->RangeLifetime = glm::vec2(8.0f, 20.0f);
	m_particleEffects[0]->RangeVelocity = glm::vec2(0.33f, 0.4f);
	m_particleEffects[0]->RangeX = glm::vec2(0.2f, 0.3f);
	m_particleEffects[0]->RangeY = glm::vec2(0.2f, 0.3f);
	m_particleEffects[0]->RangeZ = glm::vec2(0.2f, 0.3f);
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
