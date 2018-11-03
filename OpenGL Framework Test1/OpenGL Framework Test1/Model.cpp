#define _CRT_SECURE_NO_WARNINGS
#include "Model.h"
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>

#define CHAR_BUFFER_SIZE 128

Model::Model()
{
}

Model::Model(const Model& copy)
{
	for (int i = 0; i < copy.meshes.size(); i++) {
		this->meshes.push_back(copy.meshes[i]);
	}
	this->meshIndex = copy.meshIndex;

	for (int i = 0; i < copy.materials.size(); i++) {
		this->matNames.push_back(copy.matNames[i]);
		this->materials.push_back(copy.materials[i]);
	}
	this->matIndex = copy.matIndex;

	this->path = copy.path;
	this->name = copy.name;

	this->firstObj = copy.firstObj;
	this->hasUVs = copy.hasUVs;


}

Model::~Model()
{
	for (int i = 0; i < materials.size(); i++) {
		delete materials[i];
	}
}

bool Model::LoadFromFile(const std::string & _path, const std::string & _name)
{
	path = _path;
	name = _name;
	//Creates and opens a file stream at parameter "file"
	std::ifstream input;
	input.open(path + name + ".obj");

	if (!input) {
		std::cout << "File failed to open." << std::endl;
		return false;
	}

	char inputString[CHAR_BUFFER_SIZE];

	//
	while (!input.eof()) {
		input.getline(inputString, CHAR_BUFFER_SIZE);

		if (inputString[0] == '#') {
			//This line is a comment
			continue;
		}
		else if (std::strstr(inputString, "mtllib") != nullptr) {
			char buf[CHAR_BUFFER_SIZE];

			strncpy_s(buf, &inputString[7], CHAR_BUFFER_SIZE);

			std::string temp = buf;

			processMaterials(path + temp);
		}
		else if (inputString[0] == 's') {
			//This line is smooth shading
			continue;
		}
		else if (inputString[0] == 'o') {
			if (!firstObj) {
				firstObj = true;
			}
			else {
				meshes[meshIndex - 1]->ProcessMesh(vertexData, textureData, normalData, faceData);
			}
			//This line is a new object
			char buf[CHAR_BUFFER_SIZE];

			strncpy_s(buf, &inputString[2], CHAR_BUFFER_SIZE);

			std::string temp = buf;

			meshes.push_back(new Mesh(temp));
			meshIndex++;
		}
		else if (std::strstr(inputString, "usemtl") != nullptr) {
			//this is a usemtl line;
			char buf[CHAR_BUFFER_SIZE];

			strncpy_s(buf, &inputString[7], CHAR_BUFFER_SIZE);

			std::string temp = buf;
			
			for (int i = 0; i < matNames.size(); i++) {
				if (matNames[i] == temp) {
					meshes[meshIndex - 1]->material = *materials[i];
				}
			}
		}
		else if (inputString[0] == 's') {
			//this line is for smooth shading
			continue;
		}
		else if (inputString[0] == 'v') {
			if (inputString[1] == 'n') {
				//This line has normal data in it
				glm::vec3 temp;

				std::sscanf(inputString, "vn %f %f %f", &temp.x, &temp.y, &temp.z);
				normalData.push_back(temp);
			}
			else if (inputString[1] == 't') {
				//This line has texture data in it
				glm::vec2 temp;

				hasUVs = true;

				std::sscanf(inputString, "vt %f %f", &temp.x, &temp.y);
				textureData.push_back(temp);
			}
			else {
				//This line has vertex data in it
				glm::vec3 temp;

				std::sscanf(inputString, "v %f %f %f", &temp.x, &temp.y, &temp.z);
				vertexData.push_back(temp);
			}
		}
		else if (inputString[0] == 'f') {
			//This line has face data in it
			MeshFace temp;

			if (hasUVs) {
				std::sscanf(inputString, "f %u/%u/%u %u/%u/%u %u/%u/%u",
					&temp.vertices[0], &temp.textureUVs[0], &temp.normals[0],
					&temp.vertices[1], &temp.textureUVs[1], &temp.normals[1],
					&temp.vertices[2], &temp.textureUVs[2], &temp.normals[2]);
			}
			else {
				std::sscanf(inputString, "f %u//%u %u//%u %u//%u",
					&temp.vertices[0], &temp.normals[0],
					&temp.vertices[1], &temp.normals[1],
					&temp.vertices[2], &temp.normals[2]);
			}
			faceData.push_back(temp);
		}
	}

	meshes[meshIndex - 1]->ProcessMesh(vertexData, textureData, normalData, faceData);
	faceData.clear();

	//Closes the file stream
	input.close();

	vertexData.clear();
	textureData.clear();
	normalData.clear();
	faceData.clear();

	return true;
}

