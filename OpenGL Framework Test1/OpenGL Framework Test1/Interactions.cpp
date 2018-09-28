#include "Interactions.h"
#include "Input.h"

bool Interact::rmb = false;
bool Interact::lmb = false;
bool Interact::isPaused = false;
bool Interact::objRotate = false;
bool Interact::activeWindow = true;
int Interact::deltPosX = 0;
int Interact::deltPosY = 0;
int Interact::shaderIndex = 0;
int Interact::modelIndex = 0;
Transform* Interact::transform = NULL;
Interact* Interact::instance = NULL;
std::unordered_map<std::string, const char*> Interact::paths = {
	{"crysis", "./Resources/Crysis/nanosuit.obj" },
	{"albeto", "./Resources/Albeto/scene.gltf" },
	{"lamp", "./Resources/cube.obj"},
	{"box", "./Resources/Box/box.obj" }
};

void Interact::interactionWithScene(/*vector<Model*>* models, vector<Model*>* lights,*/ Camera& camera, int numObj, int numShade, float dt, SDL_Window& window, Transform* _transform) {
	//if ((SDL_GetWindowFlags(&window) & SDL_WINDOW_INPUT_FOCUS) ? false : true) {
	//	info.activeWindow = false;
	//	info.cameraRot.isPausedObj = true;
	//}
	//else {
	//	info.activeWindow = true;
	//	info.cameraRot.isPausedObj = false;
	//}
	transform = _transform;
	if (activeWindow) {
		//Allows to change the selected object
		changeSelection(numObj);
		//Allows you to create a model based on inputs from numbers
		//createModel(models, lights, camera);
		//Allows to change the selected shader
		changeShader(numShade);
		//Allows for control over model translation
		translateModel();
		//Allows for control over model rotation
		rotateModel();
		//Allows for rotation of the camera
		rotateCamera(camera, window);
		//Allows for movement of the camera
		moveCamera(camera, dt);
		Input::ResetKeys();
	}
	SDL_GetRelativeMouseState(NULL, NULL);
}

//void Interact::createModel(vector<Model*>* models, vector<Model*>* lights, Camera& camera)
//{
//	int modelSize = models->size();
//	int lightSize = lights->size();
//	glm::vec3 position = camera.getPos() + (camera.getForward() * 2.f);
//	glm::vec3 lampScale(0.25f, 0.25f, 0.25f);
//	glm::vec3 modelScale(0.10f, 0.10f, 0.10f);
//
//	if (Input::GetKeyPress(KeyCode::NumPad0)) {
//		models->push_back(new Model(paths["box"]));
//		models->at(modelSize)->getTransform()->setPos(position);
//	}
//	if (Input::GetKeyPress(KeyCode::NumPad1)) {
//		models->push_back(new Model(paths["albeto"]));
//		models->at(modelSize)->getTransform()->setScale(lampScale);
//		models->at(modelSize)->getTransform()->setPos(position);
//	}
//	if (Input::GetKeyPress(KeyCode::NumPad2)) {
//		models->push_back(new Model(paths["crysis"]));
//		models->at(modelSize)->getTransform()->setScale(modelScale);
//		models->at(modelSize)->getTransform()->setPos(position);
//	}
//	if (Input::GetKeyPress(KeyCode::NumPad3)) {
//		lights->push_back(new Model(paths["lamp"]));
//		lights->at(lightSize)->getTransform()->setScale(lampScale);
//		lights->at(lightSize)->getTransform()->setPos(position);
//	}
//}

void Interact::changeSelection(int numObj)
{
	if (Input::GetKeyPress(KeyCode::Left)) {
		if (modelIndex == 0) {
			modelIndex = numObj - 1;
		}
		else {
			modelIndex--;
		}
	}
	if (Input::GetKeyPress(KeyCode::Right)) {
		if (modelIndex == numObj - 1) {
			modelIndex = 0;
		}
		else {
			modelIndex++;
		}
	}
}

void Interact::changeShader(int numShade) {
	if (Input::GetKeyPress(KeyCode::Subtract)) {
		if (shaderIndex == 0) {
			shaderIndex = numShade - 1;
		}
		else {
			shaderIndex--;
		}
	}
	if (Input::GetKeyPress(KeyCode::Add)) {
		if (shaderIndex == numShade - 1) {
			shaderIndex = 0;
		}
		else {
			shaderIndex++;
		}
	}
}

