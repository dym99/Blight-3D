#include "Game.h"
#include <iostream>


#include "P_PhysicsBody.h"

#include "ShaderManager.h"
#include "MeshRenderBehaviour.h"
#include "TestRotateBehaviour.h"
#include "MouseLook.h"
#include "CameraBehaviour.h"
#include "AudioPlayer.h"
#include "PlayerController.h"
#include "TempEnemy.h"

#include "Input.h"

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

	delete uiImage;
	uiImage = nullptr;

	delete gBuffer;
	gBuffer = nullptr;
	delete deferredComposite;
	deferredComposite = nullptr;
	delete workBuffer1;
	workBuffer1 = nullptr;
	delete workBuffer2;
	workBuffer2 = nullptr;
	delete workBuffer3;
	workBuffer3 = nullptr;
}

void Game::initGame()
{
	///Initialise SDL
	initSDL();

	///Initialise the display
	m_display = new Display("Blight");

	///Initialise GLEW
	initGLEW();

	//Initialise Framebuffers
	gBuffer = new FrameBuffer(3);
	deferredComposite = new FrameBuffer(1);
	workBuffer1 = new FrameBuffer(1);
	workBuffer2 = new FrameBuffer(1);
	workBuffer3 = new FrameBuffer(1);

	uiImage = new Texture();
	uiImage->Load("./Resources/Textures/UIpost.png");

	//Initializes the screen quad
	InitFullScreenQuad();

	//Initializes the audio player and sets it up
	AudioPlayer::init(100, FMOD_INIT_NORMAL);
	AudioPlayer::set3DSettings(1.0f, 1.0f);

	//Initialise Camera
	auto camera = new Camera();
	camera->Perspective(70.f, 16.f/9.f, 0.001f, 1000.f);
	camera->setPos(glm::vec3(0.f, 0.f, 3.0f));
	Camera::mainCamera = camera;
	//Load in resources
	m_ravager = new Model();
	m_ravager->LoadFromFile("./Resources/Objects/Ravager2/", "Ravager");
	m_ravager->colorTint = glm::vec3(1.f, 1.f, 1.f);
	m_testArea = new Model();
	m_testArea->LoadFromFile("./Resources/Objects/TestArea/", "TestArea");
	m_brazier = new Model();
	m_brazier->LoadFromFile("./Resources/Objects/Brazier/", "brazier");
	m_box = new Model();
	m_box->LoadFromFile("./Resources/Objects/Box/", "cube");
	
	ShaderManager::loadShaders();

	ParticleManager::loadParticles();

	//Frame Buffers
#pragma region FrameBuffers
	gBuffer->InitDepthTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	gBuffer->InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Flat color (albedo)
	gBuffer->InitColorTexture(1, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB8, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Normals (xyz)
	gBuffer->InitColorTexture(2, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);		//View Space Positions (xyz)


	if (!gBuffer->CheckFBO()) {
		std::cout << "GBuffer failed to load.\n\n";
		system("pause");
		exit(0);
	}

	deferredComposite->InitDepthTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	deferredComposite->InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

	if (!deferredComposite->CheckFBO()) {
		std::cout << "Deferred Composite failed to load.\n\n";
		system("pause");
		exit(0);
	}

	workBuffer1->InitColorTexture(0, WINDOW_WIDTH / BLOOM_DOWNSCALE, WINDOW_HEIGHT / BLOOM_DOWNSCALE,
		GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE);

	if (!workBuffer1->CheckFBO()) {
		std::cout << "FBO2 failed to load.\n\n";
		system("pause");
		exit(0);
	}

	workBuffer2->InitColorTexture(0, WINDOW_WIDTH / BLOOM_DOWNSCALE, WINDOW_HEIGHT / BLOOM_DOWNSCALE,
		GL_RGB8, GL_LINEAR, GL_CLAMP_TO_EDGE);

	if (!workBuffer2->CheckFBO()) {
		std::cout << "FBO3 failed to load.\n\n";
		system("pause");
		exit(0);
	}

	workBuffer3->InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

	if (!workBuffer3->CheckFBO()) {
		std::cout << "FBO4 Failed to load.\n\n";
		system("pause");
		exit(0);
	}
#pragma endregion

	//Set up the test Scene
	auto attackBox = new GameObject("AttackBox");
	attackBox->localTransform.setPos(glm::vec3(0.f, 0.f, 0.3f));
	attackBox->localTransform.setScale(glm::vec3(0.2f, 0.2f, 1.f));
	attackBox->addBehaviour(new MeshRenderBehaviour(m_box, ShaderManager::getShader(GBUFFER_SHADER)));

	//auto enemy = new GameObject("TestEnemy");
	//enemy->localTransform.setPos(glm::vec3(0.f, 0.5f, 4.f));
	//enemy->addBehaviour(new MeshRenderBehaviour(m_box, ShaderManager::getShader(GBUFFER_SHADER)));
	//enemies.push_back(enemy);

	player = new GameObject("Ravager");
	player->addBehaviour(new MeshRenderBehaviour(m_ravager, ShaderManager::getShader(GBUFFER_SHADER)));

	auto cameraPivot = new GameObject("CameraPivot");
	cameraPivot->localTransform.setPos(glm::vec3(0.f,1.f,0.f));
	cameraPivot->addBehaviour(new MouseLook(player));

	auto cameraObject = new GameObject("Camera");

	cameraObject->localTransform.setPos(glm::vec3(0, 0.5f, 3.f));

	camera->setTransform(&cameraObject->worldTransform);

	cameraPivot->addChild(cameraObject);
	player->addChild(cameraPivot);
	
	auto brazier = new GameObject("brazier");
	brazier->addBehaviour(new MeshRenderBehaviour(m_brazier, ShaderManager::getShader(GBUFFER_SHADER)));
	brazier->localTransform.setPos(glm::vec3(3.f, 0.5f, 3.f));
	brazier->localTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	
	
	auto testArea = new GameObject("TestArea");
	testArea->addBehaviour(new MeshRenderBehaviour(m_testArea, ShaderManager::getShader(GBUFFER_SHADER)));


	auto scene = new Scene("DemoScene");
	scene->addChild(brazier);
	scene->addChild(player);
	scene->addChild(testArea);
	//scene->addChild(enemy);
	scene->addChild(attackBox);

	Camera::mainCameraTransform = &(cameraObject->worldTransform);


	//TODO: Set up transform class so that a world transform can exist
	ravagerPhys = new P_PhysicsBody(player, 1.f, true, SPHERE, 0.5f, 0.f, 0.f, glm::vec3(0, 0.5f, 0), 0.0f, 1.0f, false, false, "Player");
	hitBox = new P_PhysicsBody(attackBox, 1.f, false, BOX, .2f, .2f, 2.f, VEC3ZERO, 0.f, 0.f, false, true, "Sword");
	//enemyBox = new P_PhysicsBody(enemy, 1.f, false, SPHERE, 0.5f, 0.f, 0.f, VEC3ZERO, 0.f, 0.f, true, false, "Enemy");
	//enemy->addBehaviour(new TempEnemy(enemyBox));
	player->addBehaviour(new PlayerController(ravagerPhys, hitBox));
	player->addChild(attackBox);
	ravagerPhys->trackNames(true);
	//enemyBox->trackNames(true);
	GameObject* owo = new GameObject("Floor");
	owo->localTransform.setRot(glm::vec3(0, 90, 0));
	//scene->addChild(owo);

	new P_PhysicsBody(owo, 1.f, false, BOX, 1.f, 8.f, 8.f, glm::vec3(0, -0.5f, 0), 0, 0, true, false, "Floor");
	new P_PhysicsBody(owo, 1.f, false, BOX, 1.f, 2.f, 2.f, glm::vec3(0, -0.5f, 5), 0, 0, true, false, "Floor");
	new P_PhysicsBody(owo, 1.f, false, BOX, 1.f, 8.f, 8.f, glm::vec3(0, -0.5f, 10), 0, 0, true, false, "Floor");

	//Load audio track for drum loop
	AudioPlayer::loadAudio(*new AudioTrack("Ambiance", FMOD_3D, AudioType::EFFECT, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, true, 0.1f, 5000.f), "Ambiance");
	//Play drum loop
	AudioPlayer::playTrack("Ambiance");
	AudioPlayer::setVolume("Ambiance", 0.1f);

	m_activeScenes.push_back(scene);
}

void Game::update()
{
	Time::update();

	if (Input::GetKeyDown(KeyCode::Escape))
		exit(0);

	if (Input::GetKeyPress(KeyCode::F1)) {
		displayBuffers = !displayBuffers;
	}

	if (Input::GetKeyPress(KeyCode::G))
	{
		spawnEnemy(RAVAGER, glm::vec3(0, 0.5f, 4));
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	deferredComposite->Clear();
	gBuffer->Clear();
	workBuffer1->Clear();
	workBuffer2->Clear();
	workBuffer3->Clear();

	ShaderManager::update(*Camera::mainCamera);

	//Camera 1
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		gBuffer->Bind();

		for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
			m_activeScenes[i]->onRender();
		}

		gBuffer->Unbind();
	}

	//Copies depth texture from gbuffer to deferred composite
	

	//F1 to toggle displaying of buffers
	if (!displayBuffers) {
#pragma region Normal Render
		deferredComposite->Bind();
		ShaderManager::getPost(DEFERREDLIGHT_POST)->bind();
		ShaderManager::getPost(DEFERREDLIGHT_POST)->sendUniform("uScene", 0);			//Albedo color
		ShaderManager::getPost(DEFERREDLIGHT_POST)->sendUniform("uNormalMap", 1);		//Normals
		ShaderManager::getPost(DEFERREDLIGHT_POST)->sendUniform("uPositionMap", 2);		//Frag positions
		gBuffer->bindTex(0, 0);
		gBuffer->bindTex(1, 1);
		gBuffer->bindTex(2, 2);
		DrawFullScreenQuad();
		Texture::Unbind(2);
		Texture::Unbind(1);
		Texture::Unbind(0);
		ShaderManager::getPost(DEFERREDLIGHT_POST)->unbind();

		deferredComposite->Unbind();
		
#pragma endregion
	}
	else {
#pragma region Buffer Renders
		//*
		glViewport(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);					///Top Left
		ShaderManager::getPost(PASSTHROUGH_POST)->bind();
		ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
		gBuffer->bindTex(0, 0);		//Albedo Color
		DrawFullScreenQuad();
		Texture::Unbind(0);
		ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

		glViewport(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);	///Top Right
		ShaderManager::getPost(PASSTHROUGH_POST)->bind();
		ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
		gBuffer->bindTex(0, 1);			//Normals
		DrawFullScreenQuad();
		Texture::Unbind(0);
		ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

		glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);									///Bottom Left
		ShaderManager::getPost(PASSTHROUGH_POST)->bind();
		ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
		gBuffer->bindTex(0, 2);		//Frag Positions 
		DrawFullScreenQuad();
		Texture::Unbind(0);
		ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

		glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);					///Bottom Right
		ShaderManager::getPost(DEFERREDLIGHT_POST)->bind();
		ShaderManager::getPost(DEFERREDLIGHT_POST)->sendUniform("uScene", 0);			//Albedo color
		ShaderManager::getPost(DEFERREDLIGHT_POST)->sendUniform("uNormalMap", 1);		//Normals
		ShaderManager::getPost(DEFERREDLIGHT_POST)->sendUniform("uPositionMap", 2);		//Frag positions
		gBuffer->bindTex(0, 0);
		gBuffer->bindTex(1, 1);
		gBuffer->bindTex(2, 2);
		DrawFullScreenQuad();
		Texture::Unbind(2);
		Texture::Unbind(1);
		Texture::Unbind(0);
		ShaderManager::getPost(DEFERREDLIGHT_POST)->unbind();

		//*/
