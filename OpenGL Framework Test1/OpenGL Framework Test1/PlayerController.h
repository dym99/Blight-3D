#pragma once
#include "Behaviour.h"

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
	float health;

	//How many times in a row has the player attacked?
	int m_comboNumber = 0;

	//Is the player currently mid-attack?
	bool m_attacking = false;
	
	//How much time is left in the current action?
	float m_attackTimer = 0.0f;
	float m_timeSinceAttack = 0.0f;
	bool left = false;

	//Objects that make up the player
	P_PhysicsBody *m_playerObject;
	P_PhysicsBody *m_swordHitbox;

	//Current action the player is performing
	PlayerState m_theState;

	//Button state
	bool m_prevLMouse;
};