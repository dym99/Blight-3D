#ifndef __PARTICLEMANAGER_H__
#define __PARTICLEMANAGER_H__

#include "ParticleEffect.h"

#include <vector>

enum ParticleEffects {
	FIREPT1_PARTICLE,
	FIREPT2_PARTICLE,
	FIREPT3_PARTICLE,
	FIREPT4_PARTICLE,
	FIREPT5_PARTICLE,
	FIREPT6_PARTICLE,
	FIREPT7_PARTICLE,
	FIREPT8_PARTICLE,
	FIREPT9_PARTICLE,
	FIREPT10_PARTICLE,
	FIREPT11_PARTICLE,
	FIREPT12_PARTICLE,
	FIREPT13_PARTICLE,
	FIREPT14_PARTICLE,
	FIREPT15_PARTICLE,
	FIREPT16_PARTICLE,
	FIREPT17_PARTICLE,
	FIREPT18_PARTICLE,
	FIREPT19_PARTICLE,
	FIREPT20_PARTICLE,
	FIREPT21_PARTICLE,
	FIREPT22_PARTICLE,
	FIREPT23_PARTICLE,
	FIREPT24_PARTICLE,
	FIREPT25_PARTICLE,
	FIREPT26_PARTICLE,
	FIREPT27_PARTICLE,
	FIREPT28_PARTICLE,
	FIREPT29_PARTICLE,
	FIREPT30_PARTICLE,
	FIREPT31_PARTICLE,
	FIREPT32_PARTICLE,
	FIREPT33_PARTICLE,
	FIREPT34_PARTICLE,
	FIREPT35_PARTICLE,
	FIREPT36_PARTICLE,
	FIREPT37_PARTICLE,
	FIREPT38_PARTICLE,
	FIREPT39_PARTICLE,
	FIREPT40_PARTICLE,
	FIREPT41_PARTICLE,
	FIREPT42_PARTICLE,
	FIREPT43_PARTICLE,
	FIREPT44_PARTICLE,
	FIREPT45_PARTICLE,
	FIREPT46_PARTICLE,
	FIREPT47_PARTICLE,
	FIREPT48_PARTICLE,
	FIREPT49_PARTICLE,
	FIREPT50_PARTICLE,
	FIREPT51_PARTICLE,
	FIREPT52_PARTICLE,
	FIREPT53_PARTICLE,
	FIREPT54_PARTICLE,
	FIREPT55_PARTICLE,
	FIREPT56_PARTICLE,
	FIREPT57_PARTICLE,
	FIREPT58_PARTICLE,
	FIREPT59_PARTICLE,
	FIREPT60_PARTICLE,
	FIREPT61_PARTICLE,
	FIREPT62_PARTICLE,
	FIREPT63_PARTICLE,
	FIREPT64_PARTICLE,
	FIREPT65_PARTICLE,
	FIREPT66_PARTICLE,
	FIREPT67_PARTICLE,
	FIREPT68_PARTICLE,
	FIREPT69_PARTICLE,
	FIREPT70_PARTICLE,
	FIREPT71_PARTICLE,
	FIREPT72_PARTICLE,
	FIREPT73_PARTICLE,
	FIREPT74_PARTICLE,
	FIREPT75_PARTICLE,
	FIREPT76_PARTICLE,
	FIREPT77_PARTICLE,
	FIREPT78_PARTICLE,
	FIREPT79_PARTICLE,
	FIREPT80_PARTICLE,
	FIREPT81_PARTICLE,
	FIREPT82_PARTICLE,
	FIREPT83_PARTICLE,
	FIREPT84_PARTICLE,
	FIREPT85_PARTICLE,
	FIREPT86_PARTICLE,
	FIREPT87_PARTICLE,
	FIREPT88_PARTICLE,
	FIREPT89_PARTICLE,
	FIREPT90_PARTICLE,
	FIREPT91_PARTICLE,
	FIREPT92_PARTICLE,
	FIREPT93_PARTICLE,
	FIREPT94_PARTICLE,
	FIREPT95_PARTICLE,
	FIREPT96_PARTICLE,

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
