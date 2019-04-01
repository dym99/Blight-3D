//Tell microsoft to shut up
#define _CRT_SECURE_NO_WARNINGS

#include "IModel.h"

//IMDL Header macros
#define IMDL_HEADER 0x4c444d49U
#define V_1_0 0x0100

#define BUFFER_OFFSET(i) ((char *) 0 + (i))

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

class IndexPair {
public:
	IndexPair() {
		vert = 0;
		uv = 0;
		norm = 0;
	}
	unsigned int vert;
	unsigned int uv;
	unsigned int norm;
};

//std::map<const std::string&, IModel*> IModel::m_paths = std::map<const std::string&, IModel*>();

IModel::IModel() {

}

IModel::IModel(const IModel& _other) {
	m_path = _other.m_path;
	m_name = _other.m_name;

	m_VAO = _other.m_VAO;
	for (unsigned int i = 0; i < NUM_VBO; ++i) {
		m_VBO[i] = _other.m_VBO[i];
	}
}

IModel::~IModel() {

}

void IModel::loadFromFile(const std::string& _name, const std::string& _path) {
	std::string filename = _path + _name;

	//Check if the file is already loaded and use existing models.
	//std::map<const std::string&, IModel*>::iterator it;
	//it = IModel::m_paths.find(filename);
	//if (it != IModel::m_paths.end()) {
	//	//Model already exists, so copy it.
	//	//IModel(*IModel::m_paths.at(filename));
	//	return;
	//}

	//Otherwise, load in the file.
	FILE *file;
	file = fopen(filename.c_str(), "rb");
	if (file == NULL) {
		//File failed to open.
		std::cout << "Failed to open file '" << filename << "'" << std::endl;
		return;
	}

	//Read header
	unsigned int header;

	fread(&header, sizeof(unsigned int), 1, file);

	//Check if the file is an IMDL file.
	if (header == IMDL_HEADER) {

		//Read version numbers.
		//char ver_maj;
		//fread(&ver_maj, sizeof(char), 1, file);
		//char ver_min;
		//fread(&ver_min, sizeof(char), 1, file);
		unsigned short version;
		fread(&version, sizeof(unsigned short), 1, file);

		//Check Versions
		if (version == 1) {
			//Read version 1.0

			////Flags
			//
			// Version 1.0 only supports one flag,
			// so either 0x0000 for unskinned, or 0x0001 for skinned
			//
			////
			unsigned short flags;
			fread(&flags, sizeof(unsigned short), 1, file);

			//Read vertices
			unsigned int vertex_count;
			fread(&vertex_count, sizeof(unsigned int), 1, file);

			std::vector<Vertex> vertices;
			vertices.reserve(static_cast<size_t>(vertex_count));
			for (unsigned int i = 0; i < vertex_count; ++i) {
				//Read a vertex.
				Vertex v;

				fread(&v.m_pos.x, sizeof(float), 1, file);
				fread(&v.m_pos.y, sizeof(float), 1, file);
				fread(&v.m_pos.z, sizeof(float), 1, file);


				//If mesh is skinned...
				if (flags == 0x0001) {
					//Parse Weights
					unsigned int num_weights;
					fread(&num_weights, sizeof(unsigned int), 1, file);


					for (unsigned int w = 0; w < num_weights; ++w) {
						Weight weight;
						fread(&weight.m_group, sizeof(unsigned int), 1, file);
						fread(&weight.m_weight, sizeof(float), 1, file);

						v.m_weights.push_back(weight);
					}
				}
				else {
					//No weights
				}

				//Add vertex to vertices
				vertices.push_back(v);
			}

			//Read uv coordinates
			unsigned int uv_count;
			fread(&uv_count, sizeof(unsigned int), 1, file);

			std::vector<glm::vec2> uvs;
			uvs.reserve(static_cast<size_t>(uv_count));
			for (unsigned int i = 0; i < uv_count; ++i) {
				glm::vec2 uv;

				fread(&uv.x, sizeof(float), 1, file);
				fread(&uv.y, sizeof(float), 1, file);

				uvs.push_back(uv);
			}

			//Read normals
			unsigned int norm_count;
			fread(&norm_count, sizeof(unsigned int), 1, file);

			std::vector<glm::vec3> norms;
			norms.reserve(static_cast<size_t>(norm_count));
			for (unsigned int i = 0; i < norm_count; ++i) {
				glm::vec3 norm;

				fread(&norm.x, sizeof(float), 1, file);
				fread(&norm.y, sizeof(float), 1, file);
				fread(&norm.z, sizeof(float), 1, file);

				norms.push_back(norm);
			}

			//Read face indices

			unsigned int indexPair_count;
			fread(&indexPair_count, sizeof(float), 1, file);

			std::vector<IndexPair> indexPairs;
			indexPairs.reserve(static_cast<unsigned int>(indexPair_count));
			for (unsigned int i = 0; i < indexPair_count; ++i) {
				IndexPair indexPair;

				fread(&indexPair.vert, sizeof(unsigned int), 1, file);
				fread(&indexPair.uv, sizeof(unsigned int), 1, file);
				fread(&indexPair.norm, sizeof(unsigned int), 1, file);

				indexPairs.push_back(indexPair);
			}
			std::cout << indexPairs.size() << std::endl;
			//Unpack data

			//calculateTangents(&vertices, &uvs);

			std::vector<float> unpackedPos;
			std::vector<float> unpackedUV;
			std::vector<float> unpackedNorm;
			std::vector<float> unpackedTangent;
			std::vector<float> unpackedBitangent;
			std::vector<int> unpackedGroups;
			std::vector<float> unpackedWeights;

			//Loop through each face and add to lists of unpacked data.
			for (size_t i = 0; i < indexPairs.size(); ++i) {
				unpackedPos.push_back(vertices[indexPairs[i].vert].m_pos.x);
				unpackedPos.push_back(vertices[indexPairs[i].vert].m_pos.y);
				unpackedPos.push_back(vertices[indexPairs[i].vert].m_pos.z);
				unpackedUV.push_back(uvs[indexPairs[i].uv].x);
				unpackedUV.push_back(uvs[indexPairs[i].uv].y);
				unpackedNorm.push_back(norms[indexPairs[i].norm].x);
				unpackedNorm.push_back(norms[indexPairs[i].norm].y);
				unpackedNorm.push_back(norms[indexPairs[i].norm].z);
				//unpackedTangent.push_back(dataTangent[indexPairs[i].vert].x);
				//unpackedTangent.push_back(dataTangent[indexPairs[i].vert].y);
				//unpackedTangent.push_back(dataTangent[indexPairs[i].vert].z);
				//unpackedBitangent.push_back(dataBitangent[indexPairs[i].vert].x);
				//unpackedBitangent.push_back(dataBitangent[indexPairs[i].vert].y);
				//unpackedBitangent.push_back(dataBitangent[indexPairs[i].vert].z);

				if (vertices[indexPairs[i].vert].m_weights.size() > 4) {
					//Too many groups for the engine (for now)
					//To pick the four most influential, sort by most weight to least weight.
					std::sort(vertices[indexPairs[i].vert].m_weights.begin(), vertices[indexPairs[i].vert].m_weights.end(), [](Weight a, Weight b) {return a.m_weight > b.m_weight; });
				}

				glm::ivec4 groups;
				glm::vec4 weights;
				//Now grab up to the first four weights and put them in the unpacked groups/weights
				for (size_t w = 0; w < vertices[indexPairs[i].vert].m_weights.size() && w < 4; ++w) {
					groups[w] = vertices[indexPairs[i].vert].m_weights[w].m_group;
					weights[w] = vertices[indexPairs[i].vert].m_weights[w].m_weight;
				}
				unpackedGroups.push_back(groups.x);
				unpackedGroups.push_back(groups.y);
				unpackedGroups.push_back(groups.z);
				unpackedGroups.push_back(groups.w);
				unpackedWeights.push_back(weights.x);
				unpackedWeights.push_back(weights.y);
				unpackedWeights.push_back(weights.z);
				unpackedWeights.push_back(weights.w);
			}

			//TODO: TANGENT/BITANGENT



			//Get unpacked vertex count
			m_numVertices = static_cast<unsigned int>(unpackedPos.size());



			//Push data to VRAM
			glGenVertexArrays(1, &m_VAO);
			for (unsigned int i = 0; i < NUM_VBO; ++i) {
				glGenBuffers(1, &m_VBO[i]);
			}

			glBindVertexArray(m_VAO);

			glEnableVertexAttribArray(VBO_POS);	//Vertices
			glEnableVertexAttribArray(VBO_TEX);	//UVs
			glEnableVertexAttribArray(VBO_NORM);	//Normals
			//glEnableVertexAttribArray(VBO_NORM_TANGENT);	//Tangents
			//glEnableVertexAttribArray(VBO_NORM_BITANGENT);	//Bitangents
			glEnableVertexAttribArray(VBO_GROUPS);	//Groups
			glEnableVertexAttribArray(VBO_WEIGHTS);	//Weights

			//Send the Vertex data to OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_POS]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedPos.size(), &unpackedPos[0], GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)VBO_POS, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

			//Send the texture data to OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_TEX]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedUV.size(), &unpackedUV[0], GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)VBO_TEX, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

			//Send the normal data to OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_NORM]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedNorm.size(), &unpackedNorm[0], GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)VBO_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

			////Send the tangent data to OpenGL
			//glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_NORM_TANGENT]);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTangent.size(), &unpackedTangent[0], GL_STATIC_DRAW);
			//glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
			//
			////Send the bitangent data to OpenGL
			//glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_NORM_BITANGENT]);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedBitangent.size(), &unpackedBitangent[0], GL_STATIC_DRAW);
			//glVertexAttribPointer((GLuint)4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

			//Send the group data to OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_GROUPS]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(int) * unpackedGroups.size(), &unpackedGroups[0], GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)VBO_GROUPS, 4, GL_INT, GL_FALSE, sizeof(int) * 4, BUFFER_OFFSET(0));

			//Send the weight data to OpenGL
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_WEIGHTS]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedWeights.size(), &unpackedWeights[0], GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)VBO_WEIGHTS, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, BUFFER_OFFSET(0));

			//Cleanup after the buffers
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		else {
			//Version not supported.
			std::cout << "IMDL version not supported: '" << version << "'" << std::endl;
		}
	}
	else {
		//Not an IMDL file
		std::cout << "IMDL incorrect format" << std::endl;
	}

	//Close the file when done.
	fclose(file);
}


