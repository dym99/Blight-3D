#ifndef __ATTACHBEHAVIOUR_H__
#define __ATTACHBEHAVIOUR_H__

#include "Behaviour.h"
#include "P_PhysicsBody.h"

class AttachBehaviour : public Behaviour {
public:
	AttachBehaviour(GameObject* _attachedTo);
	~AttachBehaviour();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:
	GameObject *m_attached;
};
#endif
