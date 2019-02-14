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
#include "Enemy.h"

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

	void spawnEnemy(EnemyType _type, glm::vec3 _location);
	static void killEnemy(Enemy* _toKill);

private:
	Display *m_display;

	//TODO: Replace resources here with resource loader class

	Model *m_ravager;
	Model *m_testArea;
	Model *m_brazier;
	Model *m_bottomRoom;
	Model *m_grove;
	Model *m_grove2;
	Model *m_leftRoom;
	Model *m_rightRoom;
	Model *m_topRoom1;
	Model *m_topRoom2;
	Model *m_tree;
	Model *m_altar;

	Model *m_box;

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