void IModel::draw(Shader * shader) {

	//Draw the mesh
	m_albedo->bind(0);			//Albedo
	if (m_normal != nullptr)
	{
		shader->sendUniform("noNormMap", 0);
		m_normal->bind(1);		//Normal
	}
	else
	{
		shader->sendUniform("noNormMap", 1);
	}
	m_emissive->bind(2);		//Emissive
	if (m_metalness != nullptr)
	{
		m_metalness->bind(3);	//Metalness
	}
	if (m_roughness != nullptr)
	{
		m_roughness->bind(4);	//Roughness
	}
	if (m_height != nullptr)
	{
		m_height->bind(5);		//Height
	}
	if (m_direction != nullptr)
	{
		m_direction->bind(6);	//Direction map
	}

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices * 3);
	glBindVertexArray(0);
	Texture::unbind(0);
	Texture::unbind(1);
	Texture::unbind(2);
	Texture::unbind(3);
	Texture::unbind(4);
	Texture::unbind(5);
	Texture::unbind(6);
}

void IModel::setAlbedo(Texture * _tex)
{
	m_albedo = _tex;
}

void IModel::setEmissive(Texture * _tex)
{
	m_emissive = _tex;
}

void IModel::setHeight(Texture * _tex)
{
	m_height = _tex;
}

