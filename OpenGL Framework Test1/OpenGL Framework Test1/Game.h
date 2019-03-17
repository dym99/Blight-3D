#ifndef __GAME_H__
#define __GAME_H__

#include "Utils.h"
#include "Scene.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "GBuffer.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "PostBuffer.h"
#include "BloomBuffer.h"
#include "Display.h"
#include "Utilities.h"
#include "P_PhysicsBody.h"
#include "ParticleManager.h"
#include "UI.h"
#include "IModel.h"
#include "Enemy.h"
#include "LUT.h"
#include "AnimatedModel.h"


class Game {
public:
	Game();
	~Game();

	void initGame();

	void initGLEW();
	void initSDL();

	//void resizeWindow(int w, int h);

	void update();
	void draw();
	void GUI();

	int run();

	void spawnEnemy(EnemyType _type, glm::vec3 _location);
	static void killEnemy(Enemy* _toKill);

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

	Model *m_box;
	Model *m_sphere;

	AnimatedModel *m_ravagerIdle;

	Shader *m_shader;


	bool displayBuffers = false;
	bool displayBloom = false;

	///////////////////////

	//Framebuffers
	GBuffer *gBuffer;
	PostBuffer *deferredComposite;
	PostBuffer *compositeBuffer;
	BloomBuffer *bloomBuffer;
	BloomBuffer *bloomBuffer2;
	BloomBuffer *bloomBuffer3;
	FrameBuffer *edgeBuffer;
	FrameBuffer *lightingBuffer;
	/*FrameBuffer *workBuffer1;
	FrameBuffer *workBuffer2;
	FrameBuffer *workBuffer3;*/
	
	//Texture
	Texture *uiImage;
	Texture *toonRamp;
	LUT3D *colorCorrection;

	std::vector<Scene>  m_scenes;
	std::vector<Scene*> m_activeScenes;

	std::vector<PointLight> m_lights;

	P_PhysicsBody *ravagerPhys;
	P_PhysicsBody *hitBox;
	P_PhysicsBody *floor;

	GameObject* player;
	GameObject* playerLoc;
	GameObject* cameraPivot;

	bool guiEnabled = false;

	static std::vector<Enemy*> enemies;
	static std::vector<P_PhysicsBody*> enemyBodies;
};

#endif