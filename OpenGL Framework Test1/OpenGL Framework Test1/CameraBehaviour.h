#ifndef __CAMERA_BEHAVIOUR_H__
#define __CAMERA_BEHAVIOUR_H__

#include "Behaviour.h"
#include <glm/glm.hpp>
#include "GameObject.h"

class CameraBehaviour : public Behaviour
{
public:
	CameraBehaviour();
	~CameraBehaviour();

	//Behaviour Overrides
	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:

};

#endif