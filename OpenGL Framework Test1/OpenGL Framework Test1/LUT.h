#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "GL/glew.h"
#include "glm/common.hpp"

class LUT3D
{
public:
	LUT3D();
	LUT3D(std::string path);
	void loadFromFile(std::string path);
	void bind();
	void unbind();

	void bind(int textureSlot);
	void unbind(int textureSlot);
private:
	GLuint _Handle;
	std::vector<glm::vec3> data;
};