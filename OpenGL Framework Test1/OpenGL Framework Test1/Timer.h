#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL2/SDL.h>
#include <time.h>

//Keeps track of elapsed time
class Timer {
public:
	Timer() {
		previousTime = SDL_GetTicks();
		this->Tick();
	}

	~Timer() {}

	float Tick() {
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		return elapsedTime;
	}

	float GetElapsedTimeTicks() {
		return elapsedTime;
	}

	float GetElapsedTimeSeconds() {
		return elapsedTime / CLOCKS_PER_SEC;
	}

	float GetTimeCurrent() {
		return currentTime;
	}

private:
	float currentTime, previousTime, elapsedTime;
};

#endif // !__TIMER_H__

