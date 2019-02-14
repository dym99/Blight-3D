#include "TempEnemy.h"
#include "P_PhysicsBody.h"
#include "GameObject.h"
#include "Game.h"
#include "Enemy.h"

#define CLOSEST_RAD 1.2f

TempEnemy::TempEnemy(P_PhysicsBody * _body, Enemy * _theEnemy, GameObject* _thePlayer)
{
	m_thePlayer = _thePlayer;
	m_theEnemy = _theEnemy;
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

	glm::vec3 vectorPT = (m_thePlayer->localTransform.getPos() - m_bodyObject->getPos());
	float vectorL = sqrt((vectorPT.x * vectorPT.x) + (vectorPT.y * vectorPT.y) + (vectorPT.z * vectorPT.z));
	if (vectorL > CLOSEST_RAD)
	{
		vectorPT.y *= 0;
		m_bodyObject->P_addForce(vectorPT / (vectorL / 50));
	}

	//m_bodyObject->getGameObject()->localTransform.setScale(glm::vec3(1.f, health / 2, 1.f));

	if (health <= 0.0f)
		die();
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
	Game::killEnemy(m_theEnemy);
}
