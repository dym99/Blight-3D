#include "MeshRenderBehaviour.h"
#include "GameObject.h"
#include "Camera.h"

MeshRenderBehaviour::MeshRenderBehaviour(Model * _model, Shader* _shader, const bool& _transparent)
{
	//Set the model and shader handles.
	m_model = _model;
	m_shader = _shader;

	m_IMDL = false;

	m_transparent = _transparent;


	m_active = true;
}

MeshRenderBehaviour::MeshRenderBehaviour(IModel * _model, Shader * _shader, const bool & _transparent)
{
	//Set the model and shader handles.
	m_iModel = _model;
	m_shader = _shader;

	m_IMDL = true;

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

	//
	//    Temporary way to make render behaviour support both Model and IModel class.
	//

	m_shader->bind();
	m_shader->update(*Camera::mainCamera);
	m_shader->sendUniform("uModel", m_parentObject->worldTransform);

	if (m_IMDL) {
		m_shader->sendUniform("colorTint", glm::vec4(1, 1, 1, 1));
		m_iModel->draw(m_shader);
	}
	else {
		m_shader->sendUniform("colorTint", m_model->colorTint);
		m_model->Draw(m_shader);
	}
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
