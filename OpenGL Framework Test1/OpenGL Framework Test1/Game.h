#ifndef __GAME_H__
#define __GAME_H__

#include "Utils.h"
#include "Scene.h"
#include "Shader.h"
#include "Interactions.h"

class Game {
public:
	Game();
	~Game();

	void initGame();

	void initGLEW();
	void initSDL();

	void update();
	void draw();

	int run();

private:
	Display *m_display;

	//TODO: Replace resources here with resource loader class

	Model *m_ravager;
	Model *m_testArea;

	Shader *m_shader;

	///////////////////////


	std::vector<Scene>  m_scenes;
	std::vector<Scene*> m_activeScenes;
};

#endif