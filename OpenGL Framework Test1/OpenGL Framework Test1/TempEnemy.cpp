#include "TempEnemy.h"
#include "P_PhysicsBody.h"
#include "GameObject.h"

TempEnemy::TempEnemy(P_PhysicsBody * _body)
{
	m_bodyObject = _body;
	m_active = true;
}

void TempEnemy::start()
{

}

void TempEnemy::update()
{
	bool hitSword = false;
	for (std::string name : m_bodyObject->getTriggeredNames())
	{
		if (name == "Sword")
		{
			health -= 0.05f;
		}
	}

	if (health <= 0.0f)
		die();

	m_bodyObject->getGameObject()->localTransform.setScale(glm::vec3(1.f, health / 2, 1.f));
}

void TempEnemy::render()
{
}

void TempEnemy::renderTransparent()
{
}

void TempEnemy::renderGUI()
{
}

void TempEnemy::die()
{
	std::cout << "he dead boi" << std::endl;
}
