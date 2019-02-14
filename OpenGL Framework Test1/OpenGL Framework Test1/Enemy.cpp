#include "Enemy.h"

Enemy::~Enemy()
{
	if (m_physics != nullptr)
		delete m_physics;
}

void Enemy::setBody(P_PhysicsBody * _newBody)
{
	if (m_physics != nullptr)
		delete m_physics;
	m_physics = _newBody;
}

void Enemy::die()
{

}
