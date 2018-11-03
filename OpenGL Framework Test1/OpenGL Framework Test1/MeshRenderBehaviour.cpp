#include "MeshRenderBehaviour.h"
#include "GameObject.h"
#include "Camera.h"

MeshRenderBehaviour::MeshRenderBehaviour(Model * _model, Shader* _shader, const bool& _transparent)
{
	//Set the model and shader handles.
	m_model = _model;
	m_shader = _shader;


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
		m_shader->update(m_parentObject->worldTransform, *Camera::mainCamera);

		m_model->Draw(m_shader);
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
