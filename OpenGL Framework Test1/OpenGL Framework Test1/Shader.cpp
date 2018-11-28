#define _CRT_SECURE_NO_WARNINGS
#include "Shader.h"

 bool   Shader::_IsInitDefault = GL_FALSE;
 GLuint Shader::_VertexShaderDefault = GL_NONE;
 GLuint Shader::_FragShaderDefault = GL_NONE;
 GLuint Shader::_ProgramDefault = GL_NONE;

#define CHAR_BUFFER_SIZE 128

Shader::Shader()
{
}

Shader::Shader(const std::string & vertFile, const std::string & fragFile)
{
	Load(vertFile, fragFile);
}

Shader::~Shader()
{
	if (_IsInit)
	{
		Unload();
	}
}

bool Shader::InitDefault()
{
	if (!_IsInitDefault)
	{
		Shader errorShader;
		bool compileSuccess = errorShader.Load("./Resources/Shaders/error.vert", "./Resources/Shaders/error.frag");
		if (!compileSuccess)
		{
			std::cout << "Could not compile default shader!";
			system("pause");
			exit(EXIT_FAILURE);
		}


		_VertexShaderDefault =	errorShader._VertexShader;
		_FragShaderDefault =	errorShader._FragShader;
		_ProgramDefault =		errorShader._Program;
		_IsInitDefault =		true;
	}
	return _IsInitDefault;
}

void Shader::SetDefault()
{
	_VertexShader = _VertexShaderDefault;
	_FragShader = _FragShaderDefault;
	_Program = _ProgramDefault;
}

void Shader::Reload()
{
	Load(vertShaderFile, fragShaderFile);
}

bool Shader::Load(const std::string & vertFile, const std::string & fragFile)
{
	vertShaderFile = vertFile;
	fragShaderFile = fragFile;
	_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	_Program = glCreateProgram();

	std::string source = ReadFile(vertFile);
	const GLchar *temp = static_cast<const GLchar*>(source.c_str());
	glShaderSource(_VertexShader, 1, &temp, NULL);

	source = ReadFile(fragFile);
	temp = static_cast<const GLchar*>(source.c_str());
	glShaderSource(_FragShader, 1, &temp, NULL);

	if (!CompileShader(_VertexShader))
	{
		std::cout << "Vertex Shader failed to compile.\n";
		OutputShaderLog(_VertexShader);
		Unload();
		SetDefault();
		return false;
	}
	if (!CompileShader(_FragShader))
	{
		std::cout << "Fragment SHader failed to compile.\n";
		OutputShaderLog(_FragShader);
		Unload();
		SetDefault();
		return false;
	}

	glAttachShader(_Program, _VertexShader);
	glAttachShader(_Program, _FragShader);

	if (!LinkProgram())
	{
		std::cout << "Shader failed to link.\n";
		OutputProgramLog();
		Unload();
		return false;
	}

	_IsInit = true;
	return true;
}

bool Shader::IsLoaded() const
{
	return _IsInit;
}

void Shader::Unload()
{
	if (_VertexShader != GL_NONE && _VertexShader != _VertexShaderDefault)
	{
		glDetachShader(_Program, _VertexShader);
		glDeleteShader(_VertexShader);
		_VertexShader = GL_NONE;
	}
	if (_FragShader != GL_NONE && _FragShader != _FragShaderDefault) 
	{
		glDetachShader(_Program, _FragShader);
		glDeleteShader(_FragShader);
		_FragShader = GL_NONE;
	}
	if (_Program != GL_NONE && _Program != _ProgramDefault)
	{
		glDeleteProgram(_Program);
		_Program = GL_NONE;
	}
}

bool Shader::LinkProgram()
{
	glLinkProgram(_Program);
	GLint success;
	glGetProgramiv(_Program, GL_LINK_STATUS, &success);
	return (success == GL_TRUE);
}

void Shader::update(Camera & camera)
{
	glm::mat4 view = camera.getView();
	glm::mat4 proj = camera.GetProjection();

	sendUniform("uView", view);
	sendUniform("uProj", proj);
}

