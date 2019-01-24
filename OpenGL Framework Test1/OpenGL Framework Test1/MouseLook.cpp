#include "MouseLook.h"
#include <SDL2\SDL.h>
#include "Input.h"
#include "GameObject.h"
#include "Utils.h"

MouseLook::MouseLook(GameObject *_player, P_PhysicsBody *_playerBody)
{
	m_playerObject = _player;
	m_RotX = 0.f;
	m_RotY = 0.f;
	m_distance = 3.f;

	m_playerBody = _playerBody;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	m_active = true;
}

MouseLook::~MouseLook()
{
}

void MouseLook::start()
{
}

void MouseLook::update()
{
	int mouseRelX, mouseRelY;
	SDL_GetRelativeMouseState(&mouseRelX, &mouseRelY);

	m_RotX += ((float)mouseRelX)*0.1f;

	m_RotY += ((float)mouseRelY)*0.1f;

	if (m_RotY > 80.f) m_RotY = 80.f;
	if (m_RotY < 0) m_RotY = 0;

	
	m_parentObject->localTransform.setRot(glm::vec3(glm::radians(-m_RotY), glm::radians(180.f), 0));
	m_playerObject->localTransform.setRot(glm::vec3(0, glm::radians(-m_RotX), 0));
}

void MouseLook::render()
{
}

void MouseLook::renderTransparent()
{
}

void MouseLook::renderGUI()
{
}
