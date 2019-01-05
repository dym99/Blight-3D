#ifndef __PARTICLEMANAGER_H__
#define __PARTICLEMANAGER_H__

#include "ParticleEffect.h"

#include <vector>

enum ParticleEffects {
	SMOKEBOMB_PARTICLE,

	NUM_PARTICLES
};

class ParticleManager abstract
{
public:
	//Loads in the particle effects
	static void loadParticles();
	//Cleans up after them
	static void unloadParticles();

	//Will update all particle effects
	static void update(float dt);
	//Will only update the specific particle effect at this index
	static void update(int index, float dt);

	//Will render all particle effects
	static void render();
	//Will only render the specific particle effect at this index
	static void render(int index);

	static ParticleEffect* getParticle(int index);



private:
	static std::vector<ParticleEffect*> m_particleEffects;

};


#endif 
