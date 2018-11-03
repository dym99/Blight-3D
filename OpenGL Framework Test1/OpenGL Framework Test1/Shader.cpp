#include "Shader.h"
#include <iostream>
#include <fstream>
#include "Mesh.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

//Constructs the shader object.
Shader::Shader(const std::string& vertFileName, const std::string& fragFileName)
{
	//Creates the program (allocates space for it), and returns a handle to that created program
	m_program = glCreateProgram();
	
	//Grabs the files and creates the shader based on the loaded data and the shader type
	//I used ".vert" and ".frag" for the vertex and fragment shaders respectfully
	//But you can use anything you want.
	if (fragFileName == "")
	{
		m_shaders[0] = CreateShader(LoadShader(vertFileName + ".vert"), GL_VERTEX_SHADER);
		m_shaders[1] = CreateShader(LoadShader(vertFileName + ".frag"), GL_FRAGMENT_SHADER);
	}
	else 
	{
		m_shaders[0] = CreateShader(LoadShader(vertFileName + ".vert"), GL_VERTEX_SHADER);
		m_shaders[1] = CreateShader(LoadShader(fragFileName + ".frag"), GL_FRAGMENT_SHADER);
	}
	//Loops through every shader we have in our m_shaders variable
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		//Attaches the shader at index i to your program
		glAttachShader(m_program, m_shaders[i]);
	}

	//Finds the attribute named "position" and binds it to attribute 0
	glBindAttribLocation(m_program, 0, "position");
	//Finds the attribute named "texCoord" and binds it to attribute 1
	glBindAttribLocation(m_program, 1, "texCoord");
	//Finds the attribute named "normal" and binds it to attribute 2
	glBindAttribLocation(m_program, 2, "normal");

	//Links the shader program to our program
	glLinkProgram(m_program);
	
	//Now this can create encounter linker problems
	//so we want to check for linker errors
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	//Validates that the shader program successfully integrated with our program
	glValidateProgram(m_program);
	//Even though we've checked if our program linked correctly
	//Just because it linked correctly, doesn't mean that
	//Everything works in union.
	//SO we need to check for validation errors
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed: ");

	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "view");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");
}

//Deconstructs the shader object.
Shader::~Shader()
{
	//Loops through every shader
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		//Detaches and deletes the shader at index i fromt he program
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	//Deletes the program you created using the handle given when the program was created
	glDeleteProgram(m_program);
}

//Creates the shader
static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	//Creates the shader and sets the shader type
	GLuint shader = glCreateShader(shaderType);

	//If the shader is 0, it means that a valid shader hasn't been given
	if (shader == 0)
	{
		//Outputs that the shader creation has failed
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	//OpenGL is c based, meaning the c++ string we passed as a parameter
	//Can't be used. So we create a const char* (GLchar* in this case),
	//Because you can have more than one shader here, we make it size 1
	//Which is the same as just having one variable but it's now an array.
	//So we declare both the shader source strings and the source string lengths
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	//Here, using the .c_str() method, we store a c-string version
	//of our c++ string, text, in our source string variable at index 0.
	shaderSourceStrings[0] = text.c_str();	
	//Here we store the length of the c++ string, text, (will be the same as the c-string
	//version) at index 0.
	shaderSourceStringLengths[0] = (GLint)text.length();

	//Sends our source code to openGL and lets the GPU do its work.
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	//Compiles our shader into something usable in our program
	glCompileShader(shader);

	//During the compilation process there's a chance that this can fail, so we need to check
	//for these compiler errors
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");


	return shader;
}

//Simple I/O (with only the I part)
//Shaders are files with code in them.
//What this does is opens the file and grabs the contents for use in THIS program
std::string LoadShader(const std::string & fileName)
{
	//Creates an input file stream
	std::ifstream file;
	//Opens the shader file using the file stream
	file.open((fileName).c_str());

	//Holds the contents of the file
	std::string output;
	std::string line;

	//Checks whether the file is open
	if (file.is_open()) 
	{
		//While the file hasn't encountered any errors
		while (file.good())
		{
			//Grabs the line from the file
			getline(file, line);
			//Appends that line to the output variable and creates a new line.
			output.append(line + "\n");
		}
	}
	else 
	{
		//Returns an error if it was unable to open the file
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	//Returns the contents of the file (if the file was unable to be opened, this will return empty);
	return output;
}

//Checks the various shader errors you may run into
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	//Checks if the shader is already a program
	if (isProgram) 
	{
		//If the shader is already a program, it takes the program and checks the iv
		glGetProgramiv(shader, flag, &success);
	}
	else 
	{
		//If it's not, gets the shader file's iv error
		glGetShaderiv(shader, flag, &success);
	}

	//Checks if the iv returned successfully
	if (success == GL_FALSE)
	{
		//Checks if the shader is already a program
		if (isProgram)
		{
			//If the shader is already a program, it takes the program and checks the info log
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else 
		{
			//If it's not, gets the shader file's info log
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		//Outputs the error message with the info log on the error
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

//Set the GPU to a state that makes it use the vertex and fragment shaders defined here
void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::setVec3(const GLchar* name, const float & x, const float & y, const float & z)
{
	GLfloat vec[3] = { x, y, z };
	GLuint loc = glGetUniformLocation(m_program, name);
	glUniform3fv(loc, 1, vec);
}

void Shader::setFloat(const GLchar * name, const float & f)
{
	GLfloat fl = f;
	GLuint loc = glGetUniformLocation(m_program, name);
	glUniform1f(loc, f);
}

void Shader::setInt(const GLchar * name, const int & i)
{
	GLuint loc = glGetUniformLocation(m_program, name);
	glUniform1i(loc, i);
}

void Shader::update(const glm::mat4& _model, const Camera& _camera)
{
	//Using 4x4 matrices, you multiply the view projection by your transformation model in order to get the correct view.
	glm::mat4 model = _model;
	glm::mat4 view = _camera.getView();
	glm::mat4 projection = _camera.getProjection();

	//Updates the uniform 4x4 matrix you defined earlier.
	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &projection[0][0]);
}




