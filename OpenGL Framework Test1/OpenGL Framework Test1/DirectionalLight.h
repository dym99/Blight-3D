#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();

	virtual void init() override;
	virtual void update(float dt) override;

	virtual void bind() override;

	glm::vec4 direction;
};

#endif // !__DIRECTIONALLIGHT_H__
