#ifndef __PARTICLERENDERBEHAVIOUR_H__
#define __PARTICLERENDERBEHAVIOUR_H__

#include "ParticleEffect.h"
#include "Behaviour.h"
#include "Shader.h"

class ParticleRenderBehaviour : public Behaviour 
{
public:
	ParticleRenderBehaviour(ParticleEffect* _oarticle, Shader* _shader);
	~ParticleRenderBehaviour();

	void start() override;
	void update() override;
	void render() override;
	void renderTransparent() override;
	void renderGUI() override;

private:
	ParticleEffect* m_particle;
	Shader* m_shader;
};

#endif // !__PARTICLERENDERBEHAVIOUR_H__

