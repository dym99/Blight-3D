#include "Interactions.h"
#include <iostream>

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
	{"crysis", "./Resources/Objects/Crysis/" },
	{"Ravager", "./Resources/Objects/Ravager2/" },
	{"box", "./Resources/Objects/Box/"},
	{"lamp", "./Resources/Objects/Lamp/" }
};

void Interact::InteractionWithScene(std::vector<Model*>* models, std::vector<Model*>* lights, Camera& camera, int numShade, float dt, SDL_Window& window, Transform* _transform) {
	transform = _transform;
	int numObj = (int)models->size();
	if (activeWindow) {
		//Allows to change the selected object
		ChangeSelection(numObj);
		//Allows you to create a model based on inputs from numbers
		//Allows to change the selected shader
		ChangeShader(numShade);
		//Allows for control over model translation
		TranslateModel(camera, dt);
		//Allows for control over model rotation
		RotateModel();
		//Allows for rotation of the camera
		RotateCamera(camera, window);
		//Allows for movement of the camera
		MoveCamera(camera, dt);
	}
	SDL_GetRelativeMouseState(NULL, NULL);
}

//void Interact::CreateModel(std::vector<Model*>* models, std::vector<Model*>* lights, Camera& camera)
//{
//	int modelSize = models->size();
//	int lightSize = lights->size();
//	glm::vec3 position = camera.GetPos() + (camera.GetForward() * 2.f);
//	glm::vec3 lampScale(0.25f, 0.25f, 0.25f);
//	glm::vec3 modelScale(0.10f, 0.10f, 0.10f);
//
//	//Draws Box
//	if (Input::GetKeyPress(KeyCode::NumPad0)) {
//		models->push_back(new Model());
//		models->at(modelSize)->LoadFromFile(paths["box"], "cube");
//		models->at(modelSize)->GetTransform()->SetPos(position);
//	}
//	else if (Input::GetKeyPress(KeyCode::NumPad1)) {
//		models->push_back(new Model());
//		models->at(modelSize)->LoadFromFile(paths["Ravager"], "Ravager");
//		models->at(modelSize)->GetTransform()->SetScale(lampScale);
//		models->at(modelSize)->GetTransform()->SetPos(position);
//	}
//	else if (Input::GetKeyPress(KeyCode::NumPad2)) {
//		models->push_back(new Model());
//		models->at(modelSize)->LoadFromFile(paths["crysis"], "nanosuit");
//		models->at(modelSize)->GetTransform()->SetScale(modelScale);
//		models->at(modelSize)->GetTransform()->SetPos(position);
//	}
//	/*else if (Input::GetKeyPress(KeyCode::NumPad3)) {
//		lights->push_back(new Model());
//		models->at(modelSize)->LoadFromFile(paths["lamp"], "lamp");
//		lights->at(lightSize)->GetTransform()->setScale(lampScale);
//		lights->at(lightSize)->GetTransform()->setPos(position);
//	}*/
//}

void Interact::ChangeSelection(int numObj)
{
	if (Input::GetKeyPress(KeyCode::Left)) {
		if (modelIndex == 0) {
			modelIndex = numObj - 1;
		}
		else {
			modelIndex--;
		}
		std::cout << "You are now in control of Model number " << modelIndex + 1 << '\n';
	}
	if (Input::GetKeyPress(KeyCode::Right)) {
		if (modelIndex == numObj - 1) {
			modelIndex = 0;
		}
		else {
			modelIndex++;
		}
		std::cout << "You are now in control of Model number " << modelIndex + 1 << '\n';
	}
}

void Interact::ChangeShader(int numShade) {
	if (Input::GetKeyPress(KeyCode::Subtract)) {
		if (shaderIndex == 0) {
			shaderIndex = numShade - 1;
		}
		else {
			shaderIndex--;
		}
		std::cout << "You are now using shader number " << shaderIndex + 1 << '\n';
	}
	if (Input::GetKeyPress(KeyCode::Add)) {
		if (shaderIndex == numShade - 1) {
			shaderIndex = 0;
		}
		else {
			shaderIndex++;
		}
		std::cout << "You are now using shader number " << shaderIndex + 1 << '\n';
	}
}

