#include "Light.h"
#include <iostream>

Light::Light()
{
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	position = glm::vec4(0.0f);
	constantAttenuation = 1.0f;
	linearAttentuation = 0.1f;
	quadraticAttentuation = 0.01f;
}

Light::~Light()
{
	_UBO.unload();
}
