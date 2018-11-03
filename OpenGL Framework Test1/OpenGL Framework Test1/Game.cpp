#include "Game.h"
#include <iostream>
#include "MeshRenderBehaviour.h"
#include "TestRotateBehaviour.h"
#include "MouseLook.h"
#include "CameraBehaviour.h"
Game::Game()
{
}

Game::~Game()
{
	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i] = nullptr;
	}
	m_activeScenes.clear();
}

void Game::initGame()
{
	///Initialise SDL
	initSDL();

	///Initialise the display
	m_display = new Display("Blight");

	///Initialise GLEW
	initGLEW();

	//Initialise Camera
	auto camera = new Camera();
	camera->perspective(70.f, 16.f/9.f, 0.001f, 1000.f);
	camera->setPos(glm::vec3(0.f, 0.f, 3.0f));
	Camera::mainCamera = camera;
	//Load in resources
	m_ravager = new Model();
	m_ravager->LoadFromFile("./Resources/Objects/Ravager2/", "Ravager");
	m_testArea = new Model();
	m_testArea->LoadFromFile("./Resources/Objects/TestArea/", "TestArea");
	
	//Load shaders
	m_shader = new Shader("./Resources/Shaders/basicShader");
	m_shader->bind();
	m_shader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	m_shader->setVec3("viewPosition", camera->getPos().x, camera->getPos().y, camera->getPos().z);
	m_shader->setVec3("light.position", 0.f, 1.f, 1.f);
	m_shader->setVec3("light.color", 0.0f, 1.0f, 0.0f);
	m_shader->setVec3("light.ambience", 0.5f, 0.5f, 0.5f);
	m_shader->setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
	m_shader->setVec3("light.specular", 1.f, 1.f, 1.f);
	m_shader->setFloat("light.constant", 1.0f);
	m_shader->setFloat("light.linear", 0.09f);
	m_shader->setFloat("light.quadratic", 0.032f);
	m_shader->setFloat("material.shininess", 32.0f);

	//Set up the test Scene

	auto ravager = new GameObject("Ravager");
	ravager->addBehaviour(new MeshRenderBehaviour(m_ravager, m_shader));

	auto cameraPivot = new GameObject("CameraPivot");
	cameraPivot->localTransform.setPos(glm::vec3(0.f,1.f,0.f));
	cameraPivot->addBehaviour(new MouseLook(ravager));

	auto cameraObject = new GameObject("Camera");

	cameraObject->localTransform.setPos(glm::vec3(0, 0, 3.f));

	camera->setTransform(&cameraObject->worldTransform);

	cameraPivot->addChild(cameraObject);
	ravager->addChild(cameraPivot);
	

	auto testArea = new GameObject("TestArea");
	testArea->addBehaviour(new MeshRenderBehaviour(m_testArea, m_shader));


	auto scene = new Scene("DemoScene");
	scene->addChild(ravager);
	scene->addChild(testArea);

	

	m_activeScenes.push_back(scene);
}

void Game::update()
{
	Time::update();

	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i]->update();
	}
}

void Game::draw()
{
	for (unsigned int i = 0; i < m_activeScenes.size(); ++i) {
		m_activeScenes[i]->onRender();
	}
}

int Game::run() {
	while (m_display->isOpen()) {

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
	///End Attributes
}