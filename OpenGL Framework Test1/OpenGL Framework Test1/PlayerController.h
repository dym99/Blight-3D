#pragma once
#include "Behaviour.h"

#define SWORD_DUR 0.5f

enum PlayerState
{
	IDLE,
	WALK,
	SWORD,
	BULL,
	DODGE,
	FIREBALL
};

class P_PhysicsBody;

class PlayerController : public Behaviour
{
public:
	PlayerController(P_PhysicsBody* player, P_PhysicsBody* sword);
	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;
private:
	//How many times in a row has the player attacked?
	int comboNumber = 0;
	bool attacking = false;
	float attackTimer = 0.0f;
	float comboLag = 0.5;
	P_PhysicsBody *m_playerObject;
	P_PhysicsBody *m_swordHitbox;
	PlayerState m_theState;

};