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

	int run();

private:
	Display *m_display;

	//TODO: Replace resources here with resource loader class

	Model *m_ravager;
	Model *m_testArea;
	Model *m_brazier;

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

	P_PhysicsBody *playerPhys;

	IModel m_ravagerModel;
	Texture m_ravagerAlbedo;


	IModel m_logunModel;
	Texture m_logunAlbedo;
	//Texture TexEmmisive;
};

#endif