#include "MeshRenderBehaviour.h"
#include "GameObject.h"
#include "Camera.h"
#include "Utils.h"

MeshRenderBehaviour::MeshRenderBehaviour(Model * _model, Shader* _shader, bool morph, const bool& _transparent)
{
	//Set the model and shader handles.
	m_model = _model;
	m_shader = _shader;
	m_morph = morph;

	m_transparent = _transparent;

	m_active = true;
}

MeshRenderBehaviour::~MeshRenderBehaviour()
{
	//Upon deleting this behaviour, clear the model handle.
	//Do not delete m_model here, as it is a shared resource, and will be deleted elsewhere.
	m_model = nullptr;

	//Reset tranparency variable to avoid any potential graphical errors.
	m_transparent = false;
}

void MeshRenderBehaviour::start()
{
	//Intentionally empty
}

void MeshRenderBehaviour::update()
{
	//Intentionally empty
}

void MeshRenderBehaviour::render()
{
	//Only render here if opaque.
	//if (!m_transparent) {
		m_shader->bind();
		m_shader->update(*Camera::mainCamera);
		m_shader->sendUniform("uModel", m_parentObject->worldTransform);

		m_model->meshes[0]->update(Time::deltaTime);

		m_model->Draw(m_shader, m_morph);
	//}
}

void MeshRenderBehaviour::renderTransparent()
{
	//Intentionally empty
}

void MeshRenderBehaviour::renderGUI()
{
	//Intentionally empty
}
