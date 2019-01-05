#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__

#include "Shader.h"

#include <vector>


enum Shaders {
	PHONG_SHADER,
	GBUFFER_SHADER,

	NUM_SHADERS
};

enum Geom {
	BILLBOARD_GEOM,

	NUM_GEOM
};

enum PostProcess {
	DEFERREDLIGHT_POST,
	GREYSCALE_POST,
	SEPIA_POST,
	FOCUS_IN_POST,
	INVERT_COLOR_POST,
	INVERT_LUMINENCE_POST,
	RAINBOW_POST,
	UI_POST,
	PASSTHROUGH_POST,

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
	static Shader* getGeom(int geom);
	static Shader* getPost(int post);
	
	static std::vector<Shader*>& getBloom();


private:
	static std::vector<Shader*> m_shaders;
	static std::vector<Shader*> m_geomShaders;
	static std::vector<Shader*> m_postShaders;
	static std::vector<Shader*> m_bloomComponents;
};

#endif