#ifndef __GAME_H__
#define __GAME_H__

#include "Utils.h"
#include "Scene.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Display.h"
#include "Utilities.h"
#include "P_PhysicsBody.h"

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

	Model *m_playerModel;
	Model *m_ravagerModel;
	Model *m_testArea;

	Shader *m_shader;

	///////////////////////

	//Framebuffers
	FrameBuffer *mainBuffer;
	FrameBuffer *workBuffer1;
	FrameBuffer *workBuffer2;
	FrameBuffer *workBuffer3;

	//Textures
	Texture *uiImage;

	std::vector<Scene>  m_scenes;
	std::vector<Scene*> m_activeScenes;

	P_PhysicsBody *ravagerPhys;
};

#endif