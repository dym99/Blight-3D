#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec4(0.f, -1.f, 0.f, 0.f);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::init()
{
	_UBO.allocateMemory(sizeof(glm::vec4) * 4);
}

void DirectionalLight::update(float dt)
{
	_UBO.sendVector(color, 0);
	_UBO.sendVector(position, sizeof(glm::vec4));
	_UBO.sendVector(direction, sizeof(glm::vec4) * 2);
	_UBO.sendVector(glm::vec4(constantAttenuation, linearAttentuation, quadraticAttentuation, radius), sizeof(glm::vec4) * 3);
}

void DirectionalLight::bind()
{
	_UBO.bind(3);
}
