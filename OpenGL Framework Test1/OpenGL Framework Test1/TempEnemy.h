#pragma once
#include "Behaviour.h"

class P_PhysicsBody;
class GameObject;

class TempEnemy : public Behaviour
{
public:
	TempEnemy(P_PhysicsBody* _body);
	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

	void die();
	void respawn();
private:
	//How many times in a row has the player attacked?
	float health = 10.f;
	P_PhysicsBody *m_bodyObject;
};
