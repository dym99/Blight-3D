#ifndef __MESH_H__
#define __MESH_H__

#define BUFFER_OFFSET(i) ((char *) 0 + (i))
#include <string>
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include <vector>
#include <GL/glew.h>

struct MeshFace {
public:
	MeshFace() {
		for (int i = 0; i < 3; i++) {
			vertices[i] = 0;
			textureUVs[i] = 0;
			normals[i] = 0;
			targets[i] = 0;
		}
	}

	MeshFace(unsigned v1, unsigned v2, unsigned v3,
		unsigned t1, unsigned t2, unsigned t3,
		unsigned n1, unsigned n2, unsigned n3) {
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;

		targets[0] = v1;
		targets[1] = v2;
		targets[2] = v3;

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
	unsigned targets[3];
};

class Mesh {
public:
	Mesh(const std::string &_oName);
	~Mesh();

	//Load mesh and send to OpenGL
	//Returns true if file loaded correctly
	bool ProcessMesh(std::vector<glm::vec3> &vertexData,
		std::vector<glm::vec2> &textureData,
		std::vector<glm::vec3> &normalData,
		std::vector<MeshFace> &faceData, bool isMorphTarget = false);
	bool ProcessMesh(std::vector<float> &unPackedVertexData,
		std::vector<float> &unPackedTextureData,
		std::vector<float> &unPackedNormalData);
	void Draw(Shader* shader);

	void update(float dt) {
		uInterp += dt;
			while (uInterp > 1.f) {
				uInterp -= 1.f;

				if (targets.size() >= 4) {
					std::vector<float> newFirst = targets[3];

					targets[3] = targets[2];
					targets[2] = targets[1];
					targets[1] = targets[0];
					targets[0] = newFirst;


					//Send the Target data to OpenGL
					glBindBuffer(GL_ARRAY_BUFFER, VBO_HandlesA);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * targets[0].size(), &targets[0][0], GL_DYNAMIC_DRAW);
					glVertexAttribPointer((GLuint)6, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
					//Send the Target data to OpenGL
					glBindBuffer(GL_ARRAY_BUFFER, VBO_Vertices);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * targets[1].size(), &targets[1][0], GL_DYNAMIC_DRAW);
					glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
					//Send the Target data to OpenGL
					glBindBuffer(GL_ARRAY_BUFFER, VBO_Targets);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * targets[2].size(), &targets[2][0], GL_DYNAMIC_DRAW);
					glVertexAttribPointer((GLuint)5, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
					//Send the Target data to OpenGL
					glBindBuffer(GL_ARRAY_BUFFER, VBO_HandlesB);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * targets[3].size(), &targets[3][0], GL_DYNAMIC_DRAW);
					glVertexAttribPointer((GLuint)7, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));
				}
				else {
					if (oName != "Plane")
						std::cout << "CG Dance Failed! Object: " << oName << std::endl;
				}

			}
	}

	//Releases all data from openGL (clear allocations)
	void Unload();

	//Texturing stuffs
	Material material;

	//Helper functions
	unsigned int GetNumFaces() const;
	unsigned int GetNumVertices() const;

	std::string oName;

	//OpenGL specific stuffs
	GLuint VBO_Vertices = 0;
	GLuint VBO_Targets = 0;
	GLuint VBO_HandlesA = 0;
	GLuint VBO_HandlesB = 0;
	GLuint VBO_UVs = 0;
	GLuint VBO_Normals = 0;
	GLuint VBO_Tangents = 0;
	GLuint VBO_Bitangents = 0;
	GLuint VAO = 0;

	//Tangent space Normal mapping
	std::vector<glm::vec3> tangentData;
	std::vector<glm::vec3> bitangentData;

	std::vector<float> verticesForTarget;
	std::vector<std::vector<float>> targets;

private:
	unsigned int m_NumFaces;
	unsigned int m_NumVertices;

	float uInterp;
};





#endif