void IModel::setNormal(Texture * _tex)
{
	m_normal = _tex;
}

void IModel::setDirection(Texture * _tex)
{
	m_direction = _tex;
}

void IModel::setMetal(Texture * _tex)
{
	m_metalness = _tex;
}

void IModel::setRough(Texture * _tex)
{
	m_roughness = _tex;
}

void IModel::calculateTangents(std::vector<Vertex>* dataVertex, std::vector<glm::vec2>* dataTexture)
{
	dataTangent.resize(dataVertex->size());
	dataBitangent.resize(dataVertex->size());

	for (size_t i = 0; i < dataVertex->size(); i += 3)
	{
		glm::vec3 vertex0 = dataVertex->at(i + 0).m_pos;
		glm::vec3 vertex1 = dataVertex->at(i + 1).m_pos;
		glm::vec3 vertex2 = dataVertex->at(i + 2).m_pos;

		glm::vec2 uv0 = dataTexture->at(i + 0);
		glm::vec2 uv1 = dataTexture->at(i + 1);
		glm::vec2 uv2 = dataTexture->at(i + 2);

		glm::vec3 deltaPos1 = vertex1 - vertex0;
		glm::vec3 deltaPos2 = vertex2 - vertex0;

		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*f;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*f;

		for (int tangentLoop = 0; tangentLoop < 3; ++tangentLoop)
		{
			dataTangent[i + tangentLoop] = glm::vec4(tangent, 1.0f);
			dataBitangent[i + tangentLoop] = glm::vec4(bitangent, 1.0f);
		}
	}
}


