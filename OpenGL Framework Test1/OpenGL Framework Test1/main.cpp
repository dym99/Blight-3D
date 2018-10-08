#include <iostream>
#include <GL/glew.h>
#include <ctime>
#include "Display.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Interactions.h"

void PrepareForNextFrame(Camera* camera);

Display display(800, 600, "OpenGL Framework");
glm::vec3 objScale = glm::vec3(0.05f, 0.05f, 0.05f);
glm::vec3 objPosition = glm::vec3(0.f, 0.f, 0.f);
Shader* shaderHook;
std::vector<Shader*> shaders;


int main(int,char**) {
	Camera camera(glm::vec3(0, 0, 3.f), 70.f, (float)display.GetWidth() / (float)display.GetHeight(), 0.001f, 1000.f);

	Shader basicShader("./Resources/Shaders/basicShader");
	shaders.push_back(&basicShader);
	{
		basicShader.bind();
		basicShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		basicShader.setVec3("viewPosition", camera.getPos().x, camera.getPos().y, camera.getPos().z);
		basicShader.setVec3("light.position", 0.f, 1.f, 1.f);
		basicShader.setVec3("light.color", 0.0f, 1.0f, 0.0f);
		basicShader.setVec3("light.ambience", 0.5f, 0.5f, 0.5f);
		basicShader.setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
		basicShader.setVec3("light.specular", 1.f, 1.f, 1.f);
		basicShader.setFloat("light.constant", 1.0f);
		basicShader.setFloat("light.linear", 0.09f);
		basicShader.setFloat("light.quadratic", 0.032f);
		basicShader.setFloat("material.shininess", 32.0f);
	}

	Model box;
	box.LoadFromFile("./Resources/Objects/Crysis/", "nanosuit");
	box.GetTransform()->setScale(objScale);
	box.GetTransform()->getPos() += glm::vec3(0.f, -0.5f, 2.25f);

	if (shaders.size() != 0)
		shaderHook = shaders.at(Interact::GetShaderIndex());

	PrepareForNextFrame(&camera);

	while (!display.isClosed()) {
		
		shaderHook->bind();
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
