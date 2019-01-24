#include "PlayerController.h"
#include <SDL2\SDL.h>
#include "Input.h"
#include "GameObject.h"
#include "Utils.h"

PlayerController::PlayerController(GameObject *_player, P_PhysicsBody *_playerBody, MouseLook * _mLook)
{
	m_playerObject = _player;

	m_playerBody = _playerBody;

	m_active = true;
	m_mLook = _mLook;
}

PlayerController::~PlayerController()
{

}

void PlayerController::start()
{
}

void PlayerController::update()
{
	//Physics-based movement
	if (Input::GetKey(KeyCode::W)) {
		m_playerBody->P_addForce((glm::vec3)(glm::rotate(glm::radians(-m_mLook->m_RotX), glm::vec3(0, 1, 0))*glm::vec4(0, 0, 16, 0)));
	}
	if (Input::GetKey(KeyCode::S)) {
		m_playerBody->P_addForce((glm::vec3)(glm::rotate(glm::radians(-m_mLook->m_RotX), glm::vec3(0, 1, 0))*glm::vec4(0, 0, -12, 0)));
	}
	if (Input::GetKey(KeyCode::A)) {
		m_playerBody->P_addForce((glm::vec3)(glm::rotate(glm::radians(-m_mLook->m_RotX), glm::vec3(0, 1, 0))*glm::vec4(12, 0, 0, 0)));
	}
	if (Input::GetKey(KeyCode::D)) {
		m_playerBody->P_addForce((glm::vec3)(glm::rotate(glm::radians(-m_mLook->m_RotX), glm::vec3(0, 1, 0))*glm::vec4(-12, 0, 0, 0)));
	}

	//Jump
	if (Input::GetKeyDown(KeyCode::Space)) {
		m_playerBody->P_velocity.y = 4.f;
	}
}

void PlayerController::render()
{
}

void PlayerController::renderTransparent()
{
}

void PlayerController::renderGUI()
{
}
