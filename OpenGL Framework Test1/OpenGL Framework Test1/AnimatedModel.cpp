//Tell Microsoft to shut up
#define _CRT_SECURE_NO_WARNINGS

#include "AnimatedModel.h"

#include <exception>

//IMDL Header macros
#define IMDL_HEADER 0x4c444d49U
#define V_1_0 0x0100

#define BUFFER_OFFSET(i) ((char *) 0 + (i))

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

#include "Utils.h"

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

AnimatedModel::AnimatedModel()
{
	m_cFrame = 0;
	m_lFrame = 0;
}

AnimatedModel::AnimatedModel(const AnimatedModel &_other)
{
	m_path = _other.m_path;
	m_name = _other.m_name;

	m_VAO = _other.m_VAO;
	for (unsigned int i = 0; i < NUM_VBO; ++i) {
		m_VBO[i] = _other.m_VBO[i];
	}
}

AnimatedModel::~AnimatedModel()
{
	m_framesPos.clear();
	m_framesNorm.clear();
	m_uvs.clear();
	return;
}

void AnimatedModel::loadFromFiles(int _frameCount, const std::string & _name, const std::string & _path)
{

	for (int i = 0; i < _frameCount; ++i) {
		std::string filename = _path + _name + std::to_string(i) + ".imdl";

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

				std::vector<glm::vec3> vertices;
				vertices.reserve(static_cast<size_t>(vertex_count));
				for (unsigned int j = 0; j < vertex_count; ++j) {
					//Read a vertex.
					glm::vec3 v;

					fread(&v.x, sizeof(float), 1, file);
					fread(&v.y, sizeof(float), 1, file);
					fread(&v.z, sizeof(float), 1, file);


					//If mesh is skinned...
					if (flags == 0x0001) {
						//Parse Weights
						unsigned int num_weights;
						fread(&num_weights, sizeof(unsigned int), 1, file);

						//Skip over weights if they exist...
						fseek(file, num_weights*(sizeof(int) + sizeof(float)), SEEK_CUR);
					}

					//Add vertex to vertices
					vertices.push_back(v);
				}

				//Read uv coordinates
				unsigned int uv_count;
				fread(&uv_count, sizeof(unsigned int), 1, file);

				std::vector<glm::vec2> uvs;

				//Only bother with getting one of the model's uvs
				if (i == 0) {
					uvs.reserve(static_cast<size_t>(uv_count));
					for (unsigned int j = 0; j < uv_count; ++j) {
						glm::vec2 uv;

						fread(&uv.x, sizeof(float), 1, file);
						fread(&uv.y, sizeof(float), 1, file);

						uvs.push_back(uv);
					}
				}
				else {
					fseek(file, sizeof(float) * 2 * uv_count, SEEK_CUR);
				}

				//Read normals
				unsigned int norm_count;
				fread(&norm_count, sizeof(unsigned int), 1, file);

				std::vector<glm::vec3> norms;
				norms.reserve(static_cast<size_t>(norm_count));
				for (unsigned int j = 0; j < norm_count; ++j) {
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
				for (unsigned int j = 0; j < indexPair_count; ++j) {
					IndexPair indexPair;

					fread(&indexPair.vert, sizeof(unsigned int), 1, file);

					//Ignoring uv on all but first frame
					if (i == 0)
						fread(&indexPair.uv, sizeof(unsigned int), 1, file);
					else
						fseek(file, sizeof(unsigned int), SEEK_CUR);

					fread(&indexPair.norm, sizeof(unsigned int), 1, file);

					indexPairs.push_back(indexPair);
				}
				std::cout << indexPairs.size() << std::endl;
				//Unpack data

				std::vector<float> unpackedPos;
				std::vector<float> unpackedUV;
				std::vector<float> unpackedNorm;

				//Loop through each face and add to lists of unpacked data.
				for (size_t j = 0; j < indexPairs.size(); ++j) {
					unpackedPos.push_back(vertices[indexPairs[j].vert].x);
					unpackedPos.push_back(vertices[indexPairs[j].vert].y);
					unpackedPos.push_back(vertices[indexPairs[j].vert].z);
					
					//Ignoring uv on all but first frame
					if (i == 0) {
						unpackedUV.push_back(uvs[indexPairs[j].uv].x);
						unpackedUV.push_back(uvs[indexPairs[j].uv].y);
					}

					unpackedNorm.push_back(norms[indexPairs[j].norm].x);
					unpackedNorm.push_back(norms[indexPairs[j].norm].y);
					unpackedNorm.push_back(norms[indexPairs[j].norm].z);
				}

				if (i == 0) {
					m_numVertices = unpackedPos.size();
				}
				else if (unpackedPos.size() != m_numVertices) {
					//Frames have incorrect vert count!
					std::cout << "inconsistent vert count with file '" << filename << "'" << std::endl;
					m_framesPos.clear();
					m_framesNorm.clear();
					m_uvs.clear();
					return;
				}
				std::cout << "'" << filename << "' " << unpackedPos.size() << " " << unpackedNorm.size() << std::endl;

				m_framesPos.push_back(unpackedPos);
				m_framesNorm.push_back(unpackedNorm);

				if (i == 0) {
					m_uvs = unpackedUV;	//Use the first frame's uv coords
				}
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

		if (m_framesPos.size() <= 0) {
			//BAD!
			return;
		}
		if (m_framesNorm.size() <= 0) {
			//BAD!
			return;
		}

		if (m_framesPos.size() != m_framesNorm.size()) {
			//Incorrectly loading frames
			m_framesPos.clear();
			m_framesNorm.clear();
			m_uvs.clear();
			return;
		}

		//If all is good, load data to OpenGL
		glGenVertexArrays(1, &m_VAO);
		for (unsigned int i = 0; i < NUM_VBO; ++i) {
			glGenBuffers(1, &m_VBO[i]);
		}

		glBindVertexArray(m_VAO);
		glEnableVertexAttribArray(VBO_POS);
		glEnableVertexAttribArray(VBO_TEX);
		glEnableVertexAttribArray(VBO_NORM);
		glEnableVertexAttribArray(VBO_LASTPOS);
		glEnableVertexAttribArray(VBO_LASTNORM);

		//Send the Vertex data to OpenGL
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_POS]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_framesPos[0].size(), &m_framesPos[0][0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)VBO_POS, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_NORM]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_framesNorm[0].size(), &m_framesNorm[0][0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)VBO_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_LASTPOS]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_framesPos[0].size(), &m_framesPos[0][0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)VBO_LASTPOS, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_LASTNORM]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_framesNorm[0].size(), &m_framesNorm[0][0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)VBO_LASTNORM, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_TEX]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_uvs.size(), &m_uvs[0], GL_STATIC_DRAW); //Texture UVs not changing
		glVertexAttribPointer((GLuint)VBO_TEX, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));
		
		//Cleanup after the buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	m_frameCount = m_framesPos.size();
	for (size_t i = 0; i < m_frameCount; ++i) m_frameTimes.push_back(0.2f); //Set default frame times to 0.2 seconds per frame (5fps).
}

