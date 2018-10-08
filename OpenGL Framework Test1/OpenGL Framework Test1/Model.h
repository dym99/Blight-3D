#ifndef __MODEL_H__
#define __MODEL_H__
#include "Mesh.h"

class Model {
public:
	Model();
	~Model();
	
	bool LoadFromFile(const std::string &_path, const std::string &_name);
	void Draw(Shader* shader);

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
	bool processMaterials(const std::string &file);
	Transform transform;
};

#endif // !__MODEL_H__
