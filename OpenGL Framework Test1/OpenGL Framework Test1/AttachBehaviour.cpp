#include "MeshRenderBehaviour.h"
#include "GameObject.h"
#include "Camera.h"
#include "AttachBehaviour.h"



AttachBehaviour::AttachBehaviour(GameObject * _attachedTo)
{
	m_attached = _attachedTo;
}

AttachBehaviour::~AttachBehaviour()
{
	m_attached = nullptr;
}

void AttachBehaviour::start()
{
}

void AttachBehaviour::update()
{
	m_parentObject->localTransform.setPos(m_attached->localTransform.getPos());
}

void AttachBehaviour::render()
{
}

void AttachBehaviour::renderTransparent()
{
}

void AttachBehaviour::renderGUI()
{
}
