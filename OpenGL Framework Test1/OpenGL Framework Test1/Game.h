#ifndef __GAME_H__
#define __GAME_H__
#include "Timer.h"
#include "Scene.h"
#include "Shader.h"
#include "Interactions.h"
#include "FrameBuffer.h"
#include "Utilities.h"

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

class Game {
public:
	Game();
	~Game();

	void InitGame(bool* debug);
	void InitUniforms();
	void Update();
	void Draw();

	void KeyboardUp();
	void KeyboardDown();
	void KeyboardPress();

	//Camera
	Camera* camera;

	//Timer
	Timer *updateTimer = nullptr;
	float totalGameTime = 0.0f;

	//Hooks
	Shader* shaderHook;
	Shader* postProcShaderHook;
	std::vector<Model*> modelHook;

	//Framebuffers
	FrameBuffer mainBuffer;
	FrameBuffer workBuffer1;
	FrameBuffer workBuffer2;
	FrameBuffer workBuffer3;

	//Helpers
	Model& GetPlayer() { return *player; }
	std::vector<Model*>* GetEnemies() { return &enemies; }
	std::vector<Model*>* GetEnvironments() { return &environments; }
	std::vector<Model*>* GetLights() { return &lights; }
	std::vector<Shader*>* GetShaders() { return &shaders; }
private:

	//Models stuff
	Model* player;						//Player object
	std::vector<Model*> enemies;		//Enemy Objects
	std::vector<Model*> environments;	//Environment Objects (Walls, Floors, flora, fauna)
	std::vector<Model*> lights;			//Lighting Objects (Handle with Care)

	//Shaders
	Shader* lampShader;						//Plain white shader
	std::vector<Shader*> shaders;			//Shader objects
	std::vector<Shader*> postProcShaders;	//post processing shaders
	std::vector<Shader*> bloomComponents;	//Bloom components

	//Indexes
	int postProcShaderIndex = 0;

	//Hook to enable and disable debug features
	bool* debugFeatures;

	//Booleans to control framebuffer aspects
	bool frameBuffer = false;
	bool postProc = false;
	bool hasBloom = false;
};

#endif