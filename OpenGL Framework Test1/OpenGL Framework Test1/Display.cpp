#include "Display.h"
#include "Utilities.h"


Display::Display(const std::string& title, int windowWidth, int windowHeight, bool resizable)
{
	m_open = true;
	//Create the window as a gl context
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	//Check to make sure window is created properly
	if (m_window == NULL) {
#ifdef _DEBUG
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
#endif
	}
	else {
		//Create context
		m_context = SDL_GL_CreateContext(m_window);

		setWindowResizable(resizable);

		//Check to make sure gl context is created properly
		if (m_context == NULL) {
#ifdef _DEBUG
			std::cerr << "Failed to create gl context!" << std::endl;
#endif
			close();
		}
	}
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void Display::setWindowResizable(bool resizable)
{
	SDL_SetWindowResizable(m_window, SDL_bool(resizable));
}

void Display::setFullscreen(Uint32 flags) {
	SDL_SetWindowFullscreen(m_window, flags);
	m_fullscreen = flags;
}

Uint32 Display::getFullscreen() {
	return m_fullscreen;
}

void Display::close() {
	m_open = false;
}

void Display::flip() {
	SDL_GL_SwapWindow(m_window);
}

void Display::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}