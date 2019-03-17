#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(Model* sphere);
	~PointLight();

	virtual void init() override;
	virtual void update(float dt) override;

	virtual void bind() override;
	
	virtual void draw(Shader* shader) override;

	float calculateRadius();

private:
	Model *m_sphere;
};

#endif // !__POINTLIGHT_H__