void Model::Draw(Shader * shader)
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->Draw(shader);
	}
}

bool Model::processMaterials(const std::string & file)
{
	std::ifstream input;

	input.open(file);

	if (!input) {
		std::cout << "Material file failed to open.\n";
		return false;
	}

	char inputString[CHAR_BUFFER_SIZE];

	while (!input.eof()) {
		input.getline(inputString, CHAR_BUFFER_SIZE);

		if (inputString[0] == '#') {
			//This line is a comment
			continue;
		}
		else if (std::strstr(inputString, "newmtl") != nullptr) {
			char buf[CHAR_BUFFER_SIZE];

			std::strncpy(buf, &inputString[7], CHAR_BUFFER_SIZE);

			std::string temp = buf;

			matNames.push_back(temp);
			materials.push_back(new Material(temp));
			matIndex++;
		}
		else if (std::strstr(inputString, "map_Kd") != nullptr) {
			//This line has a diffuse map
			char buf[CHAR_BUFFER_SIZE];

			std::strncpy(buf, &inputString[7], CHAR_BUFFER_SIZE);

			std::string temp = buf;

			materials[matIndex-1]->textures.push_back(new Texture("diffuseTex"));
			materials[matIndex-1]->texIndex++;
			materials[matIndex-1]->textures[materials[matIndex-1]->texIndex - 1]->Load(path + temp);
		}
		else if (std::strstr(inputString, "map_Bump") != nullptr) {
			//This line has a normal map
			char buf[CHAR_BUFFER_SIZE];

			std::strncpy(buf, &inputString[9], CHAR_BUFFER_SIZE);

			std::string temp = buf;

			materials[matIndex - 1]->textures.push_back(new Texture("normalTex"));
			materials[matIndex - 1]->texIndex++;
			materials[matIndex - 1]->textures[materials[matIndex - 1]->texIndex - 1]->Load(path + temp);
		}
		else if (std::strstr(inputString, "map_Ks") != nullptr) {
			//This line has specular map
			char buf[CHAR_BUFFER_SIZE];

			std::strncpy(buf, &inputString[7], CHAR_BUFFER_SIZE);

			std::string temp = buf;

			materials[matIndex-1]->textures.push_back(new Texture("specularTex"));
			materials[matIndex-1]->texIndex++;
			materials[matIndex-1]->textures[materials[matIndex-1]->texIndex - 1]->Load(path + temp);
		}
		else if (std::strstr(inputString, "illum") != nullptr) {
			//This line has illumination info on it
			unsigned int temp;

			std::sscanf(inputString, "illum %u", &temp);
		}
		else if (std::strstr(inputString, "Ns") != nullptr) {
			//This line has shininess info
			float temp;

			std::sscanf(inputString, "Ns %f", &temp);
		}
		else if (std::strstr(inputString, "Ka") != nullptr) {
			//This line has illumination info on it
			glm::vec3 temp;

			std::sscanf(inputString, "Ka %f %f %f", &temp.x, &temp.y, &temp.z);
		}
		else if (std::strstr(inputString, "Kd") != nullptr) {
			//This line has illumination info on it
			glm::vec3 temp;

			std::sscanf(inputString, "Kd %f %f %f", &temp.x, &temp.y, &temp.z);
		}
		else if (std::strstr(inputString, "Ks") != nullptr) {
			//This line has illumination info on it
			glm::vec3 temp;

			std::sscanf(inputString, "Ks %f %f %f", &temp.x, &temp.y, &temp.z);
		}
		else if (std::strstr(inputString, "Ni") != nullptr) {
			//This line has illumination info on it
			float temp;

			std::sscanf(inputString, "Ni %f", &temp);
		}
		else if (std::strstr(inputString, "d") != nullptr) {
			//This line has transparancy info on it
			float temp;

			std::sscanf(inputString, "d %f", &temp);
		}
	}
	input.close();
	return true;
}
