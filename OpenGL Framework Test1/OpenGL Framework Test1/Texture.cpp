#include "Texture.h"
#include <SOIL/SOIL.h>

#include <iostream>

Texture::Texture(const std::string &_type)
{
	type = _type;
}

Texture::~Texture()
{
	unload();
}

void Texture::createTexture(int w, int h, GLenum target, GLenum filtering, GLenum edgeBehaviour, GLenum internalFormat, GLenum textureFormat, GLenum dataType, void * newDataPtr)
{
	GLenum error = 0;

	// Not necessary to enable GL_TEXTURE_* in modern context.
	//	glEnable(m_pTarget);
	//	error = glGetError();

	unload();

	glGenTextures(1, &m_texture);
	glBindTexture(target, m_texture);
	error = glGetError();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, edgeBehaviour);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, edgeBehaviour);
	error = glGetError();

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, textureFormat, dataType, newDataPtr);
	error = glGetError();

	if (error != 0)
	{
		//SAT_DEBUG_LOG_ERROR("[Texture.cpp : createTexture] Error when creating texture. ");
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}


bool Texture::load(const std::string & file)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); 
	//Wraps with repeating texture on V axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	return true;
}

void Texture::unload()
{
	if (m_texture != 0) 
	{
		//Remove data from GPU
		glDeleteTextures(1, &m_texture);
		m_texture = 0;
	}
}

void Texture::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glActiveTexture(GL_TEXTURE0);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unbind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glActiveTexture(GL_TEXTURE0);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
