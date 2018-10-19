#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"


//All the shaders are written in separate files, this class only compiles the shaders into something readable by the GPU
class Shader
{
public:
	//Constructor
	//Shader(const std::string& fileName);

	//Alternate constructor for vert and frag shaders with diff names
	Shader(const std::string& vertFileName, const std::string& fragFileName = "");

	//Methods
		//Set the GPU to a state that makes it use the vertex and fragment shaders defined here
		void Bind();
		//Updates all the uniforms we have to be correct
		void Update(const Transform& transform, const Camera& camera);
		void OutputMessage();

		void setOptionalMessage(const std::string optionalMessage);
		void SetVec3(const GLchar* name, const float& x, const float& y, const float& z);
		void SetVec3(const GLchar* name, const glm::vec3& vec3);
		void SetVec4(const GLchar* name, const float& x, const float& y, const float& z, const float& w);
		void SetVec4(const GLchar* name, const glm::vec4& vec4);
		void SetFloat(const GLchar* name, const float& f);
		void SetInt(const GLchar* name, const int& i);
	//End Methods

	//Virtual Deconstructor
	virtual ~Shader();
private:
	//We are only using the fragment shader and vertex shaders right now.
	//Hence we only need 2 shaders.
	static const unsigned int NUM_SHADERS = 2;

	//Copy constructor
	Shader(const Shader& other) {}

	//Assignment operator overload
	void operator=(const Shader& other) {}

	//To help with future uniforms
	enum
	{
		MODEL_U,
		VIEW_U,
		PROJECTION_U,

		NUM_UNIFORMS
	};

	//Optional Message When Enabled
	std::string optionalMessage = "";

	//Handle for the program you create in the constructor
	//Allows you to affect the program later on
	GLuint m_program;

	//Holds the shaders
	GLuint m_shaders[NUM_SHADERS];

	//Holds the uniforms
	GLuint m_uniforms[NUM_UNIFORMS];
};
#endif //!__SHADER_H__

