#include "MouseLook.h"
#include <SDL2\SDL.h>
#include "Input.h"
#include "GameObject.h"
#include "Utils.h"

MouseLook::MouseLook(GameObject *_player)
{
	m_playerObject = _player;
	m_RotX = 0.f;
	m_RotY = 0.f;
	m_distance = 3.f;


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

	if (Input::GetKey(KeyCode::W)) {
		m_playerObject->localTransform.setPos(m_playerObject->localTransform.getPos() + (glm::vec3)(glm::rotate(glm::radians(-m_RotX), glm::vec3(0, 1, 0))*glm::vec4(0, 0, 4, 0))*Time::deltaTime);
	}
	if (Input::GetKey(KeyCode::S)) {
		m_playerObject->localTransform.setPos(m_playerObject->localTransform.getPos() + (glm::vec3)(glm::rotate(glm::radians(-m_RotX), glm::vec3(0, 1, 0))*glm::vec4(0, 0, -4, 0))*Time::deltaTime);
	}
	if (Input::GetKey(KeyCode::A)) {
		m_playerObject->localTransform.setPos(m_playerObject->localTransform.getPos() + (glm::vec3)(glm::rotate(glm::radians(-m_RotX), glm::vec3(0, 1, 0))*glm::vec4(2, 0, 0, 0))*Time::deltaTime);
	}
	if (Input::GetKey(KeyCode::D)) {
		m_playerObject->localTransform.setPos(m_playerObject->localTransform.getPos() + (glm::vec3)(glm::rotate(glm::radians(-m_RotX), glm::vec3(0, 1, 0))*glm::vec4(-2, 0, 0, 0))*Time::deltaTime);
	}
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
