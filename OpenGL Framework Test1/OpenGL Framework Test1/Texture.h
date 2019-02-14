#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <string>

class Texture {
public:
	Texture() = default;
	Texture(const std::string &_type);
	~Texture();

	bool load(const std::string &file);
	void unload();
	// Description:
	// Creates the texture, allocates memory and uploads data to GPU
	// If you do not want to upload data to the GPU pass in a nullptr for the dataPtr.
	// For a description on filtering and edgeBehaviour see https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	// For a description on internalFormat, textureFormat and dataType see https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml
	void createTexture(int w, int h, GLenum target, GLenum filtering, GLenum edgeBehaviour, GLenum internalFormat, GLenum textureFormat, GLenum dataType, void* newDataPtr);

	void bind(int unit);
	void bind();
	static void unbind(int unit);
	static void unbind();
		
	//Helper functions
	inline GLuint getID() { return m_texture; }
	inline std::string getType() { return type; }

private:
	//Handle to the texture;
	GLuint m_texture = 0;
	std::string type;

};

#endif // !__TEXTURE_H__