void Shader::bind() const
{
	glUseProgram(_Program);
}

void Shader::unbind()
{
	glUseProgram(GL_NONE);
}

GLint Shader::GetUniformLocation(const std::string & uniformName) const
{
	GLint uniLoc = glGetUniformLocation(_Program, static_cast<const GLchar*>(uniformName.c_str()));
#if _DEBUG
	if (uniLoc == -1 && _Program != _ProgramDefault)
	{
		//std::cerr << "WARNING: Uniform " << uniformName << " does not exist!\n";
	}
#endif

	return uniLoc;
}

void Shader::sendUniform(const std::string & uniformName, const int & i) const
{
	GLint loc = GetUniformLocation(uniformName);
	glUniform1i(loc, i);
}

void Shader::sendUniform(const std::string & uniformName, const unsigned int & i) const
{
	GLint loc = GetUniformLocation(uniformName);
	glUniform1i(loc, i);
}

void Shader::sendUniform(const std::string & uniformName, const float & f) const
{
	GLint loc = GetUniformLocation(uniformName);
	glUniform1f(loc, f);
}

void Shader::sendUniform(const std::string & uniformName, const glm::vec2 & vector) const
{
	GLint loc = GetUniformLocation(uniformName);
	GLfloat vec[2] = { vector.x, vector.y };
	glUniform2fv(loc, 1, vec);
}

void Shader::sendUniform(const std::string & uniformName, const float & x, const float & y) const
{
	GLint loc = GetUniformLocation(uniformName);
	GLfloat vec[2] = { x, y };
	glUniform2fv(loc, 1, vec);
}

void Shader::sendUniform(const std::string & uniformName, const glm::vec3 & vector) const
{
	GLint loc = GetUniformLocation(uniformName);
	GLfloat vec[3] = { vector.x, vector.y, vector.z };
	glUniform3fv(loc, 1, vec);
}

void Shader::sendUniform(const std::string & uniformName, const float & x, const float & y, const float & z) const
{
	GLint loc = GetUniformLocation(uniformName);
	GLfloat vec[3] = { x, y, z };
	glUniform3fv(loc, 1, vec);
}

void Shader::sendUniform(const std::string & uniformName, const glm::vec4 & vector) const
{
	GLint loc = GetUniformLocation(uniformName);
	GLfloat vec[4] = { vector.x, vector.y, vector.z, vector.w };
	glUniform4fv(loc, 1, vec);
}

void Shader::sendUniform(const std::string & uniformName, const float & x, const float & y, const float & z, const float & w) const
{
	GLint loc = GetUniformLocation(uniformName);
	GLfloat vec[4] = { x, y, z, w };
	glUniform4fv(loc, 1, vec);
}

void Shader::sendUniform(const std::string & uniformName, const glm::mat3 & matrix) const
{
	GLint loc = GetUniformLocation(uniformName);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::sendUniform(const std::string & uniformName, const glm::mat4 & matrix) const
{
	GLint loc = GetUniformLocation(uniformName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

std::string Shader::ReadFile(const std::string & fileName) const
{
	std::ifstream inStream(fileName);
	std::cout << "Shader: " << fileName << " .";
	if (!inStream.good())
	{
		std::cout << ".. failed to load\n";
		return std::string();
	}
	
	std::cout << ".. loaded successfully\n";
	
	std::string data(std::istreambuf_iterator<char>(inStream), (std::istreambuf_iterator<char>()));
	return data;
}

bool Shader::CompileShader(GLuint shader) const
{
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	return success == GL_TRUE;
}

void Shader::OutputShaderLog(GLuint shader) const
{
	GLchar error[1024] = { 0 };

	glGetShaderInfoLog(shader, sizeof(error), NULL, error);

	std::cerr << "'" << error << "'" << std::endl;
}

void Shader::OutputProgramLog() const
{
	GLchar error[1024] = { 0 };

	glGetProgramInfoLog(_Program, sizeof(error), NULL, error);

	std::cerr << "'" << error << "'" << std::endl;
}
