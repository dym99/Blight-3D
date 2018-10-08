#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>
#include "Texture.h"

class Material {
public:
	Material() = default;
	Material(std::string &_name);
	~Material();

	std::vector<Texture*> textures;

	std::string name;
	unsigned int texIndex = 0;
private:

};

#endif // !__MATERIAL_H__

