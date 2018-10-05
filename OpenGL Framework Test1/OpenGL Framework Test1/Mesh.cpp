#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>


#define CHAR_BUFFER_SIZE 128
#define BUFFER_OFFSET(i) ((char *) 0 + (i))


struct MeshFace {
public:
	MeshFace() {
		for (int i = 0; i < 3; i++) {
			vertices[i] = 0;
			textureUVs[i] = 0;
			normals[i] = 0;
		}
	}
	
	MeshFace(unsigned v1, unsigned v2, unsigned v3,
		unsigned t1, unsigned t2, unsigned t3,
		unsigned n1, unsigned n2, unsigned n3) {
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;

		textureUVs[0] = t1;
		textureUVs[1] = t2;
		textureUVs[2] = t3;

		normals[0] = n1;
		normals[1] = n2;
		normals[2] = n3;
	}

	unsigned vertices[3];
	unsigned textureUVs[3];
	unsigned normals[3];
};


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::LoadFromFile(const std::string & file)
{
	//Creates and opens a file stream at parameter "file"
	std::ifstream input;
	input.open(file);

	if (!input) {
		std::cout << "File failed to open." << std::endl;
		return false;
	}

	char inputString[CHAR_BUFFER_SIZE];

	//Vectors to hold various data we need
	//Unique data
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> textureData;
	std::vector<glm::vec3> normalData;
	
	//Face data
	std::vector<MeshFace> faceData;

	//Data ready for OpenGL
	std::vector<float> unPackedVertexData;
	std::vector<float> unPackedTextureData;
	std::vector<float> unPackedNormalData;

	//
	while (!input.eof()) {
		input.getline(inputString, CHAR_BUFFER_SIZE);

		if (std::strstr(inputString, "#") != nullptr) {
			//This line is a comment
			continue;
		}
		if (std::strstr(inputString, "mtllib") != nullptr) {
			//This line is a mtl
			continue;
		}
		if (std::strstr(inputString, "s") != nullptr) {
			//this line is useless
			continue;
		}
		else if (std::strstr(inputString, "vn") != nullptr) {
			//This line has normal data in it
			glm::vec3 temp;

			std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
			normalData.push_back(temp);
		}
		else if (std::strstr(inputString, "vt") != nullptr) {
			//This line has texture data in it
			glm::vec2 temp;

			std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
			textureData.push_back(temp);
		}
		else if (std::strstr(inputString, "v") != nullptr) {
			//This line has vertex data in it
			glm::vec3 temp;
			
			std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
			vertexData.push_back(temp);
		}
		else if (std::strstr(inputString, "f") != nullptr) {
			//This line has face data in it
			MeshFace temp;

			std::sscanf(inputString, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&temp.vertices[0], &temp.textureUVs[0], &temp.normals[0],
				&temp.vertices[1], &temp.textureUVs[1], &temp.normals[1],
				&temp.vertices[2], &temp.textureUVs[2], &temp.normals[2]);
			faceData.push_back(temp);
		}
	}

	//Closes the file stream
	input.close();

	//Unpack the data
	//Face data important here
	for (unsigned i = 0; i < faceData.size(); i++) {
		for (unsigned j = 0; j < 3; j++) {
			unPackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].x);
			unPackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].y);
			unPackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].z);

			unPackedTextureData.push_back(textureData[faceData[i].textureUVs[j] - 1].x);
			unPackedTextureData.push_back(textureData[faceData[i].textureUVs[j] - 1].y);

			unPackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].x);
			unPackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].y);
			unPackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].z);
		}
	}

	m_NumFaces = faceData.size();
	m_NumVertices = m_NumFaces * 3;
	
	//Send the data to OpenGL
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Vertices);
	glGenBuffers(1, &VBO_UVs);
	glGenBuffers(1, &VBO_Normals);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);	//Vertexes
	glEnableVertexAttribArray(1);	//UVs
	glEnableVertexAttribArray(2);	//Normals
	
	//Send the Vertex data to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedVertexData.size(), &unPackedVertexData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//Send the texture data to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO_UVs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedTextureData.size(), &unPackedTextureData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	//Send the texture data to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedNormalData.size(), &unPackedNormalData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//Cleanup after the buffers you bound
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	vertexData.clear();
	textureData.clear();
	normalData.clear();
	faceData.clear();
	unPackedVertexData.clear();
	unPackedTextureData.clear();
	unPackedNormalData.clear();

	return true;
}

void Mesh::Draw(Shader * shader)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);
	glBindVertexArray(0);
}

void Mesh::Unload()
{
	glDeleteBuffers(1, &VBO_Normals);
	glDeleteBuffers(1, &VBO_UVs);
	glDeleteBuffers(1, &VBO_Vertices);
	glDeleteVertexArrays(1, &VAO);

	VBO_Normals = 0;
	VBO_UVs = 0;
	VBO_Vertices = 0;

	m_NumFaces = 0;
	m_NumVertices = 0;
}

unsigned int Mesh::GetNumFaces() const
{
	return m_NumFaces;
}

unsigned int Mesh::GetNumVertices() const
{
	return m_NumVertices;
}
