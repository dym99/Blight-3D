#include "Utils.h"

clock_t Time::lastClock = 0L;
clock_t Time::currentClock = 0L;

float Time::time = 0.f;
float Time::deltaTime = 0.f;

void Time::reset()
{
	lastClock = clock();
	currentClock = clock();
	time = 0.f;
	deltaTime = 0.f;
}

void Time::update() {
	lastClock = currentClock;
	currentClock = clock();
	deltaTime = (currentClock - lastClock)*ONE_OVER_CLOCKS_PER_SEC;
	time += deltaTime;
}
