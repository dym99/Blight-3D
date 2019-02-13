#pragma once
#include "GameObject.h"
#include "P_PhysicsBody.h"

enum EnemyType
{
	RAVAGER,
	LESSER_GHOUL,
	GREATER_GHOUL
};

class Enemy : public GameObject
{
public:
	Enemy(const std::string& _name) : GameObject(_name) {}
	~Enemy();

	void setBody(P_PhysicsBody* _newBody);
	P_PhysicsBody* getBody() { return m_physics; }

	void takeDamage(float _amount) { m_health -= _amount; }

	void die();
private:
	P_PhysicsBody* m_physics;
	float m_health;
	Transform* target;
};