#ifndef __GAME_H__
#define __GAME_H__

#include "Utils.h"
#include "Scene.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Display.h"
#include "Utilities.h"
#include "P_PhysicsBody.h"
#include "ParticleManager.h"
#include "UI.h"
#include "IModel.h"

class Game {
public:
	Game();
	~Game();

	void initGame();

	void initGLEW();
	void initSDL();


	void update();
	void draw();
	void GUI();

	int run();

private:
	Display *m_display;

	//TODO: Replace resources here with resource loader class

	IModel *m_ravager;
	IModel *m_testArea;
	IModel *m_brazier;
	IModel *m_bottomRoom;
	IModel *m_grove;
	IModel *m_grove2;
	IModel *m_leftRoom;
	IModel *m_rightRoom;
	IModel *m_topRoom1;
	IModel *m_topRoom2;
	IModel *m_tree;
	IModel *m_altar;

	Shader *m_shader;

	bool displayBuffers = false;

	///////////////////////

	//Framebuffers
	FrameBuffer *gBuffer;
	FrameBuffer *deferredComposite;
	FrameBuffer *workBuffer1;
	FrameBuffer *workBuffer2;
	FrameBuffer *workBuffer3;

	//Texture
	Texture *uiImage;

	std::vector<Scene>  m_scenes;
	std::vector<Scene*> m_activeScenes;

	P_PhysicsBody *ravagerPhys;
	P_PhysicsBody *floor;

	bool guiEnabled = false;
};

#endif