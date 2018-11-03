#ifndef __UTILS_H__
#define __UTILS_H__

#include <ctime>

#define ONE_OVER_CLOCKS_PER_SEC 1.f/(float)CLOCKS_PER_SEC;

class Time abstract {
public:
	static clock_t currentClock, lastClock;
	static float deltaTime, time;

	static void reset();
	static void update();
};

#endif
