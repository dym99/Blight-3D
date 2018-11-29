#pragma once
#include <glm/glm.hpp>

template <typename T>
T Lerp(T val1, T val2, float lerpParam);

float MagnitudeSquared(glm::vec3 vector);

template<typename T>
inline T Lerp(T val1, T val2, float lerpParam)
{
	return (1 - lerpParam) * val1 + lerpParam * val2;
};