void AnimatedModel::draw(Shader * shader)
{
	shader->sendUniform("uT", m_t);
	//Draw the mesh
	m_albedo->bind(0);			//Albedo
	m_albedo->bind(1);
	m_emissive->bind(2);		//Emissives
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices * 3);
	glBindVertexArray(0);
	Texture::unbind(2);
	Texture::unbind(1);
	Texture::unbind(0);
}

void AnimatedModel::setAlbedo(Texture * _tex)
{
	m_albedo = _tex;
}

void AnimatedModel::setEmissive(Texture * _tex)
{
	m_emissive = _tex;
}

void AnimatedModel::update()
{
	//Update T-value
	m_t += m_animSpeed * Time::deltaTime/m_frameTimes[m_cFrame];

	if (m_t >= 1.0f) {
		//Properly set current frame indices.
		while (m_t >= 1.0f) {
			m_lFrame = m_cFrame;
			++m_cFrame;
			if (m_cFrame >= m_frameCount)
				m_cFrame = 0;
			m_t -= 1.0f;
		}

		updateFrames();
	}
}

void AnimatedModel::setFrameTime(size_t _frame, float _time)
{
	if (_frame < m_frameTimes.size())
		m_frameTimes[_frame] = _time;
}

void AnimatedModel::reset()
{
	m_cFrame = 0;
	m_lFrame = 0;

	m_t = 0.f;
}

void AnimatedModel::setAnimSpeed(float _speed)
{
	m_animSpeed = _speed;
}

void AnimatedModel::updateFrames()
{
	glBindVertexArray(m_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_POS]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_numVertices, &m_framesPos[m_cFrame][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_NORM]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_numVertices, &m_framesNorm[m_cFrame][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_LASTPOS]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_numVertices, &m_framesPos[m_lFrame][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_LASTNORM]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_numVertices, &m_framesNorm[m_lFrame][0]);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
