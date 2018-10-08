#include "Texture.h"
#include <SOIL/SOIL.h>

#include <iostream>

Texture::Texture(const std::string &_type)
{
	type = _type;
}

Texture::~Texture()
{
	Unload();
}

bool Texture::Load(const std::string & file)
{
	m_texture = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);

	if (m_texture == 0) {
		std::cout << "Texture failed to load.\n" << file << '\n' << SOIL_last_result() << '\n';
		return false;
	}

	//modify the texture;
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Wraps with repeating texture on U axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	//Wraps with repeating texture on V axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}

void Texture::Unload()
{
	if (m_texture != 0) 
	{
		//Remove data from GPU
		glDeleteTextures(1, &m_texture);
		m_texture = 0;
	}
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
