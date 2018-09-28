#ifndef __INTERACTIONS_H__
#define __INTERACTIONS_H__
#include "Transform.h"
#include "Camera.h"
//#include "Model.h"
#include "Display.h"
#include <unordered_map>

class Interact {
public:
	static void interactionWithScene(/*vector<Model*>* models, vector<Model*>* lights, */Camera& camera, int numObj, int numShade, float dt, SDL_Window& window, Transform* transform = &Transform());

	static int GetShaderIndex() { return shaderIndex; }
	static int GetModelIndex() { return modelIndex; }
	static Transform* GetTransform() { return transform; }
private:
	//Private methods so that only interact with scene can be called
	//static void createModel(vector<Model*>* models, vector<Model*>* lights, Camera& camera);
	static void changeSelection(int numObj);
	static void changeShader(int numShade);
	static void translateModel();
	static void rotateModel();
	static void rotateCamera(Camera& camera, SDL_Window& window);
	static void moveCamera(Camera& camera, float dt);

	//Containers
	static bool rmb;
	static bool lmb;
	static bool isPaused;
	static bool objRotate;
	static bool activeWindow;
	static int deltPosX;
	static int deltPosY;
	static int shaderIndex;
	static int modelIndex;
	static std::unordered_map<std::string, const char*> paths;
	static Transform* transform;
	static Interact* instance;
};

#endif // !__INTERACTIONS_H__