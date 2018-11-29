#include "Game.h"
#include <iostream>


#include "P_PhysicsBody.h"

#include "ShaderManager.h"
#include "MeshRenderBehaviour.h"
#include "TestRotateBehaviour.h"
#include "MouseLook.h"
#include "CameraBehaviour.h"

#include "Input.h"
Game::Game()
{
}

Game::~Game()
{
	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i] = nullptr;
	}
	m_activeScenes.clear();

	uiImage->Unload();
	delete uiImage;
	uiImage = nullptr;

	delete mainBuffer;
	mainBuffer = nullptr;
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
	mainBuffer = new FrameBuffer(1);
	workBuffer1 = new FrameBuffer(1);
	workBuffer2 = new FrameBuffer(1);
	workBuffer3 = new FrameBuffer(1);

	uiImage = new Texture();
	uiImage->Load("./Resources/Textures/UIpost.png");

	//Initializes the screen quad
	InitFullScreenQuad();

	//Initialise Camera
	auto camera = new Camera();
	camera->Perspective(70.f, 16.f/9.f, 0.001f, 1000.f);
	camera->setPos(glm::vec3(0.f, 0.f, 3.0f));
	Camera::mainCamera = camera;
	//Load in resources
	m_ravager = new Model();
	m_ravager->LoadFromFile("./Resources/Objects/Ravager2/", "Ravager");
	m_testArea = new Model();
	m_testArea->LoadFromFile("./Resources/Objects/TestArea/", "TestArea");
	
	ShaderManager::loadShaders();

	//Frame Buffers
#pragma region FrameBuffers
	mainBuffer->InitDepthTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	mainBuffer->InitColorTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

	if (!mainBuffer->CheckFBO()) {
		std::cout << "FBO1 failed to load.\n\n";
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

	auto ravager = new GameObject("Ravager");
	ravager->addBehaviour(new MeshRenderBehaviour(m_ravager, ShaderManager::getShader(PHONG_SHADER)));

	auto cameraPivot = new GameObject("CameraPivot");
	cameraPivot->localTransform.setPos(glm::vec3(0.f,1.f,0.f));
	cameraPivot->addBehaviour(new MouseLook(ravager));

	auto cameraObject = new GameObject("Camera");

	cameraObject->localTransform.setPos(glm::vec3(0, 0, 3.f));

	camera->setTransform(&cameraObject->worldTransform);

	cameraPivot->addChild(cameraObject);
	ravager->addChild(cameraPivot);
	

	auto testArea = new GameObject("TestArea");
	testArea->addBehaviour(new MeshRenderBehaviour(m_testArea, ShaderManager::getShader(PHONG_SHADER)));


	auto scene = new Scene("DemoScene");
	scene->addChild(ravager);
	scene->addChild(testArea);

	Camera::mainCameraTransform = &(cameraObject->worldTransform);


	//TODO: Set up transform class so that a world transform can exist
	ravagerPhys = new P_PhysicsBody(&ravager->localTransform, 1.f, true, SPHERE, 1.f, 0.f, 0.f, glm::vec3(0, 0.5f, 0));
	P_PhysicsBody::P_bodyCount.push_back(ravagerPhys);
	P_PhysicsBody::P_bodyCount.push_back(new P_PhysicsBody(new Transform(), 1.f, false, BOX, 1.f, 8.f, 8.f, glm::vec3(0, -0.5f, 0), 0, true));
	P_PhysicsBody::P_bodyCount.push_back(new P_PhysicsBody(new Transform(), 1.f, false, BOX, 1.f, 2.f, 2.f, glm::vec3(0, -0.5f, 5), 0, true));
	P_PhysicsBody::P_bodyCount.push_back(new P_PhysicsBody(new Transform(), 1.f, false, BOX, 1.f, 8.f, 8.f, glm::vec3(0, -0.5f, 10), 0, true));


	m_activeScenes.push_back(scene);
}

void Game::update()
{
	Time::update();

	//Remove this when done testing. Or use as a jump for testing purposes.
	if (Input::GetKeyDown(KeyCode::Space)) {
		ravagerPhys->P_velocity.y = 4.f;
	}


	P_PhysicsBody::P_physicsUpdate(Time::deltaTime);
	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i]->update();
	}
	ShaderManager::getShader(PHONG_SHADER)->bind();
	ShaderManager::getShader(PHONG_SHADER)->sendUniform("light.position", glm::vec4(glm::vec3(0,0,0),1));
	Shader::unbind();

	//postProcShaders.at(FOCUS_IN_POST)->Bind();
	//postProcShaders.at(FOCUS_IN_POST)->SendUniform("uTime", totalGameTime);
	//postProcShaders.at(RAINBOW_POST)->Bind();
	//postProcShaders.at(RAINBOW_POST)->SendUniform("uTime", totalGameTime);

	Shader::unbind();
	Input::ResetKeys();
	//lights[0]->GetTransform()->SetPos(glm::vec3(glm::sin(updateTimer->GetTimeCurrent() / 1000.f) * 5.0f, 1.0f, 1.3f));
}

void Game::draw()
{
	/// Clear Buffers ///
	mainBuffer->Clear();
	workBuffer1->Clear();
	workBuffer2->Clear();

	ShaderManager::update(*Camera::mainCamera);

	//Camera 1
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		//mainBuffer->Bind();

		for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
			m_activeScenes[i]->onRender();
			
		}

		//mainBuffer->Unbind();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	/// * Performs Frame buffer stuffs, don't remove pls and thank
	glEnable(GL_BLEND);
	ShaderManager::getPost(UI_POST)->bind();
	ShaderManager::getPost(UI_POST)->sendUniform("uiTex", 1);
	uiImage->Bind(1);
	ProcessFramebufferStuff(*mainBuffer, *workBuffer1, *workBuffer2, *workBuffer3,
								ShaderManager::getBloom(), *ShaderManager::getPost(UI_POST),
									true, false);
	uiImage->Unbind(1);
	glDisable(GL_BLEND);
	/// * Will be commented out in case this branch gets used for Expo
	//////////////////////////////////////////////////////////////////////////////////////////////
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
	}
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