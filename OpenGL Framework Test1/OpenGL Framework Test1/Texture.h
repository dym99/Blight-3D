#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <string>

class Texture {
public:
	Texture() = default;
	Texture(const std::string &_type);
	~Texture();

	bool Load(const std::string &file);
	void Unload();

	void Bind();
	void Unbind();
		
	//Helper functions
	inline GLuint GetTextureHandle() { return m_texture; }
	inline std::string GetType() { return type; }

private:
	//Handle to the texture;
	GLuint m_texture = 0;
	std::string type;

};

#endif // !__TEXTURE_H__

