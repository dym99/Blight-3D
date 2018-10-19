#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__
#include <GL/glew.h>

class FrameBuffer {
public:
	FrameBuffer() = delete;
	FrameBuffer(unsigned int _NumColorAttachments);
	~FrameBuffer();

	//Init the different textures
	void InitDepthTexture(unsigned int width, unsigned int height);
	void InitColorTexture(unsigned int index, unsigned int width, unsigned int height,
							GLint internalFormat, GLint filter, GLint wrap);

	//Checks to make sure that everything is loaded in correctly
	bool CheckFBO();

	//Clears OpenGL memory
	void Unload();

	//Clears all attached textures
	void Clear();

	//Binds and unbinds the FBO
	void Bind();
	void Unbind();

	//Move to buffer
	void MoveToBackBuffer(int windowWidth, int windowHeight);
				
	//Getters
	GLuint GetDepthHandle() const;
	GLuint GetColorHandle(unsigned int index) const;

private:
	GLuint FBO = GL_NONE;
	GLuint depthAttachment = GL_NONE;
	GLuint *colorAttachment = nullptr;
	GLenum *bufs = nullptr;

	unsigned int numColorAttachment = 0;
};

#endif // !__FRAME_BUFFER_H__
