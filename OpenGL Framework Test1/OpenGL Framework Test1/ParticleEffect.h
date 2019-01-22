#ifndef __PARTICLEEFFECT_H__
#define __PARTICLEEFFECT_H__

#include <vector>
#include <glm/common.hpp>
#include "Transform.h"
#include "Texture.h"

struct ParticleList
{
	glm::vec3 *Positions = nullptr;
	glm::vec3 *Velocities = nullptr;
	float *Size = nullptr;
	float *Alpha = nullptr;
	float *Ages = nullptr;
	float *Lifetimes = nullptr;
};

class ParticleEffect
{
public:
	ParticleEffect();
	~ParticleEffect();

	bool Init(const std::string &textureFile, unsigned int maxParticles, unsigned int rate);

	void Update(float elapsed);
	void Render();

	void setRate(float rate);
	float getRate();
	unsigned int getCurrent();
	unsigned int getMax();

	//Public variables
	Transform transform = Transform();

	glm::vec2 RangeX = glm::vec2(-10.0f, 10.0f);
	glm::vec2 RangeY = glm::vec2(0.0f, 10.0f);
	glm::vec2 RangeZ = glm::vec2(-10.0f, 10.0f);
	glm::vec2 RangeVelocityX = glm::vec2(-1.f, 1.f);
	glm::vec2 RangeVelocityY = glm::vec2(-1.f, 1.f);
	glm::vec2 RangeVelocityZ = glm::vec2(-1.f, 1.f);
	glm::vec2 RangeVelocity = glm::vec2(0.1f, 1.0f);
	glm::vec2 RangeLifetime = glm::vec2(7.0f, 9.5f);
	//Lerp variables are dynamic based on lifetime of particle
	glm::vec2 LerpAlpha = glm::vec2(0.5f, 0.0f);
	glm::vec2 LerpSize = glm::vec2(0.0f, 1.0f);

private:
	ParticleList m_particles;
	Texture m_texture;

	float m_rate = 0.0f;
	unsigned int m_maxParticles = 0;
	unsigned int m_numCurrentParticles = 0;

	GLuint VAO = GL_NONE;
	GLuint VBO_Position = GL_NONE;
	GLuint VBO_Size = GL_NONE;
	GLuint VBO_Alpha = GL_NONE;
};

#endif