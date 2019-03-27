#include "PlayerController.h"
#include "Input.h"
#include "P_PhysicsBody.h"
#include "Utils.h"
#include <algorithm>

//Length in seconds each attack lasts
#define SWORD_DUR 0.3f

//How much time must pass to reset the combo
#define COMBO_LAG 0.3f

#define SPEED 25.f
#define RUN_MOD 300.f


#define DT Time::deltaTime

PlayerController::PlayerController(P_PhysicsBody * player, P_PhysicsBody * sword)
{
	m_playerObject = player;
	m_swordHitbox = sword;
	m_active = true;

	m_prevLMouse = false;
}

void PlayerController::start()
{
}

void PlayerController::update()
{
	if (m_swordHitbox->getGameObject()->getParent()->getName() != "Player")
		m_playerObject->getGameObject()->addChild(m_swordHitbox->getGameObject());


	//If the player is not currently attacking
	if (m_attackTimer <= 0.0f)
	{
		if (m_timeSinceAttack <= COMBO_LAG)
			m_timeSinceAttack += DT;
		else
			left = false;

		m_attacking = false;
		m_swordHitbox->getGameObject()->localTransform.setPos(glm::vec3(0.f, -1000.f, 0.f));

		//Mouse clicked
		bool lMouse = (GetKeyState(VK_LBUTTON) & 0x100);
		if (lMouse != 0 && lMouse != m_prevLMouse )
		{
			m_attacking = true;
			m_attackTimer = SWORD_DUR;
			m_theState = SWORD;
		}
		else
		{
			m_theState = IDLE;
		}

	}
	else
	{
		if (m_timeSinceAttack <= COMBO_LAG && (m_timeSinceAttack != 0))
			left = !left;

		m_attackTimer -= DT;
		m_timeSinceAttack = 0.f;
		float completePercent = 0.0f;

		switch (m_theState)
		{
		case SWORD:
		default:
			completePercent = m_attackTimer / SWORD_DUR;

			//float _rot = m_playerObject->getTransform()->getRot().y;
			//float _X = (cos(_rot) * sin(10 * Time::time) / 2) - (sin(_rot) * 0.3f);
			//float _Z = (-sin(_rot) * sin(10 * Time::time) / 2) + (cos(_rot) * 0.3f);

			//\left(\left(1 - g\right)\cdot2\ - \ 1, \ 0.6\ \left(1 - g\right)\ \cdot\ 2\ - 0.6\right)
			float _X = (1 + (-2 * left)) * (((1 - completePercent) * 2 - 1) / 2);
			float _Y = -0.6f * (1 - completePercent) + 1;

			m_swordHitbox->getGameObject()->localTransform.setPos((glm::vec3(_X, _Y, 0.5f)));
			break;
		}
	}


	//Allow player to move and jump, when touching the ground
	bool touchGround = false;
	for (std::string _name : m_playerObject->getTriggeredNames())
	{
		if(_name == "Floor")
			touchGround = true;

		if (_name == "Enemy")
			health -= 10.f * Time::deltaTime;
	}
	float mult = Input::GetKey(KeyCode::Shift);
	float yRot = m_playerObject->getGameObject()->localTransform.getRot().y;
	glm::vec3 force = glm::vec3(0,0,0);
	if (Input::GetKey(KeyCode::W))
	{
		force +=((SPEED + (RUN_MOD * mult)) * glm::vec3(sin(yRot), 0, cos(yRot)));
	}
	if (Input::GetKey(KeyCode::S))
	{
		force += ((-SPEED - (RUN_MOD * mult)) * glm::vec3(sin(yRot), 0, cos(yRot)));
	}
	if (Input::GetKey(KeyCode::A))
	{
		force += ((SPEED + (RUN_MOD * mult)) * glm::vec3(cos(yRot), 0, -sin(yRot)));
	}
	if (Input::GetKey(KeyCode::D))
	{
		force += ((-SPEED - (RUN_MOD * mult)) * glm::vec3(cos(yRot), 0, -sin(yRot)));
	}
	if (glm::length(force) > 0.01f) {
		force = glm::normalize(force);
		m_playerObject->P_addForce(force * SPEED);
	}

	if (touchGround)
	{
		if (Input::GetKey(KeyCode::Space)) {
			m_playerObject->P_addForce(glm::vec3(0, 10 / Time::deltaTime, 0));
		}
	}

	m_prevLMouse = (GetKeyState(VK_LBUTTON) & 0x100);

		//std::cout << health << std::endl;

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
