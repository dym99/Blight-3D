#pragma once
#include <string>
#include <utility>
#include <glm/glm.hpp>
#include "GL/glew.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Camera.h"


class Shader
{
public:
	Shader();
	Shader(const std::string &vertFile, const std::string &fragFile, const std::string &geomFile="");
	~Shader();

	static bool InitDefault();
	void SetDefault();

	void Reload();

	bool Load(const std::string &vertFile, const std::string &fragFile, const std::string &geomFile="");
	bool IsLoaded() const;
	void Unload();
	bool LinkProgram();

	void update(Camera& camera);
	void bind() const;
	static void unbind();

	void sendUniform(const std::string &uniformName, const int &i) const;
	void sendUniform(const std::string &uniformName, const unsigned int &i) const;
	void sendUniform(const std::string &uniformName, const float &f) const;
	void sendUniform(const std::string &uniformName, const glm::vec2 &vector) const;
	void sendUniform(const std::string &uniformName, const float &x, const float &y) const;
	void sendUniform(const std::string &uniformName, const glm::vec3 &vector) const;
	void sendUniform(const std::string &uniformName, const float &x, const float &y, const float &z) const;
	void sendUniform(const std::string &uniformName, const glm::vec4 &vector) const;
	void sendUniform(const std::string &uniformName, const float &x, const float &y, const float &z, const float &w) const;
	void sendUniform(const std::string &uniformName, const glm::mat3 &matrix) const;
	void sendUniform(const std::string &uniformName, const glm::mat4 &matrix) const;
private:
	std::string vertShaderFile, fragShaderFile;
	std::string geomShaderFile = "";

	GLuint _VertexShader = GL_NONE;
	GLuint _FragShader = GL_NONE;
	GLuint _GeomShader = GL_NONE;
	GLuint _Program = GL_NONE;
	bool _IsInit = GL_FALSE;

	static bool _IsInitDefault;
	static GLuint _VertexShaderDefault;
	static GLuint _FragShaderDefault;
	static GLuint _ProgramDefault;

	std::string ReadFile(const std::string &fileName) const;
	bool CompileShader(GLuint shader) const;
	void OutputShaderLog(GLuint shader) const;
	void OutputProgramLog() const;

	GLint GetUniformLocation(const std::string &uniformName) const;
};