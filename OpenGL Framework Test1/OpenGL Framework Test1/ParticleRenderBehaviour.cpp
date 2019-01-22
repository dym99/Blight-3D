#include "ParticleRenderBehaviour.h"

ParticleRenderBehaviour::ParticleRenderBehaviour(ParticleEffect * _particle, Shader * _shader)
{
}

ParticleRenderBehaviour::~ParticleRenderBehaviour()
{
}

void ParticleRenderBehaviour::start()
{
	//Intentionally empty
}

void ParticleRenderBehaviour::update()
{
	//intentionally empty
}

void ParticleRenderBehaviour::render()
{
	//intentionally empty
}

void ParticleRenderBehaviour::renderTransparent()
{
	m_shader->bind();
	m_shader->sendUniform("uTex", 0);
	m_shader->sendUniform("uModel", m_particle->transform.getModel());
	m_particle->Render();
	m_shader->unbind();
}

void ParticleRenderBehaviour::renderGUI()
{
	//intentionally empty
}
