
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
	std::vector<float> unPackedVertexData;
	std::vector<float> unPackedTextureData;
	std::vector<float> unPackedNormalData;
	std::vector<float> unPackedTangentData;
	std::vector<float> unPackedBitangentData;
	
	tangentData.resize(vertexData.size());
	bitangentData.resize(vertexData.size());

	//Calculate tangent and bitangent data here
	//V IMPORTANT PLS AND THANK FOR TANGENT SPACE NORMALS
	for (unsigned i = 0; i < faceData.size(); i++) {
		std::vector<glm::vec3> tempPos;
		std::vector<glm::vec2> tempUV;

		for (unsigned j = 0; j < 3; j++) {
			glm::vec3 tempP;
			glm::vec2 tempU;

			tempP.x = vertexData[faceData[i].vertices[j] - 1].x;
			tempP.y = vertexData[faceData[i].vertices[j] - 1].y;
			tempP.z = vertexData[faceData[i].vertices[j] - 1].z;
			tempPos.push_back(tempP);

			tempU.x = textureData[faceData[i].textureUVs[j] - 1].x;
			tempU.y = textureData[faceData[i].textureUVs[j] - 1].y;
			tempUV.push_back(tempU);
		}

		//Tangent and bitangent calculation here
		glm::vec3 deltaPos1 = tempPos[1] - tempPos[0];
		glm::vec3 deltaPos2 = tempPos[2] - tempPos[0];

		glm::vec2 deltaUV1 = tempUV[1] - tempUV[0];
		glm::vec2 deltaUV2 = tempUV[2] - tempUV[0];

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		//Puts the current tangent and bitangent data into the correct slot in the tangentData and
		//bitangent data vectors
		for (unsigned j = 0; j < 3; j++) {
			tangentData[faceData[i].vertices[j] - 1].x = tangent.x;
			tangentData[faceData[i].vertices[j] - 1].y = tangent.y;
			tangentData[faceData[i].vertices[j] - 1].z = tangent.z;

			bitangentData[faceData[i].vertices[j] - 1].x = bitangent.x;
			bitangentData[faceData[i].vertices[j] - 1].y = bitangent.y;
			bitangentData[faceData[i].vertices[j] - 1].z = bitangent.z;
		}
		
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

			unPackedTangentData.push_back(tangentData[faceData[i].vertices[j] - 1].x);
			unPackedTangentData.push_back(tangentData[faceData[i].vertices[j] - 1].y);
			unPackedTangentData.push_back(tangentData[faceData[i].vertices[j] - 1].z);

			unPackedBitangentData.push_back(bitangentData[faceData[i].vertices[j] - 1].x);
			unPackedBitangentData.push_back(bitangentData[faceData[i].vertices[j] - 1].y);
			unPackedBitangentData.push_back(bitangentData[faceData[i].vertices[j] - 1].z);
		}
		

	}

	m_NumFaces = (int)faceData.size();
	m_NumVertices = m_NumFaces * 3;
	
	//Send the data to OpenGL
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Vertices);
	glGenBuffers(1, &VBO_UVs);
	glGenBuffers(1, &VBO_Normals);
	glGenBuffers(1, &VBO_Tangents);
	glGenBuffers(1, &VBO_Bitangents);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);	//Vertexes
	glEnableVertexAttribArray(1);	//UVs
	glEnableVertexAttribArray(2);	//Normals
	glEnableVertexAttribArray(3);	//Tangents
	glEnableVertexAttribArray(4);	//Bitangents
	
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

	//Send the tangent data to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Tangents);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedTangentData.size(), &unPackedTangentData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//Send the bitangent data to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Bitangents);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unPackedBitangentData.size(), &unPackedBitangentData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	//Cleanup after the buffers you bound
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	faceData.clear();

	return true;
}

bool Mesh::ProcessMesh(std::vector<float>& unPackedVertexData, std::vector<float>& unPackedTextureData, std::vector<float>& unPackedNormalData)
{
	return false;
}

void Mesh::Draw(Shader * shader)
{
	unsigned int diffuseNr = 0;
	unsigned int normalNr = 0;
	unsigned int specularNr = 0;
	for (unsigned int i = 0; i < material.textures.size(); i++) {
		//Sets the correct texture unit to active
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = material.textures[i]->GetType();
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
			shader->sendUniform("hasNormMap", 0);
		}
		else {
			shader->sendUniform("hasNormMap", 1);
		}

		shader->sendUniform(("material." + name).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, material.textures[i]->GetTextureHandle());
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