#include <Windows.h>
#include <iostream>
#include "Game.h"


int main(int argc, char **argv) {
	Game game;

	game.initGame();
	
	return game.run();
}