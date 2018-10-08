
#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>


#define CHAR_BUFFER_SIZE 128
#define BUFFER_OFFSET(i) ((char *) 0 + (i))

Mesh::Mesh(const std::string &_oName)
{
	oName = _oName;
}

Mesh::~Mesh()
{
}

bool Mesh::ProcessMesh(std::vector<glm::vec3> &vertexData, std::vector<glm::vec2> &textureData, std::vector<glm::vec3> &normalData, std::vector<MeshFace> &faceData)
{
	//Data ready for OpenGL
	std::vector<float> unPackedVertexData;
	std::vector<float> unPackedTextureData;
	std::vector<float> unPackedNormalData;
	{
		//
		//while (!input.eof()) {
		//	input.getline(inputString, CHAR_BUFFER_SIZE);

		//	if (inputString[0] == '#') {
		//		//This line is a comment
		//		continue;
		//	}
		//	else if (inputString[0] == 'o') {
		//		//This line is an object
		//		char buf[CHAR_BUFFER_SIZE];

		//		std::strncpy(buf, &inputString[2], CHAR_BUFFER_SIZE);

		//		std::string temp = buf;
		//	}
		//	if (loadingData) {
		//		if (std::strstr(inputString, "usemtl") != nullptr) {
		//			char buf[CHAR_BUFFER_SIZE];

		//			std::strncpy(buf, &inputString[7], CHAR_BUFFER_SIZE);

		//			std::string temp = buf;

		//			LoadMaterial(temp);
		//		}
		//		else if (inputString[0] == 's') {
		//			//this line is for smooth shading
		//			continue;
		//		}
		//		else if (inputString[0] == 'v') {
		//			if (inputString[1] == 'n') {
		//				//This line has normal data in it
		//				glm::vec3 temp;

		//				std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
		//				normalData.push_back(temp);
		//			}
		//			else if (inputString[1] == 't') {
		//				//This line has texture data in it
		//				glm::vec2 temp;

		//				hasUVs ? true : hasUVs = true;

		//				std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
		//				textureData.push_back(temp);
		//			}
		//			else {
		//				//This line has vertex data in it
		//				glm::vec3 temp;

		//				std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
		//				vertexData.push_back(temp);
		//			}
		//		}
		//		else if (inputString[0] == 'f') {
		//			//This line has face data in it
		//			MeshFace temp;

		//			if (hasUVs) {
		//				std::sscanf(inputString, "f %u/%u/%u %u/%u/%u %u/%u/%u",
		//					&temp.vertices[0], &temp.textureUVs[0], &temp.normals[0],
		//					&temp.vertices[1], &temp.textureUVs[1], &temp.normals[1],
		//					&temp.vertices[2], &temp.textureUVs[2], &temp.normals[2]);
		//			}
		//			else {
		//				std::sscanf(inputString, "f %u//%u %u//%u %u//%u",
		//					&temp.vertices[0], &temp.normals[0],
		//					&temp.vertices[1], &temp.normals[1],
		//					&temp.vertices[2], &temp.normals[2]);
		//			}
		//			faceData.push_back(temp);
		//		}
		//	}
		//}

		////Closes the file stream
		//input.close();
	}

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

	faceData.clear();
	unPackedVertexData.clear();
	unPackedTextureData.clear();
	unPackedNormalData.clear();

	return true;
}

void Mesh::Draw(Shader * shader)
{
	unsigned int diffuseNr = 0;
	unsigned int normalNr = 0;
	unsigned int specularNr = 0;
	for (unsigned int i = 0; i < material.textures.size(); i++) {
		//Sets the correct texture unit to active
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = material.textures[i]->getType();
		if (name == "diffuseTex") {
			diffuseNr++;
		}
		else if (name == "specularTex") {
			specularNr++;
		}
		else if (name == "normalTex") {
			normalNr++;
		}

		if (normalNr == 0) {
			shader->setInt("hasNormMap", 0);
		}
		else {
			shader->setInt("hasNormMap", 1);
		}

		shader->setInt(("material." + name).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, material.textures[i]->getTextureHandle());
	}
	glActiveTexture(GL_TEXTURE0);

	//draws mesh
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