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

	void bind();
	void Unbind();
		
	//Helper functions
	inline GLuint getTextureHandle() { return m_texture; }
	inline std::string getType() { return type; }

private:
	//Handle to the texture;
	GLuint m_texture = 0;
	std::string type;

};

#endif // !__TEXTURE_H__

