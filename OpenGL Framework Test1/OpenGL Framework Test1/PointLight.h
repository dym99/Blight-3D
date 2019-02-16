#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	~PointLight();

	virtual void init() override;
	virtual void update(float dt) override;

	virtual void bind() override;

	float calculateRadius();
};

#endif // !__POINTLIGHT_H__