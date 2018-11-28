#include "CameraBehaviour.h"
#include "Camera.h"
#include "GameObject.h"



CameraBehaviour::CameraBehaviour()
{
}

CameraBehaviour::~CameraBehaviour()
{
}

void CameraBehaviour::start()
{
}

void CameraBehaviour::update()
{
	Camera::mainCamera->setPos(m_parentObject->worldTransform*glm::vec4(0,0,0,0));
}

void CameraBehaviour::render()
{
}

void CameraBehaviour::renderTransparent()
{
}

void CameraBehaviour::renderGUI()
{
}