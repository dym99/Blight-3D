#ifndef __MODEL_H__
#define __MODEL_H__
#include "Mesh.h"

#define _CRT_SECURE_NO_WARNINGS

#define BUFFER_OFFSET(i) ((char *) 0 + (i))
#define CHAR_BUFFER_SIZE 128

class Model {
public:
	Model();

	Model(const Model& copy);

	~Model();
	
	bool LoadFromFile(const std::string &_path, const std::string &_name);
	bool LoadFromFile(const std::string &_path, const std::string& _name, unsigned int _numFiles);
	void Draw(Shader* shader, bool morph = false);

	//Meshes
	std::vector<Mesh*> meshes;
	unsigned int meshIndex = 0;

	//Materials
	std::vector<Material*> materials;
	std::vector<std::string> matNames;
	unsigned int matIndex = 0;

	//helper functions
	inline Transform* GetTransform() { return &transform; }

	//File stuffs
	std::string path;
	std::string name;

	//unique data
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec2> textureData;
	std::vector<glm::vec3> normalData;
	std::vector<MeshFace> faceData;
	
	bool firstObj = false;
	bool hasUVs = false;

private:
	bool ProcessMaterials(const std::string &file);
	Transform transform;
};


#endif // !__MODEL_H__
