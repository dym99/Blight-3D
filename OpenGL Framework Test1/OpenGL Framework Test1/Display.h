#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <SDL2/SDL.h>

#include <string>
#include <iostream>
#include <GL/glew.h>

class Display
{
public:
	Display(const std::string& title, int windowWidth, int windowHeight, bool resizable=false);
	virtual ~Display();

	void clear(float, float, float, float);
	void flip();


	void setWindowResizable(bool);
	void setFullscreen(Uint32);
	Uint32 getFullscreen();
	void close();

	inline bool isOpen() const { return m_open; }
private:
	Display(const Display&);
	SDL_Window *m_window;
	SDL_GLContext m_context;
	bool m_open;
	Uint32 m_fullscreen;
};

#endif