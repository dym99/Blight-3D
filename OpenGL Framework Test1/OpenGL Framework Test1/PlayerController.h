#ifndef __PLAYERCONTROLLER_BEHAVIOUR_H__
#define __PLAYERCONTROLLER_BEHAVIOUR_H__
#include "Behaviour.h"
#include "P_PhysicsBody.h"
#include "Camera.h"
#include "MouseLook.h"

class PlayerController : public Behaviour
{
public:
	PlayerController(GameObject *_player, P_PhysicsBody *_playerBody, MouseLook *_mLook);
	~PlayerController();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:
	GameObject *m_playerObject;
	P_PhysicsBody *m_playerBody;
	MouseLook *m_mLook;
};

#endif