#ifndef __MOUSELOOK_BEHAVIOUR_H__
#define __MOUSELOOK_BEHAVIOUR_H__
#include "Behaviour.h"
#include "Camera.h"
class MouseLook : public Behaviour
{
public:
	MouseLook(GameObject *_player);
	~MouseLook();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

	inline GameObject& getPlayerObject() { return *m_playerObject; }

private:
	float m_distance, m_RotX, m_RotY;
	GameObject *m_playerObject;
};

#endif