#ifndef __IMODEL_H__
#define __IMODEL_H__

#include "Shader.h"
#include <string>
#include <map>
#include "Texture.h"
#include "BVH.h"
#include "MathFunc.h"


#pragma region enums

enum VBOType {
	VBO_POS,
	VBO_TEX,
	VBO_NORM,

	VBO_NORM_TANGENT,
	VBO_NORM_BITANGENT,

	VBO_GROUPS,
	VBO_WEIGHTS,

	NUM_VBO
};

enum TexTypes {
	TEX_ALBEDO,
	TEX_NORM,
	TEX_SPEC,
	TEX_EMM,

	NUM_TEX_TYPES
};

#pragma endregion

//Simple IMDL Loader
//
// Skipped Tangent/Bitangent stuff for now
//
class IModel
{
public:
	IModel();
	IModel(const IModel&);
	~IModel();

	void loadBindSkeleton(const std::string& fileName);
	void loadAnimations(const std::string& fileName);
	void loadFromFile(const std::string& _name, const std::string& _path="Resources/Objects/");
	void loadBindMatrices();
	void loadAnimMatrices(int index);
	void update(float dt);

	void sendBones();
	void calculateBindBones(int index);

	void draw(Shader *shader);

	//TODO: just assume textures are named albedo.png, normals.png, spec.png (etc.) unless specifed.
	//Right now, you have to specify.
	void setAlbedo(Texture* _tex);

private:
	//Vertex attributes
	GLuint m_VAO;
	GLuint m_VBO[NUM_VBO];

	//Textures applied to the model.
	//GLuint m_TEX[NUM_TEX_TYPES];

	Texture* m_albedo;

	const char* m_path;
	const char* m_name;

	unsigned int m_numVertices;

	std::vector<glm::mat4> m_bindBones;

	BVH m_bindSkeleton;
	std::vector<BVH*> m_animations;

	float m_percentNextFrame = 0.f;
	int m_currentFrame = 0;

	////Map of all previously loaded files,
	////in order to prevent loading the same model twice.
	//static std::map<const std::string&,IModel*> m_paths;
};

#endif