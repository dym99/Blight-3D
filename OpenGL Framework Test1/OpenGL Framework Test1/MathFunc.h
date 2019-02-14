#ifndef __MATHFUNC_H__
#define __MATHFUNC_H__

#include <glm/glm.hpp>

template <typename T>
T Lerp(T val1, T val2, float lerpParam);

float MagnitudeSquared(glm::vec3 vector);


//Random stuffs
void SeedRandomNumberGenerator();
void SeedRandomNumberGenerator(unsigned int seed);

float RandomRangef(float min, float max);
int RandomRangei(int min, int max);

template<typename T>
inline T Lerp(T val1, T val2, float lerpParam)
{
	return (1 - lerpParam) * val1 + lerpParam * val2;
};

#endif

