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

	////Map of all previously loaded files,
	////in order to prevent loading the same model twice.
	//static std::map<const std::string&,IModel*> m_paths;
};

#endif