#include "Game.h"
#include <iostream>

#include "AnimatedModel.h"
#include "ShaderManager.h"
#include "MeshRenderBehaviour.h"
#include "TestRotateBehaviour.h"
#include "MouseLook.h"
#include "CameraBehaviour.h"
#include "AudioPlayer.h"
#include "PlayerController.h"
#include "TempEnemy.h"

#include "Input.h"

#ifndef _DEBUG
#define _DEBUG 0
#endif

std::vector<Enemy*> Game::enemies;
std::vector<P_PhysicsBody*> Game::enemyBodies;

Game::Game()
{
}

Game::~Game()
{
	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i] = nullptr;
	}
	m_activeScenes.clear();

	if (uiImage != nullptr)
		delete uiImage;
	uiImage = nullptr;
	if (toonRamp != nullptr)
		delete toonRamp;
	toonRamp = nullptr;

	if (gBuffer != nullptr)
		delete gBuffer;
	gBuffer = nullptr;
	if (deferredComposite != nullptr)
		delete deferredComposite;
	deferredComposite = nullptr;
	if (edgeBuffer != nullptr)
		delete edgeBuffer;
	edgeBuffer = nullptr;
}

void Game::initGame()
{
	///Initialise SDL
	initSDL();

	///Initialise the display
	m_display = new Display("Blight");

	///Initialise GLEW
	initGLEW();

	UI::InitImGUI();

	//Initialise Framebuffers
	gBuffer = new GBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
	deferredComposite = new PostBuffer;
	bloomBuffer = new BloomBuffer;
	edgeBuffer = new FrameBuffer(1);

	uiImage = new Texture();
	uiImage->load("./Resources/Textures/UIpost.png");
	toonRamp = new Texture();
	toonRamp->load("./Resources/Textures/ToonRamp.png");
	colorCorrection = new LUT3D("Blight_Lut.cube");

	//Initializes the screen quad
	FrameBuffer::initFSQ();

	//Initializes the audio player and sets it up
	AudioPlayer::init(100, FMOD_INIT_NORMAL);
	AudioPlayer::set3DSettings(1.0f, 1.0f);

	//Initialise Camera
	auto camera = new Camera();
	camera->Perspective(70.f, 16.f/9.f, 0.001f, 1000.f);
	camera->setPos(glm::vec3(0.f, 0.f, 3.0f));

	Camera::mainCamera = camera;

	//Load in resources
	m_ravager = new IModel();
	m_ravager->loadFromFile("RavagerIdle0.imdl", "./Resources/Objects/Ravager/Anims/");
	//m_ravager->colorTint = glm::vec3(1.f, 1.f, 1.f);

	Texture *ravagerAlbedo = new Texture("diffuseTex");
	ravagerAlbedo->load("./Resources/Objects/Ravager/albedo.png");
	m_ravager->setAlbedo(ravagerAlbedo);

	m_brazier = new IModel();
	m_brazier->loadFromFile("Brazier.imdl", "./Resources/Objects/Brazier/");

	Texture* brazierAlbedo = new Texture("diffuseTex");
	brazierAlbedo->load("./Resources/Objects/Brazier/BrazierBasic.png");
	m_brazier->setAlbedo(brazierAlbedo);

	m_bottomRoom = new IModel();
	m_bottomRoom->loadFromFile("MapBottom.imdl", "./Resources/Objects/MainLevel/");
	m_grove = new IModel();
	m_grove->loadFromFile("MarshFinal.imdl", "./Resources/Objects/MainLevel/");
	m_leftRoom = new IModel();
	m_leftRoom->loadFromFile("MapLeft.imdl", "./Resources/Objects/MainLevel/");
	m_rightRoom = new IModel();
	m_rightRoom->loadFromFile("MapRight.imdl", "./Resources/Objects/MainLevel/");
	m_topRoom1 = new IModel();
	m_topRoom1->loadFromFile("MapTop2.imdl", "./Resources/Objects/MainLevel/");
	m_topRoom2 = new IModel();
	m_topRoom2->loadFromFile("MapTop1.imdl", "./Resources/Objects/MainLevel/");
	m_tree = new IModel();
	m_tree->loadFromFile("Tree.imdl", "./Resources/Objects/MainLevel/");
	m_altar = new IModel();
	m_altar->loadFromFile("SkullAltar.imdl", "./Resources/Objects/MainLevel/");
	m_box = new Model();
	m_box->LoadFromFile("./Resources/Objects/Box/", "cube");

	Texture *roomTex = new Texture("diffuseTex");
	roomTex->load("./Resources/Objects/MainLevel/BlightLevelTexturesOne.png");
	Texture *blankEmissive = new Texture("emissiveTex");
	blankEmissive->load("./Resources/Objects/MainLevel/BlightLevelTexturesEmissive.png");
	Texture *testEmissive = new Texture("emissiveTex");
	testEmissive->load("./Resources/Objects/Box/face_emis.png");

	m_ravagerIdle = new AnimatedModel();
	m_ravagerIdle->loadFromFiles(6, "RavagerIdle", "Resources/Objects/Ravager/Anims/");

	m_ravagerIdle->setAlbedo(ravagerAlbedo);
	m_ravagerIdle->setEmissive(blankEmissive);
	for (int i = 0; i < 6; ++i) {
		m_ravagerIdle->setFrameTime(i, 0.8333f);
	}


	m_brazier->setEmissive(blankEmissive);
	m_ravager->setEmissive(blankEmissive);
	m_bottomRoom->setAlbedo(roomTex);
	m_bottomRoom->setEmissive(blankEmissive);
	m_grove->setAlbedo(roomTex);
	m_grove->setEmissive(blankEmissive);
	m_leftRoom->setAlbedo(roomTex);
	m_leftRoom->setEmissive(blankEmissive);
	m_rightRoom->setAlbedo(roomTex);
	m_rightRoom->setEmissive(blankEmissive);
	m_topRoom1->setAlbedo(roomTex);
	m_topRoom1->setEmissive(blankEmissive);
	m_topRoom2->setAlbedo(roomTex);
	m_topRoom2->setEmissive(blankEmissive);
	m_tree->setAlbedo(roomTex);
	m_tree->setEmissive(testEmissive);
	m_altar->setAlbedo(roomTex);
	m_altar->setEmissive(blankEmissive);

	
	ShaderManager::loadShaders();

	ParticleManager::loadParticles();

	//Frame Buffers
#pragma region FrameBuffers
	deferredComposite->init(WINDOW_WIDTH, WINDOW_HEIGHT);

	bloomBuffer->init(WINDOW_WIDTH, WINDOW_HEIGHT, 2.f);

	edgeBuffer->initDepthTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	edgeBuffer->initColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

	if (!edgeBuffer->checkFBO()) {
		std::cout << "Edge buffer failed to load.\n\n";
		system("pause");
		exit(0);
	}
#pragma endregion

	//Set up the test Scene

	player = new GameObject("Ravager");
	player->addBehaviour(new MeshRenderBehaviour(m_ravagerIdle, ShaderManager::getShader(GBUFFER_MORPH)));
	//player->addBehaviour(new MeshRenderBehaviour(m_ravager, ShaderManager::getShader(GBUFFER_SHADER)));
	if (_DEBUG)
		player->localTransform.setPos(glm::vec3(0.f, 25.f, 0.f));

	cameraPivot = new GameObject("CameraPivot");
	cameraPivot->localTransform.setPos(glm::vec3(0.f,1.f,0.f));
	cameraPivot->addBehaviour(new MouseLook(player));

	auto cameraObject = new GameObject("Camera");

	cameraObject->localTransform.setPos(glm::vec3(0, 0, 3.f));

	camera->setTransform(&cameraObject->worldTransform);

	cameraPivot->addChild(cameraObject);
	player->addChild(cameraPivot);
	
#pragma region braziers
	auto brazier = new GameObject("brazier");
	brazier->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier->localTransform.setPos(glm::vec3(-44.633648f, 0.500000f, 5.672839f));
	brazier->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	
	auto brazier2 = new GameObject("brazier");
	brazier2->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier2->localTransform.setPos(glm::vec3(-44.090328, 0.500000, -6.341741));
	brazier2->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier3 = new GameObject("brazier");
	brazier3->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier3->localTransform.setPos(glm::vec3(-26.775608, 0.500000, 9.505545));
	brazier3->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier4 = new GameObject("brazier");
	brazier4->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier4->localTransform.setPos(glm::vec3(-26.590355, 0.500000, -6.158344));
	brazier4->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier5 = new GameObject("brazier");
	brazier5->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier5->localTransform.setPos(glm::vec3(-20.662336, 0.500000, 13.387436));
	brazier5->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier6 = new GameObject("brazier");
	brazier6->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier6->localTransform.setPos(glm::vec3(-19.626617, 0.500000, -14.462436));
	brazier6->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier7 = new GameObject("brazier");
	brazier7->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier7->localTransform.setPos(glm::vec3(-2.028160, 0.500000, -20.524620));
	brazier7->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier8 = new GameObject("brazier");
	brazier8->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier8->localTransform.setPos(glm::vec3(-2.043056, 0.500000, -27.361380));
	brazier8->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier9 = new GameObject("brazier");
	brazier9->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier9->localTransform.setPos(glm::vec3(-8.776593, 0.500000, -35.394379));
	brazier9->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier10 = new GameObject("brazier");
	brazier10->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier10->localTransform.setPos(glm::vec3(8.868602, 0.500000, -35.207016));
	brazier10->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier11 = new GameObject("brazier");
	brazier11->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier11->localTransform.setPos(glm::vec3(-13.200074, 0.500000, -40.927586));
	brazier11->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier12 = new GameObject("brazier");
	brazier12->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier12->localTransform.setPos(glm::vec3(-20.744389, 0.500000, -41.195820));
	brazier12->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier13 = new GameObject("brazier");
	brazier13->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier13->localTransform.setPos(glm::vec3(-19.371952, 0.500000, -49.894417));
	brazier13->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier14 = new GameObject("brazier");
	brazier14->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier14->localTransform.setPos(glm::vec3(-0.732033, 0.500000, -45.884380));
	brazier14->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier15 = new GameObject("brazier");
	brazier15->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier15->localTransform.setPos(glm::vec3(-0.732033, 0.500000, -52.130676));
	brazier15->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier16 = new GameObject("brazier");
	brazier16->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier16->localTransform.setPos(glm::vec3(19.899551, 0.500000, -50.202072));
	brazier16->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier17 = new GameObject("brazier");
	brazier17->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier17->localTransform.setPos(glm::vec3(19.737904, 0.500000, -42.220512));
	brazier17->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier18 = new GameObject("brazier");
	brazier18->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier18->localTransform.setPos(glm::vec3(14.181462, 0.500000, -42.111050));
	brazier18->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier19 = new GameObject("brazier");
	brazier19->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier19->localTransform.setPos(glm::vec3(18.004396, 0.500000, -20.646599));
	brazier19->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier20 = new GameObject("brazier");
	brazier20->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier20->localTransform.setPos(glm::vec3(12.796072, 0.500000, -20.646599));
	brazier20->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier21 = new GameObject("brazier");
	brazier21->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier21->localTransform.setPos(glm::vec3(2.245983, 0.500000, -20.821217));
	brazier21->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier22 = new GameObject("brazier");
	brazier22->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier22->localTransform.setPos(glm::vec3(32.002598, 0.500000, -1.914401));
	brazier22->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier23 = new GameObject("brazier");
	brazier23->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier23->localTransform.setPos(glm::vec3(32.002598, 0.500000, 1.469780));
	brazier23->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier24 = new GameObject("brazier");
	brazier24->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier24->localTransform.setPos(glm::vec3(28.118650, 0.500000, 1.469780));
	brazier24->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier25 = new GameObject("brazier");
	brazier25->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier25->localTransform.setPos(glm::vec3(28.118650, 0.500000, -1.914401));
	brazier25->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier26 = new GameObject("brazier");
	brazier26->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier26->localTransform.setPos(glm::vec3(28.118650, 0.500000, -5.344815));
	brazier26->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier27 = new GameObject("brazier");
	brazier27->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier27->localTransform.setPos(glm::vec3(32.002598, 0.500000, -5.344815));
	brazier27->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier28 = new GameObject("brazier");
	brazier28->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier28->localTransform.setPos(glm::vec3(28.118650, 0.500000, 5.344815));
	brazier28->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier29 = new GameObject("brazier");
	brazier29->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier29->localTransform.setPos(glm::vec3(32.002598, 0.500000, 5.344815));
	brazier29->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier30 = new GameObject("brazier");
	brazier30->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier30->localTransform.setPos(glm::vec3(61.330212, 0.500000, -6.199307));
	brazier30->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier31 = new GameObject("brazier");
	brazier31->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier31->localTransform.setPos(glm::vec3(61.330212, 0.500000, 6.199307));
	brazier31->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier32 = new GameObject("brazier");
	brazier32->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier32->localTransform.setPos(glm::vec3(53.128838, 0.500000, 0.000000));
	brazier32->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier33 = new GameObject("brazier");
	brazier33->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier33->localTransform.setPos(glm::vec3(43.614162, 0.500000, 13.970689));
	brazier33->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier34 = new GameObject("brazier");
	brazier34->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier34->localTransform.setPos(glm::vec3(43.614162, 0.500000, -13.970689));
	brazier34->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier35 = new GameObject("brazier");
	brazier35->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier35->localTransform.setPos(glm::vec3(13.018315, 0.500000, 45.338821));
	brazier35->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier36 = new GameObject("brazier");
	brazier36->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier36->localTransform.setPos(glm::vec3(16.903147, 0.500000, 49.881462));
	brazier36->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier37 = new GameObject("brazier");
	brazier37->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier37->localTransform.setPos(glm::vec3(-13.018315, 0.500000, 45.338821));
	brazier37->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier38 = new GameObject("brazier");
	brazier38->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier38->localTransform.setPos(glm::vec3(-16.903147, 0.500000, 49.881462));
	brazier38->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier39 = new GameObject("brazier");
	brazier39->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier39->localTransform.setPos(glm::vec3(21.690195, 0.500000, 38.013233));
	brazier39->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier40 = new GameObject("brazier");
	brazier40->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier40->localTransform.setPos(glm::vec3(-21.690195, 0.500000, 38.013233));
	brazier40->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier41 = new GameObject("brazier");
	brazier41->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier41->localTransform.setPos(glm::vec3(-2.287966, 0.500000, 44.972633));
	brazier41->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier42 = new GameObject("brazier");
	brazier42->localTransform.setPos(glm::vec3(2.287966, 0.500000, 44.972633));
	brazier42->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	brazier42->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));

	auto brazier43 = new GameObject("brazier");
	brazier43->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier43->localTransform.setPos(glm::vec3(13.638598, 0.500000, 28.890642));
	brazier43->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier44 = new GameObject("brazier");
	brazier44->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier44->localTransform.setPos(glm::vec3(16.099287, 0.500000, 25.178598));
	brazier44->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier45 = new GameObject("brazier");
	brazier45->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier45->localTransform.setPos(glm::vec3(-13.638598, 0.500000, 28.890642));
	brazier45->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier46 = new GameObject("brazier");
	brazier46->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier46->localTransform.setPos(glm::vec3(-16.099287, 0.500000, 25.178598));
	brazier46->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier47 = new GameObject("brazier");
	brazier47->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier47->localTransform.setPos(glm::vec3(9.315192, 0.500000, 20.322336));
	brazier47->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	auto brazier48 = new GameObject("brazier");
	brazier48->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier48->localTransform.setPos(glm::vec3(-9.315192, 0.500000, 20.322336));
	brazier48->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
