#ifndef __MOUSELOOK_BEHAVIOUR_H__
#define __MOUSELOOK_BEHAVIOUR_H__
#include "Behaviour.h"
#include "P_PhysicsBody.h"
#include "Camera.h"
class MouseLook : public Behaviour
{
public:
	friend class PlayerController;
	MouseLook(GameObject *_player, P_PhysicsBody *_playerBody);
	~MouseLook();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:
	float m_distance, m_RotX, m_RotY;
	GameObject *m_playerObject;
	P_PhysicsBody *m_playerBody;
};

#endif