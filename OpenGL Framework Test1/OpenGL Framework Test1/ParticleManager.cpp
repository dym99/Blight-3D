#include "ParticleManager.h"
#include <iostream>

std::vector<ParticleEffect*> ParticleManager::m_particleEffects = std::vector<ParticleEffect*>();

void ParticleManager::loadParticles()
{
	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[0]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[0]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[0]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[0]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[0]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[0]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[0]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[0]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[0]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[0]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[0]->transform.setPos(glm::vec3(-44.633648, 0.500000, 5.672839));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[1]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[1]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[1]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[1]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[1]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[1]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[1]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[1]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[1]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[1]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[1]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[1]->transform.setPos(glm::vec3(-44.633648, 0.500000, 5.672839));
	
	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[2]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[2]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[2]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[2]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[2]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[2]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[2]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[2]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[2]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[2]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[2]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[2]->transform.setPos(glm::vec3(-44.090328, 0.500000, -6.341741));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[3]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[3]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[3]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[3]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[3]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[3]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[3]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[3]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[3]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[3]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[3]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[3]->transform.setPos(glm::vec3(-44.090328, 0.500000, -6.341741));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[4]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[4]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[4]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[4]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[4]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[4]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[4]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[4]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[4]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[4]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[4]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[4]->transform.setPos(glm::vec3(-26.775608, 0.500000, 9.505545));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[5]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[5]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[5]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[5]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[5]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[5]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[5]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[5]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[5]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[5]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[5]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[5]->transform.setPos(glm::vec3(-26.775608, 0.500000, 9.505545));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[6]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[6]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[6]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[6]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[6]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[6]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[6]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[6]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[6]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[6]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[6]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[6]->transform.setPos(glm::vec3(-26.590355, 0.500000, -6.158344));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[7]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[7]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[7]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[7]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[7]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[7]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[7]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[7]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[7]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[7]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[7]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[7]->transform.setPos(glm::vec3(-26.590355, 0.500000, -6.158344));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[4]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[8]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[8]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[8]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[8]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[8]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[8]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[8]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[8]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[8]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[8]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[8]->transform.setPos(glm::vec3(-20.662336, 0.500000, 13.387436));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[9]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[9]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[9]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[9]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[9]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[9]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[9]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[9]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[9]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[9]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[9]->transform.setPos(glm::vec3(-20.662336, 0.500000, 13.387436));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[5]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[10]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[10]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[10]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[10]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[10]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[10]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[10]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[10]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[10]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[10]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[10]->transform.setPos(glm::vec3(-19.626617, 0.500000, -14.462436));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[11]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[11]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[11]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[11]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[11]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[11]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[11]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[11]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[11]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[11]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[11]->transform.setPos(glm::vec3(-19.626617, 0.500000, -14.462436));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[6]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[12]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[12]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[12]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[12]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[12]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[12]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[12]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[12]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[12]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[12]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[12]->transform.setPos(glm::vec3(-2.028160, 0.500000, -20.524620));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[13]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[13]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[13]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[13]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[13]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[13]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[13]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[13]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[13]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[13]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[13]->transform.setPos(glm::vec3(-2.028160, 0.500000, -20.524620));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[7]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[14]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[14]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[14]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[14]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[14]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[14]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[14]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[14]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[14]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[14]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[14]->transform.setPos(glm::vec3(-2.043056, 0.500000, -27.361380));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[15]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[15]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[15]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[15]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[15]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[15]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[15]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[15]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[15]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[15]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[15]->transform.setPos(glm::vec3(-2.043056, 0.500000, -27.361380));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[8]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[16]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[16]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[16]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[16]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[16]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[16]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[16]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[16]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[16]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[16]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[16]->transform.setPos(glm::vec3(-8.776593, 0.500000, -35.394379));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[17]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[17]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[17]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[17]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[17]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[17]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[17]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[17]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[17]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[17]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[17]->transform.setPos(glm::vec3(-8.776593, 0.500000, -35.394379));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[9]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[18]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[18]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[18]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[18]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[18]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[18]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[18]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[18]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[18]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[18]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[18]->transform.setPos(glm::vec3(8.868602, 0.500000, -35.207016));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[19]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[19]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[19]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[19]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[19]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[19]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[19]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[19]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[19]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[19]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[19]->transform.setPos(glm::vec3(8.868602, 0.500000, -35.207016));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[10]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[20]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[20]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[20]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[20]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[20]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[20]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[20]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[20]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[20]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[20]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[20]->transform.setPos(glm::vec3(-13.200074, 0.500000, -40.927586));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[21]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[21]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[21]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[21]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[21]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[21]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[21]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[21]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[21]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[21]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[21]->transform.setPos(glm::vec3(-13.200074, 0.500000, -40.927586));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[11]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[22]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[22]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[22]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[22]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[22]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[22]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[22]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[22]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[22]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[22]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[22]->transform.setPos(glm::vec3(-20.744389, 0.500000, -41.195820));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[23]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[23]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[23]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[23]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[23]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[23]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[23]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[23]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[23]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[23]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[23]->transform.setPos(glm::vec3(-20.744389, 0.500000, -41.195820));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[12]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[24]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[24]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[24]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[24]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[24]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[24]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[24]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[24]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[24]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[24]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[24]->transform.setPos(glm::vec3(-19.371952, 0.500000, -49.894417));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[25]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[25]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[25]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[25]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[25]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[25]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[25]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[25]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[25]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[25]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[25]->transform.setPos(glm::vec3(-19.371952, 0.500000, -49.894417));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[13]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[26]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[26]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[26]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[26]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[26]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[26]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[26]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[26]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[26]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[26]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[26]->transform.setPos(glm::vec3(-0.732033, 0.500000, -45.884380));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[27]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[27]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[27]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[27]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[27]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[27]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[27]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[27]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[27]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[27]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[27]->transform.setPos(glm::vec3(-0.732033, 0.500000, -45.884380));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[14]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[28]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[28]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[28]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[28]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[28]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[28]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[28]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[28]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[28]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[28]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[28]->transform.setPos(glm::vec3(-0.732033, 0.500000, -52.130676));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[29]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[29]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[29]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[29]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[29]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[29]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[29]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[29]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[29]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[29]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[29]->transform.setPos(glm::vec3(-0.732033, 0.500000, -52.130676));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[15]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[30]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[30]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[30]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[30]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[30]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[30]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[30]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[30]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[30]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[30]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[30]->transform.setPos(glm::vec3(19.899551, 0.500000, -50.202072));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[31]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[31]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[31]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[31]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[31]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[31]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[31]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[31]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[31]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[31]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[31]->transform.setPos(glm::vec3(19.899551, 0.500000, -50.202072));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[16]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[32]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[32]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[32]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[32]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[32]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[32]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[32]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[32]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[32]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[32]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[32]->transform.setPos(glm::vec3(19.737904, 0.500000, -42.220512));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[33]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[33]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[33]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[33]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[33]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[33]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[33]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[33]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[33]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[33]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[33]->transform.setPos(glm::vec3(19.737904, 0.500000, -42.220512));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[17]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[34]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[34]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[34]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[34]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[34]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[34]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[34]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[34]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[34]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[34]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[34]->transform.setPos(glm::vec3(14.181462, 0.500000, -42.111050));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[35]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[35]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[35]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[35]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[35]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[35]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[35]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[35]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[35]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[35]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[35]->transform.setPos(glm::vec3(14.181462, 0.500000, -42.111050));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[18]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[36]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[36]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[36]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[36]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[36]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[36]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[36]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[36]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[36]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[36]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[36]->transform.setPos(glm::vec3(18.004396, 0.500000, -20.646599));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[37]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[37]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[37]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[37]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[37]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[37]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[37]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[37]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[37]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[37]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[37]->transform.setPos(glm::vec3(18.004396, 0.500000, -20.646599));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[19]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}				  
	m_particleEffects[38]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[38]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[38]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[38]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[38]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[38]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[38]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[38]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[38]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[38]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[38]->transform.setPos(glm::vec3(12.796072, 0.500000, -20.646599f));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[39]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[39]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[39]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[39]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[39]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[39]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[39]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[39]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[39]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[39]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[39]->transform.setPos(glm::vec3(12.796072, 0.500000, -20.646599f));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[20]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {			
		std::cout << "Particle effect failed to initialize.\n";									
		system("Pause");																		
		exit(0);																				
	}																							
	
	m_particleEffects[40]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[40]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[40]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[40]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[40]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[40]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[40]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[40]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[40]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[40]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[40]->transform.setPos(glm::vec3(2.245983, 0.500000, -20.821217));		
																							
	m_particleEffects.push_back(new ParticleEffect());										
	//Initialize particle effect															
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {				
		std::cout << "Particle effect failed to initialize.\n";								
		system("Pause");																	
		exit(0);																			
	}																						
	m_particleEffects[41]->LerpAlpha = glm::vec2(0.1f, 0.0f);								
	m_particleEffects[41]->LerpSize = glm::vec2(0.0f, 1.0f);								
	m_particleEffects[41]->RangeLifetime = glm::vec2(0.0f, 2.0f);							
	m_particleEffects[41]->RangeVelocity = glm::vec2(0.0f, 0.1f);							
	m_particleEffects[41]->RangeVelocityX = glm::vec2(0.0f, 0.1f);							
	m_particleEffects[41]->RangeVelocityY = glm::vec2(0.0f, 1.0f);							
	m_particleEffects[41]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);							
	m_particleEffects[41]->RangeX = glm::vec2(-0.2f, 0.2f);									
	m_particleEffects[41]->RangeY = glm::vec2(0.f, 0.5f);									
	m_particleEffects[41]->RangeZ = glm::vec2(-0.2f, 0.2f);									
	m_particleEffects[41]->transform.setPos(glm::vec3(2.245983, 0.500000, -20.821217));		
																								  
	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[21]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[42]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[42]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[42]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[42]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[42]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[42]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[42]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[42]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[42]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[42]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[42]->transform.setPos(glm::vec3(32.002598, 0.500000, -1.914401));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[43]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[43]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[43]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[43]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[43]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[43]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[43]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[43]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[43]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[43]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[43]->transform.setPos(glm::vec3(32.002598, 0.500000, -1.914401));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[22]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[44]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[44]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[44]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[44]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[44]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[44]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[44]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[44]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[44]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[44]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[44]->transform.setPos(glm::vec3(32.002598, 0.500000, 1.469780));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[45]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[45]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[45]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[45]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[45]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[45]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[45]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[45]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[45]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[45]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[45]->transform.setPos(glm::vec3(32.002598, 0.500000, 1.469780));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[23]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[46]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[46]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[46]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[46]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[46]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[46]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[46]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[46]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[46]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[46]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[46]->transform.setPos(glm::vec3(28.118650, 0.500000, 1.469780));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[47]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[47]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[47]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[47]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[47]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[47]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[47]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[47]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[47]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[47]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[47]->transform.setPos(glm::vec3(28.118650, 0.500000, 1.469780));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[24]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[48]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[48]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[48]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[48]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[48]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[48]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[48]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[48]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[48]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[48]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[48]->transform.setPos(glm::vec3(28.118650, 0.500000, -1.914401));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[49]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[49]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[49]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[49]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[49]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[49]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[49]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[49]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[49]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[49]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[49]->transform.setPos(glm::vec3(28.118650, 0.500000, -1.914401));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[25]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[50]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[50]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[50]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[50]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[50]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[50]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[50]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[50]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[50]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[50]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[50]->transform.setPos(glm::vec3(28.118650, 0.500000, -5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[51]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[51]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[51]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[51]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[51]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[51]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[51]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[51]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[51]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[51]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[51]->transform.setPos(glm::vec3(28.118650, 0.500000, -5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[26]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[52]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[52]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[52]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[52]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[52]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[52]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[52]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[52]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[52]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[52]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[52]->transform.setPos(glm::vec3(32.002598, 0.500000, -5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[53]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[53]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[53]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[53]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[53]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[53]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[53]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[53]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[53]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[53]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[53]->transform.setPos(glm::vec3(32.002598, 0.500000, -5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[27]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[54]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[54]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[54]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[54]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[54]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[54]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[54]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[54]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[54]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[54]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[54]->transform.setPos(glm::vec3(28.118650, 0.500000, 5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[55]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[55]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[55]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[55]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[55]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[55]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[55]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[55]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[55]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[55]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[55]->transform.setPos(glm::vec3(28.118650, 0.500000, 5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[28]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[56]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[56]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[56]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[56]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[56]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[56]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[56]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[56]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[56]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[56]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[56]->transform.setPos(glm::vec3(32.002598, 0.500000, 5.344815));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {							
		std::cout << "Particle effect failed to initialize.\n";											
		system("Pause");																				
		exit(0);																						
	}																									
	m_particleEffects[57]->LerpAlpha = glm::vec2(0.1f, 0.0f);											
	m_particleEffects[57]->LerpSize = glm::vec2(0.0f, 1.0f);											
	m_particleEffects[57]->RangeLifetime = glm::vec2(0.0f, 2.0f);										
	m_particleEffects[57]->RangeVelocity = glm::vec2(0.0f, 0.1f);										
	m_particleEffects[57]->RangeVelocityX = glm::vec2(0.0f, 0.1f);										
	m_particleEffects[57]->RangeVelocityY = glm::vec2(0.0f, 1.0f);										
	m_particleEffects[57]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);										
	m_particleEffects[57]->RangeX = glm::vec2(-0.2f, 0.2f);												
	m_particleEffects[57]->RangeY = glm::vec2(0.f, 0.5f);												
	m_particleEffects[57]->RangeZ = glm::vec2(-0.2f, 0.2f);												
	m_particleEffects[57]->transform.setPos(glm::vec3(32.002598, 0.500000, 5.344815));					
																										
	m_particleEffects.push_back(new ParticleEffect());													
	//Initialize particle effect
	if (!m_particleEffects[29]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[58]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[58]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[58]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[58]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[58]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[58]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[58]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[58]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[58]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[58]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[58]->transform.setPos(glm::vec3(61.330212, 0.500000, -6.199307));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[59]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[59]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[59]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[59]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[59]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[59]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[59]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[59]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[59]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[59]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[59]->transform.setPos(glm::vec3(61.330212, 0.500000, -6.199307));

	m_particleEffects.push_back(new ParticleEffect());									 
	//Initialize particle effect														 
	if (!m_particleEffects[30]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {	
		std::cout << "Particle effect failed to initialize.\n";							 
		system("Pause");																 
		exit(0);																		 
	}																					 
	m_particleEffects[60]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[60]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[60]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[60]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[60]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[60]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[60]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[60]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[60]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[60]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[60]->transform.setPos(glm::vec3(61.330212, 0.500000, 6.199307));	 
																						 
	m_particleEffects.push_back(new ParticleEffect());									 
	//Initialize particle effect														 
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {			 
		std::cout << "Particle effect failed to initialize.\n";							 
		system("Pause");																 
		exit(0);																		 
	}																					 
	m_particleEffects[61]->LerpAlpha = glm::vec2(0.1f, 0.0f);							 
	m_particleEffects[61]->LerpSize = glm::vec2(0.0f, 1.0f);							 
	m_particleEffects[61]->RangeLifetime = glm::vec2(0.0f, 2.0f);						 
	m_particleEffects[61]->RangeVelocity = glm::vec2(0.0f, 0.1f);						 
	m_particleEffects[61]->RangeVelocityX = glm::vec2(0.0f, 0.1f);						 
	m_particleEffects[61]->RangeVelocityY = glm::vec2(0.0f, 1.0f);						 
	m_particleEffects[61]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);						 
	m_particleEffects[61]->RangeX = glm::vec2(-0.2f, 0.2f);								 
	m_particleEffects[61]->RangeY = glm::vec2(0.f, 0.5f);								 
	m_particleEffects[61]->RangeZ = glm::vec2(-0.2f, 0.2f);								 
	m_particleEffects[61]->transform.setPos(glm::vec3(61.330212, 0.500000, 6.199307));	 //

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[31]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[62]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[62]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[62]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[62]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[62]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[62]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[62]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[62]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[62]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[62]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[62]->transform.setPos(glm::vec3(53.128838, 0.500000, 0.000000));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[63]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[63]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[63]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[63]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[63]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[63]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[63]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[63]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[63]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[63]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[63]->transform.setPos(glm::vec3(53.128838, 0.500000, 0.000000));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[32]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[64]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[64]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[64]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[64]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[64]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[64]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[64]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[64]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[64]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[64]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[64]->transform.setPos(glm::vec3(43.614162, 0.500000, 13.970689));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[65]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[65]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[65]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[65]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[65]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[65]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[65]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[65]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[65]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[65]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[65]->transform.setPos(glm::vec3(43.614162, 0.500000, 13.970689));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[33]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[66]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[66]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[66]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[66]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[66]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[66]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[66]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[66]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[66]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[66]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[66]->transform.setPos(glm::vec3(43.614162, 0.500000, -13.970689));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[67]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[67]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[67]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[67]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[67]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[67]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[67]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[67]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[67]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[67]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[67]->transform.setPos(glm::vec3(43.614162, 0.500000, -13.970689));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[34]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[68]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[68]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[68]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[68]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[68]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[68]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[68]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[68]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[68]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[68]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[68]->transform.setPos(glm::vec3(13.018315, 0.500000, 45.338821));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[69]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[69]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[69]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[69]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[69]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[69]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[69]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[69]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[69]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[69]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[69]->transform.setPos(glm::vec3(13.018315, 0.500000, 45.338821));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[35]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[70]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[70]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[70]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[70]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[70]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[70]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[70]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[70]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[70]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[70]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[70]->transform.setPos(glm::vec3(16.903147, 0.500000, 49.881462));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[71]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[71]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[71]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[71]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[71]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[71]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[71]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[71]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[71]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[71]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[71]->transform.setPos(glm::vec3(16.903147, 0.500000, 49.881462));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[36]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[72]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[72]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[72]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[72]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[72]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[72]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[72]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[72]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[72]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[72]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[72]->transform.setPos(glm::vec3(-13.018315, 0.500000, 45.338821));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[73]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[73]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[73]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[73]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[73]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[73]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[73]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[73]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[73]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[73]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[73]->transform.setPos(glm::vec3(-13.018315, 0.500000, 45.338821));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[37]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[74]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[74]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[74]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[74]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[74]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[74]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[74]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[74]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[74]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[74]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[74]->transform.setPos(glm::vec3(-16.903147, 0.500000, 49.881462));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[75]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[75]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[75]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[75]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[75]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[75]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[75]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[75]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[75]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[75]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[75]->transform.setPos(glm::vec3(-16.903147, 0.500000, 49.881462));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[38]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[76]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[76]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[76]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[76]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[76]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[76]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[76]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[76]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[76]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[76]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[76]->transform.setPos(glm::vec3(21.690195, 0.500000, 38.013233));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[77]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[77]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[77]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[77]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[77]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[77]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[77]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[77]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[77]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[77]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[77]->transform.setPos(glm::vec3(21.690195, 0.500000, 38.013233));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[39]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[78]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[78]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[78]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[78]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[78]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[78]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[78]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[78]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[78]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[78]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[78]->transform.setPos(glm::vec3(-21.690195, 0.500000, 38.013233));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[79]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[79]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[79]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[79]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[79]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[79]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[79]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[79]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[79]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[79]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[79]->transform.setPos(glm::vec3(-21.690195, 0.500000, 38.013233));

	m_particleEffects.push_back(new ParticleEffect());										  
	//Initialize particle effect															  
	if (!m_particleEffects[40]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {				  
		std::cout << "Particle effect failed to initialize.\n";								  
		system("Pause");																	  
		exit(0);																			  
	}																						  
	m_particleEffects[80]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[80]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[80]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[80]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[80]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[80]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[80]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[80]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[80]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[80]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[80]->transform.setPos(glm::vec3(-2.287966, 0.500000, 44.972633));		  
																							  
	m_particleEffects.push_back(new ParticleEffect());										  
	//Initialize particle effect															  
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {				  
		std::cout << "Particle effect failed to initialize.\n";								  
		system("Pause");																	  
		exit(0);																			  
	}																						  
	m_particleEffects[81]->LerpAlpha = glm::vec2(0.1f, 0.0f);								  
	m_particleEffects[81]->LerpSize = glm::vec2(0.0f, 1.0f);								  
	m_particleEffects[81]->RangeLifetime = glm::vec2(0.0f, 2.0f);							  
	m_particleEffects[81]->RangeVelocity = glm::vec2(0.0f, 0.1f);							  
	m_particleEffects[81]->RangeVelocityX = glm::vec2(0.0f, 0.1f);							  
	m_particleEffects[81]->RangeVelocityY = glm::vec2(0.0f, 1.0f);							  
	m_particleEffects[81]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);							  
	m_particleEffects[81]->RangeX = glm::vec2(-0.2f, 0.2f);									  
	m_particleEffects[81]->RangeY = glm::vec2(0.f, 0.5f);									  
	m_particleEffects[81]->RangeZ = glm::vec2(-0.2f, 0.2f);									  
	m_particleEffects[81]->transform.setPos(glm::vec3(-2.287966, 0.500000, 44.972633));		  

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[41]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[82]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[82]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[82]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[82]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[82]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[82]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[82]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[82]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[82]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[82]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[82]->transform.setPos(glm::vec3(2.287966, 0.500000, 44.972633));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[83]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[83]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[83]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[83]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[83]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[83]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[83]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[83]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[83]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[83]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[83]->transform.setPos(glm::vec3(2.287966, 0.500000, 44.972633));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[42]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[84]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[84]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[84]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[84]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[84]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[84]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[84]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[84]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[84]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[84]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[84]->transform.setPos(glm::vec3(13.638598, 0.500000, 28.890642));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[85]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[85]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[85]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[85]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[85]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[85]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[85]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[85]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[85]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[85]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[85]->transform.setPos(glm::vec3(13.638598, 0.500000, 28.890642));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[43]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[86]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[86]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[86]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[86]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[86]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[86]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[86]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[86]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[86]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[86]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[86]->transform.setPos(glm::vec3(16.099287, 0.500000, 25.178598));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[87]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[87]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[87]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[87]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[87]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[87]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[87]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[87]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[87]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[87]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[87]->transform.setPos(glm::vec3(16.099287, 0.500000, 25.178598));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[44]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[88]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[88]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[88]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[88]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[88]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[88]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[88]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[88]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[88]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[88]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[88]->transform.setPos(glm::vec3(-13.638598, 0.500000, 28.890642));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[89]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[89]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[89]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[89]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[89]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[89]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[89]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[89]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[89]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[89]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[89]->transform.setPos(glm::vec3(-13.638598, 0.500000, 28.890642));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[45]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[90]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[90]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[90]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[90]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[90]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[90]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[90]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[90]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[90]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[90]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[90]->transform.setPos(glm::vec3(-16.099287, 0.500000, 25.178598));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[91]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[91]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[91]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[91]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[91]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[91]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[91]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[91]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[91]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[91]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[91]->transform.setPos(glm::vec3(-16.099287, 0.500000, 25.178598));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[46]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[92]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[92]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[92]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[92]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[92]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[92]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[92]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[92]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[92]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[92]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[92]->transform.setPos(glm::vec3(9.315192, 0.500000, 20.322336));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[93]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[93]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[93]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[93]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[93]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[93]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[93]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[93]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[93]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[93]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[93]->transform.setPos(glm::vec3(9.315192, 0.500000, 20.322336));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[47]->Init("./Resources/Textures/fireYellow.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[94]->LerpAlpha = glm::vec2(0.3f, 0.0f);
	m_particleEffects[94]->LerpSize = glm::vec2(0.0f, 0.2f);
	m_particleEffects[94]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[94]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[94]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[94]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[94]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[94]->RangeX = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[94]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[94]->RangeZ = glm::vec2(-0.1f, 0.1f);
	m_particleEffects[94]->transform.setPos(glm::vec3(-9.315192, 0.500000, 20.322336));

	m_particleEffects.push_back(new ParticleEffect());
	//Initialize particle effect
	if (!m_particleEffects[0]->Init("./Resources/Textures/fire.png", 10, 2)) {
		std::cout << "Particle effect failed to initialize.\n";
		system("Pause");
		exit(0);
	}
	m_particleEffects[95]->LerpAlpha = glm::vec2(0.1f, 0.0f);
	m_particleEffects[95]->LerpSize = glm::vec2(0.0f, 1.0f);
	m_particleEffects[95]->RangeLifetime = glm::vec2(0.0f, 2.0f);
	m_particleEffects[95]->RangeVelocity = glm::vec2(0.0f, 0.1f);
	m_particleEffects[95]->RangeVelocityX = glm::vec2(0.0f, 0.1f);
	m_particleEffects[95]->RangeVelocityY = glm::vec2(0.0f, 1.0f);
	m_particleEffects[95]->RangeVelocityZ = glm::vec2(0.0f, 0.1f);
	m_particleEffects[95]->RangeX = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[95]->RangeY = glm::vec2(0.f, 0.5f);
	m_particleEffects[95]->RangeZ = glm::vec2(-0.2f, 0.2f);
	m_particleEffects[95]->transform.setPos(glm::vec3(-9.315192, 0.500000, 20.322336));
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
