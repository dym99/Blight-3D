#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "UniformBuffer.h"


class Light
{
public:
	Light();
	~Light();

	virtual void init()=0;
	virtual void update(float dt)=0;

	virtual void bind()=0;

	glm::vec4 color;
	glm::vec4 position;

	float constantAttenuation;
	float linearAttentuation;
	float quadraticAttentuation;
	float radius = 0.f;

	UniformBuffer _UBO;
};

#endif // !__LIGHT_H__
