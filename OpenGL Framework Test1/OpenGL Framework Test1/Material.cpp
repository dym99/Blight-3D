#include "Material.h"

Material::Material(std::string & _name)
{
	name = _name;
}

Material::~Material()
{
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i] != nullptr)
			delete textures[i];

		textures[i] = nullptr;
	}
}
