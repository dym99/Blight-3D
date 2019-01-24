#ifndef __IMODEL_H__
#define __IMODEL_H__

#include "Shader.h"
#include <string>
#include <map>
#include "Texture.h"

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

class IModel
{
public:
	IModel();
	IModel(const IModel&);
	~IModel();

	void loadFromFile(const std::string& _name, const std::string& _path="Resources/Objects/");
	void draw(Shader *shader);

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

	//Map of all previously loaded files,
	//in order to prevent loading the same model twice.
	//static std::map<const std::string&,IModel*> m_paths;
};

#endif