#ifndef __GAME_H__
#define __GAME_H__
#include "Timer.h"
#include "Scene.h"
#include "Shader.h"
#include "Interactions.h"

class Game {
public:
	Game();
	~Game();

	void initGame(bool* debug);
	void update();
	void draw();

	void keyboardUp();
	void keyboardDown();
	void keyboardPress();

	//Camera stuff
	Camera* camera;

	//Hooks
	Shader* shaderHook;
	std::vector<Model*> modelHook;

	//Plain white shader
	Shader* lampShader;

	//Hook to enable and disable debug features
	bool* debugFeatures;

	//Helpers
	Model& getPlayer() { return *player; }
	std::vector<Model*>* getEnemies() { return &enemies; }
	std::vector<Model*>* getEnvironments() { return &environments; }
	std::vector<Model*>* getLights() { return &lights; }
	std::vector<Shader*>* getShaders() { return &shaders; }

	//Time stuff
	Timer *updateTimer = nullptr;
	float totalGameTime = 0.0f;
private:
	//Object stuff
	Model* player;						//Player object
	std::vector<Model*> enemies;		//Enemy Objects
	std::vector<Model*> environments;	//Environment Objects (Walls, Floors, flora, fauna)
	std::vector<Model*> lights;			//Lighting Objects (Handle with Care)

	//Shader stuff
	std::vector<Shader*> shaders;		//Shader objects

	//Loads in scene info
	Scene* scene;
};

#endif