void Interact::TranslateModel(Camera& camera, float dt)
{
	/*if (!lmb) {
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
	}*/
	glm::vec3 forwardBack = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rightLeft = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 upDown = glm::vec3(0.0f, 0.0f, 0.0f);

	int modifier = -1;

	if (Input::GetKey(KeyCode::I)) {
		glm::vec3 forward = glm::vec3(-modifier * camera.GetForward().x, -modifier * camera.GetForward().y, -modifier * camera.GetForward().z);
		forwardBack += forward * dt;
	}
	else if (Input::GetKey(KeyCode::K)) {
		glm::vec3 back = glm::vec3(modifier * camera.GetForward().x, modifier * camera.GetForward().y, modifier * camera.GetForward().z);
		forwardBack += back * dt;
	}
	if (Input::GetKey(KeyCode::J)) {
		glm::vec3 left = glm::vec3(-modifier * camera.GetSideways().x, -modifier * camera.GetSideways().y, -modifier * camera.GetSideways().z);
		rightLeft += left * dt;
	}
	else if (Input::GetKey(KeyCode::L)) {
		glm::vec3 right = glm::vec3(modifier * camera.GetSideways().x, modifier * camera.GetSideways().y, modifier * camera.GetSideways().z);
		rightLeft += right * dt;
	}
	if (Input::GetKey(KeyCode::O)) {
		glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
		upDown += up * dt;
	}
	else if (Input::GetKey(KeyCode::U)) {
		glm::vec3 down = glm::vec3(0.f, -1.f, 0.f);
		upDown += down * dt;
	}

	transform->getPos() += forwardBack + rightLeft + upDown;
}

void Interact::RotateModel()
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

void Interact::RotateCamera(Camera& camera, SDL_Window& window)
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
		glm::vec2 deltaPos(-deltPosX, -deltPosY);

		if (camera.GetForward().z > 0) {
			deltaPos.y *= -1;
		}

		rotation.x += deltaPos.y * glm::pi<float>() / 400;
		rotation.y += deltaPos.x * glm::pi<float>() / 400;

		glm::mat4 rotationXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));

		glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

		camera.Rotate(rotationMatrix);
		camera.RotateSideways(rotationYMatrix);
	}
}

void Interact::MoveCamera(Camera& camera, float dt) {
	//Holds the movement on the axes
	glm::vec3 forwardBack = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rightLeft = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 upDown = glm::vec3(0.0f, 0.0f, 0.0f);
	
	int modifier = -1;

	//if (camera.getForward().z > 0) {
	//	modifier = 1;
	//}

	if (Input::GetKey(KeyCode::W)) {
		glm::vec3 forward = glm::vec3(-modifier * camera.GetForward().x, -modifier * camera.GetForward().y, -modifier * camera.GetForward().z);
		forwardBack += forward * dt;
	}
	else if (Input::GetKey(KeyCode::S)) {
		glm::vec3 back = glm::vec3(modifier * camera.GetForward().x, modifier * camera.GetForward().y, modifier * camera.GetForward().z);
		forwardBack += back * dt;
	}
	if (Input::GetKey(KeyCode::A)) {
		glm::vec3 left = glm::vec3(-modifier * camera.GetSideways().x, -modifier * camera.GetSideways().y, -modifier * camera.GetSideways().z);
		rightLeft += left * dt;
	}
	else if (Input::GetKey(KeyCode::D)) {
		glm::vec3 right = glm::vec3(modifier * camera.GetSideways().x, modifier * camera.GetSideways().y, modifier * camera.GetSideways().z);
		rightLeft += right * dt;
	}
	if (Input::GetKey(KeyCode::Space)) {
		glm::vec3 up = glm::vec3(0, 1, 0);
		upDown += up * dt;
	}
	else if (Input::GetKey(KeyCode::Shift)) {
		glm::vec3 down = glm::vec3(0, -1, 0);
		upDown += down * dt;
	}

	glm::vec3 translate = forwardBack + rightLeft + upDown;
	glm::mat4 transMatrix = glm::translate(translate);

	camera.Translate(transMatrix);
}
