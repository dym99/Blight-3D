#ifndef  __DISPLAY_H__
#define __DISPLAY_H__

#include <SDL2\SDL.h>
#include <string>


class Display
{
public:
	//Constructor
	Display(int width, int height, const std::string& name);
	
	//Methods to be used
		//Wraps GLEW logic to just clear from the display object
		void Clear(float r, float g, float b, float a);
		//Swaps between the two buffers and performs event handling
		void Update();
		//Checks if the window is closed
		bool IsClosed();
		//Gets window handle
		inline SDL_Window& GetWindow() { return *m_window; }
		//Gets width
		inline int GetWidth() { return m_width; }
		//Gets height
		inline int GetHeight() { return m_height; }
	//End methods

	//Virtual Deconstructor
	virtual ~Display();

private:
	//Copy constructor
	Display(const Display& other) {}

	//Assignment operator overload
	void operator=(const Display& other) {}

	//My window
	SDL_Window* m_window;

	//Creates context
	SDL_GLContext m_glContext;

	//Whether window is open or closed
	bool m_isClosed;

	int m_width;
	int m_height;
};

#endif // !__DISPLAY_H__