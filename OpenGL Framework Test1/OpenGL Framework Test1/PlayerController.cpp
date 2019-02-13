#include "PlayerController.h"
#include "Input.h"
#include "P_PhysicsBody.h"
#include "Utils.h"

PlayerController::PlayerController(P_PhysicsBody * player, P_PhysicsBody * sword)
{
	m_playerObject = player;
	m_swordHitbox = sword;
	m_active = true;
}

void PlayerController::start()
{
}

void PlayerController::update()
{
	//Mouse clicked
	if (attackTimer <= 0.0f)
	{
		attacking = false;
		m_swordHitbox->getGameObject()->localTransform.setPos(glm::vec3(0.f, -1000.f, 0.f));

		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		{
			attacking = true;
			attackTimer = SWORD_DUR;
			m_theState = SWORD;
		}
		else
		{
			m_theState = IDLE;
		}

	}
	else
	{
		attackTimer -= Time::deltaTime;
		float completePercent = 0.0f;

		switch (m_theState)
		{
		case SWORD:
		default:
			completePercent = attackTimer / SWORD_DUR;
			break;
		}
		//float _rot = m_playerObject->getTransform()->getRot().y;
		//float _X = (cos(_rot) * sin(10 * Time::time) / 2) - (sin(_rot) * 0.3f);
		//float _Z = (-sin(_rot) * sin(10 * Time::time) / 2) + (cos(_rot) * 0.3f);

		//\left(\left(1 - g\right)\cdot2\ - \ 1, \ 0.6\ \left(1 - g\right)\ \cdot\ 2\ - 0.6\right)
		float _X = ((1 - completePercent) * 2 - 1) / 2;
		float _Y = -0.6f * (1 - completePercent) + 1;

		m_swordHitbox->getGameObject()->localTransform.setPos((glm::vec3(_X, _Y, 0.5f)));
	}


	//Allow player to move and jump, when touching the ground
	bool touchGround = false;
	for (std::string _name : m_playerObject->getTriggeredNames())
	{
		if (_name == "Floor")
			touchGround = true;
	}
	if (touchGround)
	{
		float mult = Input::GetKey(KeyCode::Shift);
		float yRot = m_playerObject->getGameObject()->localTransform.getRot().y;
		if (Input::GetKey(KeyCode::W))
		{
			m_playerObject->P_addForce((15.f + (20.f * mult)) * glm::vec3(sin(yRot), 0, cos(yRot)));
		}
		if (Input::GetKey(KeyCode::S))
		{
			m_playerObject->P_addForce((-15.f - (20.f * mult)) * glm::vec3(sin(yRot), 0, cos(yRot)));
		}
		if (Input::GetKey(KeyCode::A))
		{
			m_playerObject->P_addForce((15.f + (20.f * mult)) * glm::vec3(cos(yRot), 0, -sin(yRot)));
		}
		if (Input::GetKey(KeyCode::D))
		{
			m_playerObject->P_addForce((-15.f - (20.f * mult)) * glm::vec3(cos(yRot), 0, -sin(yRot)));
		}

		//Remove this when done testing. Or use as a jump for testing purposes.
		if (Input::GetKey(KeyCode::Space)) {
			m_playerObject->P_addForce(glm::vec3(0, 3 / Time::deltaTime, 0));
		}
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
