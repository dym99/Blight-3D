#pragma once
#include "Behaviour.h"

#define MAX_HEALTH 100.f

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
	float health = MAX_HEALTH;
	float healthLerp = MAX_HEALTH;
	float healthYellow = MAX_HEALTH;
	float tVal = 0.f;

	inline PlayerState getState() { return m_theState; }
	inline bool isWalking() { return m_walking; }

	inline void setPlayerRotation(float _rot) { m_playerRotation = _rot; }
private:

	//How many times in a row has the player attacked?
	int m_comboNumber = 0;

	float m_playerRotation = 0.f;

	//Is the player currently mid-attack?
	bool m_attacking = false;
	bool m_walking = false;
	
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

	//stupid variable to make stuff more bad :)
	float m_hurtDelay = 0.f;
};