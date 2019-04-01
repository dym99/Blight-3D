#ifndef __GAME_H__
#define __GAME_H__

#include "Utils.h"
#include "Scene.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "GBuffer.h"
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
#include "MeshRenderBehaviour.h"
#include "Graph.h"

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

	Node* getClosestToLogun();

private:
	Display *m_display;

	float totalGameTime = 0.f;

	//TODO: Replace resources here with resource loader class

	IModel *m_ravager;
	IModel *m_testArea;
	IModel *m_brazier;

	IModel *m_level;
	IModel *m_acid;

	Model *m_box;

	AnimatedModel *m_logunWalk, *m_logunWalkSword;
	AnimatedModel *m_logunSwingA, *m_logunSwingASword;

	MeshRenderBehaviour *m_logunRenderer, *m_swordRenderer;

	bool m_logunAttacking = false;

	Shader *m_shader;
	
	Graph* m_AIGraph;

	Node* closestToLogun;

	bool displayBuffers = false;
	bool displayBloom = true;

	///////////////////////

	//Framebuffers
	GBuffer *gBuffer;
	PostBuffer *deferredComposite;
	BloomBuffer *bloomBuffer;
	FrameBuffer *edgeBuffer;
	/*FrameBuffer *workBuffer1;
	FrameBuffer *workBuffer2;
	FrameBuffer *workBuffer3;*/

	//Texture
	Texture *uiImage;
	Texture *toonRamp;
	LUT3D *colorCorrection;

	std::vector<Scene>  m_scenes;
	std::vector<Scene*> m_activeScenes;

	P_PhysicsBody *playerPhys;
	P_PhysicsBody *hitBox;
	P_PhysicsBody *floor;

	GameObject* player;
	GameObject* playerModel;
	GameObject* playerLoc;
	GameObject* cameraPivot;
	GameObject* deadLogun;
	GameObject* healthShower;

	bool guiEnabled = false;

	bool greyScaleEnabled = false;
	bool sepiaEnabled = false;

	static std::vector<Enemy*> enemies;
	static std::vector<P_PhysicsBody*> enemyBodies;

	float m_playerModelAngle;

	static int m_score;
};

#endif