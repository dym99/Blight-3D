#include "PointLight.h"

PointLight::PointLight() : Light()
{
}

PointLight::PointLight(Model * sphere) : Light()
{
	m_sphere = sphere;
}

PointLight::~PointLight()
{
}

void PointLight::init()
{
	_UBO.allocateMemory(sizeof(glm::vec4) * 3);
}

void PointLight::update(float dt)
{
	calculateRadius();
	m_sphere->GetTransform()->getPos() = position;
	_UBO.sendData(&color, sizeof(glm::vec4) * 3, 0);
}

void PointLight::bind()
{
	_UBO.bind(2);
}

void PointLight::draw(Shader * shader)
{
	m_sphere->GetTransform()->setScale(glm::vec3(radius, radius, radius));

	shader->update(*Camera::mainCamera);
	shader->sendUniform("uModel", m_sphere->GetTransform()->getModel());

	m_sphere->Draw(shader);
}

float PointLight::calculateRadius()
{
	float luminance = glm::dot((glm::vec3(color) / color.w), glm::vec3(0.3f, 0.59f, 0.11f));
	float luminanceMin = 0.05f;
	radius = (-linearAttentuation + sqrtf(linearAttentuation * linearAttentuation - 4.0f * quadraticAttentuation * (constantAttenuation - luminance / luminanceMin))) / (2.0f * quadraticAttentuation);
	return radius;
}
