#include <Windows.h>
#include <iostream>
#include "Game.h"

#define WINDOW_HEIGHT			600
#define WINDOW_WIDTH			800
#define FRAMES_PER_SECONDS		60

Game *theGame;
Display display(WINDOW_WIDTH, WINDOW_HEIGHT, "Blight3D");
bool debugFeatures = false;

//Display callback, should be top of the list
void displayCallback() {
	//Clears the display
	display.clear(0.0f, 0.05f, 0.10f, 1.0f);
	//Draws everything to the second buffer
	theGame->draw();
	//Swaps buffer and polls events
	display.update();
}

void debugInteractionCallback() {
	//Right idea.... wrong format, but will work for now.
	if (theGame->getEnemies()->size() > 0) {
		Interact::interactionWithScene(&theGame->modelHook, theGame->getLights(),
										*theGame->camera, theGame->getShaders()->size(),
											theGame->updateTimer->getElapsedTimeSeconds(),
												display.getWindow(),
													theGame->modelHook.at(Interact::GetModelIndex())->GetTransform());
	}
}

void keyboardInteractionCallback() {
	theGame->keyboardUp();
	theGame->keyboardDown();
	theGame->keyboardPress();
}

void mouseInteractionCallback() {

}


//Interactions callback, should happen in between
void interactionCallback() {
	
	if (debugFeatures) {
		debugInteractionCallback();
	}
	keyboardInteractionCallback();
	mouseInteractionCallback();
	//Resets mouse input
	SDL_GetRelativeMouseState(NULL, NULL);
}


//Update callback, should be bottom of the list 
void timerCallback() {
	//Updates the game
	theGame->update();
}

int main(int argc, char **argv) {

	theGame = new Game();
	theGame->initGame(&debugFeatures);

	while (!display.isClosed()) {
		
		displayCallback();
		interactionCallback();
		timerCallback();
		Input::ResetKeys();
	}

	return 0;
}