void Interact::translateModel()
{
	if (!lmb) {
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) {
			SDL_GetRelativeMouseState(NULL, NULL);
			lmb = true;
		}
	}
	else {
		if (SDL_GetRelativeMouseState(&deltPosX, &deltPosY) & SDL_BUTTON_LMASK) {
			glm::vec2 deltaPos(deltPosX, deltPosY);
			transform->getPos().x += deltaPos.x / 400;
			transform->getPos().y += -deltaPos.y / 400;
		}
		else {
			SDL_GetRelativeMouseState(NULL, NULL);
			lmb = false;
		}
	}
}

void Interact::rotateModel()
{
	if (!rmb) {
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_RMASK) {
			SDL_GetRelativeMouseState(NULL, NULL);
			rmb = true;
			objRotate = true;
		}
	}
	else {
		if (SDL_GetRelativeMouseState(&deltPosX, &deltPosY) & SDL_BUTTON_RMASK) {
			glm::vec2 deltaPos(deltPosX, deltPosY);
			transform->getRot().x += deltaPos.y * glm::pi<float>() / 400;
			transform->getRot().y += deltaPos.x * glm::pi<float>() / 400;
		}
		else {
			SDL_GetRelativeMouseState(NULL, NULL);
			rmb = false;
			objRotate = false;
		}
	}
}

void Interact::rotateCamera(Camera& camera, SDL_Window& window)
{
	//Gets key press for escape
	if (Input::GetKeyPress(KeyCode::Escape)) {
		isPaused = !isPaused;
	}
	//If camera is not paused, this line will basically make the mouse
	//invisible and motionless but, make it so it still records the motion, allowing for
	//Rotation without fear of mouse going out of window.
	if (!isPaused) {
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	else {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}

	SDL_GetRelativeMouseState(&deltPosX, &deltPosY);
	if (!isPaused && !objRotate) {
		glm::vec3 rotation(0.0, 0.0, 0.0);
		int deltaPosYAlt = deltPosY * -1;
		glm::vec2 deltaPos(-deltPosX, -deltPosY);
	    if (camera.getPos().z > 0.0) {
			deltaPos.y = deltaPosYAlt;
		}
		else {
			deltaPos.y = deltPosY;
		}
		rotation.x += deltaPos.y * glm::pi<float>() / 400;
		rotation.y += deltaPos.x * glm::pi<float>() / 400;

		glm::mat4 rotationXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

		glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

		camera.rotate(rotationMatrix);
		camera.rotateSideways(rotationYMatrix);
	}
}

void Interact::moveCamera(Camera& camera, float dt) {
	//Holds the movement on the axes
	glm::vec3 forwardBack = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rightLeft = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 upDown = glm::vec3(0.0f, 0.0f, 0.0f);
	
	if (Input::GetKey(KeyCode::W)) {
		glm::vec3 forward = camera.getForward();
		forwardBack += forward * dt;
	}
	if (Input::GetKey(KeyCode::A)) {
		glm::vec3 left = camera.getSideways();
		rightLeft += left * dt;
	}
	if (Input::GetKey(KeyCode::S)) {
		glm::vec3 back = glm::vec3(-1 * camera.getForward().x, -1 * camera.getForward().y, -1 * camera.getForward().z);
		forwardBack += back * dt;
	}
	if (Input::GetKey(KeyCode::D)) {
		glm::vec3 right = glm::vec3(-1 * camera.getSideways().x, -1 * camera.getSideways().y, -1 * camera.getSideways().z);
		rightLeft += right * dt;
	}
	if (Input::GetKey(KeyCode::Space)) {
		glm::vec3 up = glm::vec3(0, 1, 0);
		upDown += up * dt;
	}
	if (Input::GetKey(KeyCode::Shift)) {
		glm::vec3 down = glm::vec3(0, -1, 0);
		upDown += down * dt;
	}

	glm::vec3 translate = forwardBack + rightLeft + upDown;
	glm::mat4 transMatrix = glm::translate(translate);

	camera.translate(transMatrix);
}
