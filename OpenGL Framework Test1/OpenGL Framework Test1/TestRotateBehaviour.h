#ifndef __TESTROTATE_BEHAVIOUR_H__
#define __TESTROTATE_BEHAVIOUR_H__

#include "Behaviour.h"
#include "Model.h"

class TestRotateBehaviour : public Behaviour {
public:
	TestRotateBehaviour();
	~TestRotateBehaviour();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:
};
#endif
