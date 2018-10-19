#ifndef __INTERACTIONS_H__
#define __INTERACTIONS_H__
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "Display.h"
#include "Input.h"
#include <unordered_map>

class Interact {
public:
	static void InteractionWithScene(std::vector<Model*>* models, std::vector<Model*>* lights, Camera& camera, int numShade, float dt, SDL_Window& window, Transform* transform = &Transform());

	static int GetShaderIndex() { return shaderIndex; }
	static int GetModelIndex() { return modelIndex; }
	static Transform* GetTransform() { return transform; }

	static void SetShaderIndex(int index) { shaderIndex = index; }
	static void SetModelIndex(int index) { modelIndex = index; }
private:
	//Private methods so that only interact with scene can be called
	static void CreateModel(std::vector<Model*>* models, std::vector<Model*>* lights, Camera& camera);
	static void ChangeSelection(int numObj);
	static void ChangeShader(int numShade);
	static void TranslateModel(Camera& camera, float dt);
	static void RotateModel();
	static void RotateCamera(Camera& camera, SDL_Window& window);
	static void MoveCamera(Camera& camera, float dt);

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