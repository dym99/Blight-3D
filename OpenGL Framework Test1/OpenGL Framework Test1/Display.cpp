#include "Display.h"
#include <GL/glew.h>
#include <iostream>

//Creates the display to be used.
Display::Display(int width, int height, const std::string& name) : m_width(width), m_height(height)
{
	//Initializes everything (because the tutorial guy was too lazy to init individually)
	//If you plan on using SDL for anything other than just drawing the window, DO NOT USE THIS
	SDL_Init(SDL_INIT_EVERYTHING);

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
	///End Attributes

	//Creates the window.
	//SDL is C based, hence we can't use the c++ string
	//We must use the .c_str() method.
	m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//Set GL context version (for RenderDoc stuffs)
	if (m_window != NULL) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	}

	//Creates the context for the window, such that OpenGL can actually draw to the window
	m_glContext = SDL_GL_CreateContext(m_window);

	//Holds the result of the initialization of glew.
	//glewInit finds every OpenGl function that our system supports
	GLenum status = glewInit();

	//Checks if glewInit didn't returned okay.
	if (status != GLEW_OK) 
	{
		//If it didn't, prints an error message
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	m_isClosed = false;

	//Enables the depth test
	
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//If the face is facing away from the camera, we don't draw it;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

}

//Deconstructs the display and performs cleanup
Display::~Display()
{
	//Cleans up after all the data you created in the constructor
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);

	//Will just uninitialized anything that has been initialized, in this case... everything
	SDL_Quit();
}

//Clears the window using the clear color
void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Swaps between the two buffers and performs event handling
void Display::Update()
{
	//Swaps the buffers on the screen.
	//We are double buffering things. 
	//The one buffer is the one that OpenGL is drawing on.
	//The other is the buffer that is displayed.
	//When OpenGL finishes drawing, we swap the buffer.
	//This lets OpenGL draw on the other one and then displays the other one.
	SDL_GL_SwapWindow(m_window);

	//Handles events
	SDL_Event e;

	//Searches for any event that might occur and takes the address of that event and stores it in e.
	while (SDL_PollEvent(&e)) 
	{
		//Checks for a specific type of event.
		if (e.type == SDL_QUIT) {
			//Sets the closed boolean to true
			m_isClosed = true;
		}
	}
}

//Checks if the window is closed.
bool Display::IsClosed()
{
	return m_isClosed;
}
