#include <Windows.h>
#include <iostream>
#include "Game.h"

#define FRAMES_PER_SECONDS		60

Game *theGame;
Display display(WINDOW_WIDTH, WINDOW_HEIGHT, "Blight3D");
bool debugFeatures = false;

//Display callback, should be top of the list
void displayCallback() {
	//Clears the display
	display.Clear(0.0f, 0.05f, 0.10f, 1.0f);
	//display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	//Draws everything to the second buffer
	theGame->Draw();
	//Swaps buffer and polls events
	display.Update();
}

void debugInteractionCallback() {
	//Right idea.... wrong format, but will work for now.
	if (theGame->modelHook.size() > 0) {
		Interact::InteractionWithScene(&theGame->modelHook, theGame->GetLights(),
										*theGame->camera, theGame->GetShaders()->size(),
											theGame->updateTimer->GetElapsedTimeSeconds(),
												display.GetWindow(),
													theGame->modelHook.at(Interact::GetModelIndex())->GetTransform());
	}
}

void keyboardInteractionCallback() {
	theGame->KeyboardUp();
	theGame->KeyboardDown();
	theGame->KeyboardPress();
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
	theGame->Update();
}

int main(int argc, char **argv) {

	theGame = new Game();
	theGame->InitGame(&debugFeatures);

	while (!display.IsClosed()) {
		
		displayCallback();
		interactionCallback();
		timerCallback();
		Input::ResetKeys();
	}

	return 0;
}