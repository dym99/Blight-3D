#include <iostream>
#include <GL/glew.h>
#include <ctime>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Interactions.h"

void PrepareForNextFrame(Camera* camera);

Display display(800, 600, "OpenGL Framework");
Shader* shaderHook;
std::vector<Shader*> shaders;


int main(int,char**) {
	Camera camera(glm::vec3(0, 0, 40), 70.f, (float)display.GetWidth() / (float)display.GetHeight(), 0.001f, 1000.f);

	Shader basicShader("./Resources/Shaders/basicShader");
	shaders.push_back(&basicShader);

	Mesh box;
	box.LoadFromFile("./Resources/Objects/Ravager/Ravager.obj");
	box.GetTransform()->getPos() -= glm::vec3(0, 5.f, 20.f);

	if (shaders.size() != 0)
		shaderHook = shaders.at(Interact::GetShaderIndex());

	PrepareForNextFrame(&camera);

	while (!display.isClosed()) {

		shaderHook->bind();
		//box.GetTransform()->getRot().y += glm::pi<float>();
		shaderHook->update(*box.GetTransform(), camera);
		box.Draw(shaderHook);

		PrepareForNextFrame(&camera);
	}
	return 0;
}

//Prepares everything for the next frame
void PrepareForNextFrame(Camera* camera)
{
	//Swaps buffers
	display.update();

	

	//Clears the Display and fills it with the background color
	display.clear(0.0f, 0.05f, 0.10f, 1.0f);
}