#pragma endregion
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	/// * Performs Frame buffer stuffs, don't remove pls and thank
	//glEnable(GL_BLEND);
	//*
	ShaderManager::getPost(UI_POST)->bind();
	ShaderManager::getPost(UI_POST)->sendUniform("uiTex", 1);
	uiImage->Bind(1);
	ProcessFramebufferStuff(*deferredComposite, *workBuffer1, *workBuffer2, *workBuffer3,
								ShaderManager::getBloom(), *ShaderManager::getPost(UI_POST),
									true, false);
	uiImage->Unbind(1);//*/
	//glDisable(GL_BLEND);
	/// * Will be commented out in case this branch gets used for Expo
	//////////////////////////////////////////////////////////////////////////////////////////////

	//Render the particle emitters
	if (!displayBuffers)
	{
		gBuffer->copyTo(GL_NONE, GL_DEPTH_BUFFER_BIT, WINDOW_WIDTH, WINDOW_HEIGHT);
		ShaderManager::getGeom(BILLBOARD_GEOM)->bind();
		ShaderManager::getGeom(BILLBOARD_GEOM)->sendUniform("uTex", 0);
		//ShaderManager::getGeom(BILLBOARD_GEOM)->sendUniform("uModel", ParticleManager::getParticle(SMOKEBOMB_PARTICLE)->transform.getModel());
		//ParticleManager::render(SMOKEBOMB_PARTICLE);
		ShaderManager::getGeom(BILLBOARD_GEOM)->sendUniform("uModel", ParticleManager::getParticle(FIRE_PARTICLE)->transform.getModel());
		ParticleManager::render(FIRE_PARTICLE);
		ShaderManager::getGeom(BILLBOARD_GEOM)->sendUniform("uModel", ParticleManager::getParticle(FIREPT2_PARTICLE)->transform.getModel());
		ParticleManager::render(FIREPT2_PARTICLE);
		ShaderManager::getGeom(BILLBOARD_GEOM)->unbind();


	}
}
	
int Game::run() {
	while (m_display->isOpen()) {


		ShaderManager::getShader(PHONG_SHADER)->bind();
		//ShaderManager::getShader(PHONG_SHADER)->SendUniform("light.position", glm::vec4(lights[0]->GetTransform()->GetPos(), 1.0f));
		Shader::unbind();

		update();

		m_display->clear(0.f, 0.f, 0.f, 1.f);

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

	P_PhysicsBody* enemyBody = new P_PhysicsBody(enemy, 10.f, false, SPHERE, 0.5f, 0.f, 0.f, VEC3ZERO, 0.f, 1.f, false, false, "Enemy");
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