#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__

#include "Shader.h"

#include <vector>


enum Shaders {
	PHONG_SHADER,

	NUM_SHADERS
};

enum PostProcess {
	GREYSCALE_POST,
	SEPIA_POST,
	FOCUS_IN_POST,
	INVERT_COLOR_POST,
	INVERT_LUMINENCE_POST,
	RAINBOW_POST,

	NUM_POST
};



class ShaderManager abstract
{
public:
	static void loadShaders();
	static void reloadShaders();
	static void unloadShaders();

	static void update(Camera& _camera);

	static Shader* getShader(int shader);


private:
	static std::vector<Shader*> m_shaders;
	static std::vector<Shader*> m_postShaders;
};

#endif