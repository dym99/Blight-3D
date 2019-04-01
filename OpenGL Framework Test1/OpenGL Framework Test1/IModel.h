#ifndef __IMODEL_H__
#define __IMODEL_H__

#include "Shader.h"
#include <string>
#include <map>
#include "Texture.h"


#pragma region enums

enum VBOType {
	VBO_POS,
	VBO_TEX,
	VBO_NORM,

	VBO_NORM_TANGENT,
	VBO_NORM_BITANGENT,

	VBO_GROUPS,
	VBO_WEIGHTS,

	VBO_LASTPOS,
	VBO_LASTNORM,

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

class Weight {
public:
	Weight() {
		m_group = 0;
		m_weight = 0.f;
	}
	unsigned int m_group;
	float m_weight;
};

class Vertex {
public:
	Vertex() {
		m_pos = glm::vec3();
		m_weights = std::vector<Weight>();
	}
	Vertex(const glm::vec3& _pos, const std::vector<Weight>& _weights) {
		m_pos = _pos;
		m_weights = _weights;
	}

	glm::vec3 m_pos;
	std::vector<Weight> m_weights;
};

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


	///<summary>
	///Load *.imdl file directly into VRAM.
	///</summary>
	///<param name='_name'>Name of file (including extension)</param>
	///<param name='_path'>Parent directory of the file.</param>
	void loadFromFile(const std::string& _name, const std::string& _path = "Resources/Objects/");
	
	
	void draw(Shader *shader);

	//TODO: just assume textures are named albedo.png, normals.png, spec.png (etc.) unless specifed.
	//Right now, you have to specify.
	void setAlbedo(Texture* _tex);

	//Specify Emissive texture
	void setEmissive(Texture* _tex);
	void setHeight(Texture* _tex);
	void setNormal(Texture* _tex);
	void setDirection(Texture* _tex);
	void setMetal(Texture* _tex);
	void setRough(Texture* _tex);

private:
	std::vector<glm::vec4> dataTangent;
	std::vector<glm::vec4> dataBitangent;

	void calculateTangents(std::vector<Vertex>* dataVertex, std::vector<glm::vec2>* dataTexture);
	//Vertex attributes
	GLuint m_VAO;
	GLuint m_VBO[NUM_VBO];

	//Textures applied to the model.
	//GLuint m_TEX[NUM_TEX_TYPES];

	Texture* m_albedo;
	Texture* m_emissive;
	Texture* m_height;
	Texture* m_normal;
	Texture* m_direction;
	Texture* m_metalness;
	Texture* m_roughness;

	const char* m_path;
	const char* m_name;

	unsigned int m_numVertices;

	////Map of all previously loaded files,
	////in order to prevent loading the same model twice.
	//static std::map<const std::string&,IModel*> m_paths;
};

#endif