#pragma endregion


#pragma region trees
	auto tree1 = new GameObject("Tree1");
	tree1->addBehaviour(new MeshRenderBehaviour(m_tree, ShaderManager::getShader(GBUFFER_SHADER)));
	tree1->localTransform.setPos(glm::vec3(10.846286, 0.500000, -9.084585));

	auto tree2 = new GameObject("Tree2");
	tree2->addBehaviour(new MeshRenderBehaviour(m_tree, ShaderManager::getShader(GBUFFER_SHADER)));
	tree2->localTransform.setPos(glm::vec3(12.069606, 0.500000, 6.998760));
#pragma endregion

	auto bottomRoom = new GameObject("BottomRoom");
	bottomRoom->addBehaviour(new MeshRenderBehaviour(m_bottomRoom, ShaderManager::getShader(GBUFFER_SHADER)));

	auto grove = new GameObject("Grove");
	grove->addBehaviour(new MeshRenderBehaviour(m_grove, ShaderManager::getShader(GBUFFER_SHADER)));

	auto leftRoom = new GameObject("LeftRoom");
	leftRoom->addBehaviour(new MeshRenderBehaviour(m_leftRoom, ShaderManager::getShader(GBUFFER_SHADER)));

	auto rightRoom = new GameObject("RightRoom");
	rightRoom->addBehaviour(new MeshRenderBehaviour(m_rightRoom, ShaderManager::getShader(GBUFFER_SHADER)));

	auto topRoom1 = new GameObject("TopRoom1");
	topRoom1->addBehaviour(new MeshRenderBehaviour(m_topRoom1, ShaderManager::getShader(GBUFFER_SHADER)));

	auto topRoom2 = new GameObject("TopRoom2");
	topRoom2->addBehaviour(new MeshRenderBehaviour(m_topRoom2, ShaderManager::getShader(GBUFFER_SHADER)));

	auto altar = new GameObject("Altar");
	altar->addBehaviour(new MeshRenderBehaviour(m_altar, ShaderManager::getShader(GBUFFER_SHADER)));


	auto scene = new Scene("DemoScene");
	scene->addChild(player);
	scene->addChild(bottomRoom);
	scene->addChild(grove);
	scene->addChild(leftRoom);
	scene->addChild(rightRoom);
	scene->addChild(topRoom1);
	scene->addChild(topRoom2);
	//scene->addChild(altar);

	{
		scene->addChild(brazier);
		//new P_PhysicsBody(&brazier->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier2);
		//new P_PhysicsBody(&brazier2->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier3);
		//new P_PhysicsBody(&brazier3->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier4);
		//new P_PhysicsBody(&brazier4->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier5);
		//new P_PhysicsBody(&brazier5->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier6);
		//new P_PhysicsBody(&brazier6->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier7);
		//new P_PhysicsBody(&brazier7->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier8);
		//new P_PhysicsBody(&brazier8->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier9);
		//new P_PhysicsBody(&brazier9->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier10);
		//new P_PhysicsBody(&brazier10->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier11);
		//new P_PhysicsBody(&brazier11->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier12);
		//new P_PhysicsBody(&brazier12->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier13);
		//new P_PhysicsBody(&brazier13->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier14);
		//new P_PhysicsBody(&brazier14->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier15);
		//new P_PhysicsBody(&brazier15->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier16);
		//new P_PhysicsBody(&brazier16->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier17);
		//new P_PhysicsBody(&brazier17->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier18);
		//new P_PhysicsBody(&brazier18->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier19);
		//new P_PhysicsBody(&brazier19->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier20);
		//new P_PhysicsBody(&brazier20->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier21);
		///new P_PhysicsBody(&brazier21->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier22);
		//new P_PhysicsBody(&brazier22->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier23);
		//new P_PhysicsBody(&brazier23->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier24);
		//new P_PhysicsBody(&brazier24->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier25);
		//new P_PhysicsBody(&brazier25->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier26);
		//new P_PhysicsBody(&brazier26->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier27);
		//new P_PhysicsBody(&brazier28->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier28);
		//new P_PhysicsBody(&brazier28->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier29);
		//new P_PhysicsBody(&brazier29->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier30);
		//new P_PhysicsBody(&brazier30->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier31);
		//new P_PhysicsBody(&brazier31->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier32);
		//new P_PhysicsBody(&brazier32->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier33);
		//new P_PhysicsBody(&brazier33->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier34);
		//new P_PhysicsBody(&brazier34->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier35);
		//new P_PhysicsBody(&brazier35->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier36);
		//new P_PhysicsBody(&brazier36->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier37);
		//new P_PhysicsBody(&brazier37->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier38);
		//new P_PhysicsBody(&brazier38->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier39);
		//new P_PhysicsBody(&brazier39->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier40);
		//new P_PhysicsBody(&brazier40->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier41);
		//new P_PhysicsBody(&brazier41->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier42);
		//new P_PhysicsBody(&brazier42->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier43);
		//new P_PhysicsBody(&brazier43->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier44);
		//new P_PhysicsBody(&brazier44->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier45);
		//new P_PhysicsBody(&brazier45->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier46);
		//new P_PhysicsBody(&brazier46->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier47);
		//new P_PhysicsBody(&brazier47->localTransform, 1.0f, false, BOX, 1.f, 1.f, 1.f, glm::vec3(0.f, 0.f, 1.f), 0.f, 0.f, true);
		scene->addChild(brazier48);
	}

	{
		scene->addChild(tree1);
		scene->addChild(tree2);
	}

	Camera::mainCameraTransform = &(cameraObject->worldTransform);

	auto attackBox = new GameObject("AttackBox");
	attackBox->localTransform.setPos(glm::vec3(0.f, 0.f, 0.3f));
	attackBox->localTransform.setScale(glm::vec3(0.2f, 0.2f, 1.f));
	attackBox->addBehaviour(new MeshRenderBehaviour(m_box, ShaderManager::getShader(GBUFFER_SHADER)));

	ravagerPhys = new P_PhysicsBody(player, 1.f, true, SPHERE, 0.5f, 0.f, 0.f, glm::vec3(0, 0.5f, 0), 0.0f, 1.0f, false, false, "Player");
	hitBox = new P_PhysicsBody(attackBox, 1.f, false, BOX, .2f, .2f, 2.f, VEC3ZERO, 0.f, 0.f, false, true, "Sword");

	player->addBehaviour(new PlayerController(ravagerPhys, hitBox));
	player->addChild(attackBox);
	ravagerPhys->trackNames(true);

	//World Physics Bodies
	{
		auto owo = new GameObject("World");
		owo->localTransform.setPos(glm::vec3(4.f, -0.4f, 0.f)*2.f);
		floor = new P_PhysicsBody(owo, 1.0f, false, BOX, 1.f * 2, 56.f * 2, 54.f * 2, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World");
		owo->localTransform.setPos(glm::vec3(0.5f, 2.f, -9.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 13.f * 2.f, 1.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(20.25f, 2.f, -9.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f, 23.5f, 1.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(-15.75f, 2.f, -9.f));
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 16.5f * 2.f, 1.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(-12.f, 2.f, -14.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 24.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(-12.f, 2.f, 15.5f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 23.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(-14.f, 2.f, 9.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 20.f * 2.f, 1.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(12.f, 2.f, -14.25f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 25.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(12.f, 2.f, 14.25f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 25.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(18.f, 2.f, 9.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 28.f * 2.f, 1.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(32.f, 2.f, -0.25f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 18.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(0.f, 2.f, 27.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 24.f * 2.f, 1.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(0.f, 2.f, -27.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 24.f * 2.f, 1.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(-24.f, 2.f, 0.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 18.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(13.f, 2.f, 1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 3.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(15.f, 3.f, 1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 3.f * 2.f, 1.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(16.25f, 2.f, 1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.5f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(13.f, 2.f, -1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 3.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(15.f, 3.f, -1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 3.f * 2.f, 1.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(16.25f, 2.f, -1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.5f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(16.75f, 2.f, 0.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 0.5f * 2.f, 4.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(20.f, 2.f, 5.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 7.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(20.f, 2.f, -5.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 1.f * 2.f, 7.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(20.75f, 2.f, 1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 2.5f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(20.75f, 2.f, -1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 2.5f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(23.f, 3.75f, 1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 1.5f * 2.f, 2.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(23.f, 3.75f, -1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 1.5f * 2.f, 2.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(25.75f, 2.f, 1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 3.5f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(25.75f, 2.f, -1.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 3.5f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(27.75, 2.f, 0.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 0.5f * 2.f, 8.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(27.75f, 3.75f, 5.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 1.5f * 2.f, 0.5f * 2.f, 2.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(27.75, 3.75, -5.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 1.5f * 2.f, 0.5f * 2.f, 2.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(27.75, 2.f, 7.25f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 0.5f * 2.f, 2.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(27.75, 2.f, -7.25) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 0.5f * 2.f, 2.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(0.f, 2.f, 8.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 23.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(0.f, 2.f, -8.75f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 5.f * 2.f, 23.f * 2.f, 0.5f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);


		owo = new GameObject("World"); 
		owo->localTransform.setPos(glm::vec3(4.f, 10.f, 0.f) * 2.f);
		new P_PhysicsBody(owo, 1.0f, false, BOX, 1.f * 2.f, 56.f * 2.f, 54.f * 2.f, glm::vec3(0.f, 0.f, 0.f), 0.f, 0.f, true);
	}
	
	//P_PhysicsBody::P_bodyCount.push_back(ravagerPhys);
	//P_PhysicsBody::P_bodyCount.push_back(floor);

	if (_DEBUG)
		new P_PhysicsBody(new GameObject("World"), 1.f, false, BOX, 1.f, 500.f, 500.f, glm::vec3(0, 20.f, 0), 0, 0, true);


#pragma region Level Physics Bodies


#pragma endregion


	//Load audio track for ambiance
	AudioPlayer::loadAudio(*new AudioTrack("Ambiance", FMOD_3D, AudioType::EFFECT, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, true, 0.1f, 5000.f), "Ambiance");
	//Play ambiance
	AudioPlayer::playTrack("Ambiance");
	AudioPlayer::setVolume("Ambiance", 0.1f);

	m_activeScenes.push_back(scene);
}

void Game::update()
{
	Time::update();

	m_ravagerIdle->update();


	//Remove this when done testing. Or use as a jump for testing purposes.
	if (Input::GetKeyDown(KeyCode::Space)) {
		ravagerPhys->P_velocity.y = 4.f;
	}

	///SUPER SKETCHY KILL BUTTON
	if (Input::GetKeyDown(KeyCode::K))
	{
		//std::vector<Behaviour*>* behav = player->getBehaviours();
		//PlayerController* playR = (PlayerController*)&behav[1];
		//playR->health = 0.f;
	}


	if (Input::GetKeyDown(KeyCode::Escape))
	{
		exit(0);
	}

	if (Input::GetKeyPress(KeyCode::G))
	{
		spawnEnemy(RAVAGER, VEC3ZERO + glm::vec3(0, 2, 0));
	}

	if (Input::GetKeyPress(KeyCode::F1)) {
		displayBuffers = !displayBuffers;
	}

	if (Input::GetKeyUp(KeyCode::F2)) {
		displayBloom = !displayBloom;
	}

	if (Input::GetKeyDown(KeyCode::F4)) {
		guiEnabled = !guiEnabled;
	}

	ParticleManager::update(Time::deltaTime);

	AudioPlayer::update(Time::deltaTime);

	P_PhysicsBody::P_physicsUpdate(Time::deltaTime);
	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i]->update();
	}

	Shader::unbind();
	Input::ResetKeys();
}

void Game::draw()
{
	/// Clear Buffers ///
	glClearColor(0.f, 0.0f, 0.0f, 1.f);
	deferredComposite->clear();
	gBuffer->clear();
	edgeBuffer->clear();

	ShaderManager::update(*Camera::mainCamera);

	//Camera 1
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		gBuffer->bind();

		for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
			m_activeScenes[i]->onRender();
		}

		gBuffer->unbind();
	}

	//Copies depth texture from gbuffer to deferred composite
	
	//GUI();

	//F1 to toggle displaying of buffers
	if (!displayBuffers) 
	{
		ShaderManager::getPost(DEFERREDLIGHT_POST)->bind();
		gBuffer->bindLighting();
		toonRamp->bind(3);
		deferredComposite->drawTo();
		toonRamp->unbind(3);
		gBuffer->unbindLighting();
		ShaderManager::getPost(DEFERREDLIGHT_POST)->unbind();
	}
	else
	{
		gBuffer->drawBuffers();

		glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);					///Bottom Right
		ShaderManager::getPost(DEFERREDLIGHT_POST)->bind();
		gBuffer->bindLighting();
		FrameBuffer::drawFSQ();
		gBuffer->unbindLighting();
		ShaderManager::getPost(DEFERREDLIGHT_POST)->unbind();
	}

	ShaderManager::getPost(TOONSHADER_POST)->bind();
	toonRamp->bind(3);
	gBuffer->bindTex(1, 0);
	deferredComposite->draw();
	gBuffer->unbindTex(1);
	toonRamp->unbind(3);
	ShaderManager::getPost(TOONSHADER_POST)->unbind();

	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	gBuffer->bindTex(0, 3);
	bloomBuffer->drawTo();
	gBuffer->unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	bloomBuffer->applyBloom(0.01f, 20);

	if (displayBloom)
	{
		bloomBuffer->drawBuffer(2);
	}

	ShaderManager::getPost(EMISSIVE_POST)->bind();
	bloomBuffer->bindTexColor(3, 1);
	deferredComposite->draw();
	gBuffer->unbindTex(1);
	ShaderManager::getPost(EMISSIVE_POST)->unbind();

	edgeBuffer->bind();
	ShaderManager::getPost(EDGEDETECTION_POST)->bind();
	gBuffer->bindEdge();
	FrameBuffer::drawFSQ();
	gBuffer->unbindEdge();
	edgeBuffer->unbind();
	
	//Example of how to use the new composite buffer
	//ShaderManager::getPost(GREYSCALE_POST)->bind();
	//deferredComposite->draw();
	//ShaderManager::getPost(GREYSCALE_POST)->unbind();

	ShaderManager::getPost(COLORCORR_POST)->bind();
	colorCorrection->bind(30);
	//deferredComposite->draw();
	colorCorrection->unbind(30);
	ShaderManager::getPost(COLORCORR_POST)->unbind();

	ShaderManager::getPost(ADDEDGE_POST)->bind();
	edgeBuffer->bindTex(1, 0);				//Edge buffer
	deferredComposite->drawToScreen();
	Texture::unbind(1);
	ShaderManager::getPost(ADDEDGE_POST)->bind();

	//Render the particle emitters
	if (!displayBuffers)
	{
		gBuffer->copyTo(GL_NONE, GL_DEPTH_BUFFER_BIT, WINDOW_WIDTH, WINDOW_HEIGHT);
		ShaderManager::getGeom(BILLBOARD_GEOM)->bind();
		ShaderManager::getGeom(BILLBOARD_GEOM)->sendUniform("uTex", 0);
		for (unsigned int i = 0; i < NUM_PARTICLES; i++)
		{
			ShaderManager::getGeom(BILLBOARD_GEOM)->sendUniform("uModel", ParticleManager::getParticle(i)->transform.getModel());
			ParticleManager::render(i);
		}
	}
}

void Game::GUI()
{
	UI::Start(WINDOW_WIDTH, WINDOW_HEIGHT);

	ImGui::SliderFloat3("Ravager Position", &ravagerPhys->getGameObject()->localTransform.getPos()[0], -5.f, 5.f);


	UI::End();
}
	
void Game::spawnEnemy(EnemyType _type, glm::vec3 _location)
{
	auto enemy = new Enemy("Enemy");
	enemy->localTransform.setPos(_location);
	switch (_type)
	{
	case RAVAGER:
		enemy->addBehaviour(new MeshRenderBehaviour(m_ravager, ShaderManager::getShader(GBUFFER_SHADER)));
		break;
	case LESSER_GHOUL:
	case GREATER_GHOUL:
	default:
		enemy->addBehaviour(new MeshRenderBehaviour(m_box, ShaderManager::getShader(GBUFFER_SHADER)));
		break;
	}

	enemies.push_back(enemy);

	m_activeScenes[0]->addChild(enemy);

	P_PhysicsBody* enemyBody = new P_PhysicsBody(enemy, 10.f, true, SPHERE, 0.5f, 0.f, 0.f, VEC3ZERO, 0.f, 1.f, false, false, "Enemy");
	enemyBodies.push_back(enemyBody);
	enemy->addBehaviour(new TempEnemy(enemyBody, enemy, player));
	enemyBody->trackNames(true);
}

void Game::killEnemy(Enemy* _toKill)
{
	int i = 0;
	bool proceed = false;

	for (i; i < enemies.size(); ++i)
	{
		if (enemies[i] == _toKill)
		{
			proceed = true;
			break;
		}
	}
	if (proceed)
	{
		delete enemyBodies[i];
		enemyBodies.erase(enemyBodies.begin() + i);
		enemies[i]->getParent()->removeChild(enemies[i]);
		//GameObject* parent = enemies[0]->getParent();
		//std::vector<GameObject*> childVec = *parent->getChildren();
		//parent->removeChildren();
		//for (GameObject* obj : childVec)
		//{
		//	if (obj != enemies[0])
		//	{
		//		parent->addChild(obj);
		//	}
		//}
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
	}
	else
		std::cout << "ERROR: Enemy not found!" << std::endl;
}

int Game::run() {
	while (m_display->isOpen()) {


		ShaderManager::getShader(PHONG_SHADER)->bind();
		//ShaderManager::getShader(PHONG_SHADER)->SendUniform("light.position", glm::vec4(lights[0]->GetTransform()->GetPos(), 1.0f));
		Shader::unbind();

		update();

		m_display->clear(0.f, 0.0f, 0.0f, 1.f);

		draw();

		m_display->flip();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				m_display->close();
			}
		}
		
		//Example for stopping the particles, etc, could even be based on time passed
		/*if (ParticleManager::getParticle(SMOKEBOMB_PARTICLE)->getCurrent() == ParticleManager::getParticle(SMOKEBOMB_PARTICLE)->getMax())
		{
			ParticleManager::getParticle(SMOKEBOMB_PARTICLE)->setRate(0.f);
		}*/

		if (Input::GetKeyPress(KeyCode::F5))
		{
			ShaderManager::reloadShaders();
		}
	}

	//Closes and cleans up after the audioplayer system
	AudioPlayer::close();
	SDL_Quit();
	return 0;
}

void Game::initGLEW() {
	//Holds the result of the initialization of glew.
	//glewInit finds every OpenGl function that our system supports
	GLenum status = glewInit();

	//Checks if glewInit didn't returned okay.
	if (status != GLEW_OK)
	{
		//If it didn't, prints an error message
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);
}

void Game::initSDL() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	///Setting attributes
		//2 to the 8th power shades of Red (256)
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//2 to the 8th power shades of Green (256)
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//2 to the 8th power shades of Blue (256)
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	//2 to the 8th power of shades of transparancy (256)
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//How many bits allocated for each pixel, we have 32 bits of color, hence we want 32 here
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	//Sets the depth buffer for openGL, basically, is needed for z buffering 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//Allocates the space for a second window that won't be displayed
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Set GL Context Version (Forces OpenGL version 3.2)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	//Set up anti-aliasing (4xMSAA)
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	///End Attributes
}