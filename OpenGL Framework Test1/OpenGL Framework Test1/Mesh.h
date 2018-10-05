#ifndef __MESH_H__
#define __MESH_H__

#include <string>
#include "Transform.h"
#include "Shader.h"
#include <vector>
#include <GL/glew.h>

class Mesh {
public:
	Mesh();
	~Mesh();

	//Load mesh and send to OpenGL
	//Returns true if file loaded correctly
	bool LoadFromFile(const std::string &file);
	void Draw(Shader* shader);

	//Releases all data from openGL (clear allocations)
	void Unload();

	//Helper functions
	unsigned int GetNumFaces() const;
	unsigned int GetNumVertices() const;
	inline Transform* GetTransform() { return &transform; }

	//OpenGL specific stuffs
	GLuint VBO_Vertices = 0;
	GLuint VBO_UVs = 0;
	GLuint VBO_Normals = 0;
	GLuint VAO = 0;

private:
	bool hasUVs = false;
	unsigned int m_NumFaces;
	unsigned int m_NumVertices;
	Transform transform;
};

#endif
