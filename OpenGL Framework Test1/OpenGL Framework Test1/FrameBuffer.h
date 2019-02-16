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

	/*
	//Sends the color texture to openGL
	*- This is the texture unit you're binding to
	*- This is the color buffer index, be careful not to go out of bounds
	*/
	void bindTex(GLuint textureUnit, unsigned int colorIndex);
	
	/*
	//Sends the depth texture to openGL
	*- This is the texture unit you're binding to
	*/
	void bindTex(GLuint textureUnit);

	/*
	//quick unbind for the texture
	*/
	void unbindTex(GLuint textureUnit);

	/*
	//Copies a buffer to another FBO
	*- This is the buffer you're copying to, set to GL_NONE to copy from back buffer
	*- This is the buffer mask you're copying (GL_DEPTH_BUFFER_BIT or GL_COLOR_BUFFER_BIT)
	*- This is the width of the window
	*- This is the height of the window
	*- This is the bottom left corner x of where you're copying
	*- This is the bottom left corner y of where you're copying
	*/
	void copyTo(GLuint FBODraw, GLbitfield mask, int windowWidth, int windowHeight);
			
	/*
	//Copies a buffer from another FBO
	*- This is the buffer you're copying from, set to GL_NONE to copy from back buffer
	*- This is the buffer mask you're copying (GL_DEPTH_BUFFER_BIT or GL_COLOR_BUFFER_BIT)
	*- This is the width of the window
	*- This is the height of the window
	*- This is the bottom left corner x of where you're copying
	*- This is the bottom left corner y of where you're copying
	*/
	void copyFrom(GLuint FBORead, GLbitfield mask, int windowWidth, int windowHeight);

	//Getters
	GLuint getFBO() const;
	GLuint GetDepthHandle() const;
	GLuint GetColorHandle(unsigned int index) const;

private:
	GLuint FBO = GL_NONE;
	GLuint depthAttachment = GL_NONE;
	GLuint *colorAttachments = nullptr;
	GLenum *bufs = nullptr;

	unsigned int numColorAttachments = 0;
};

#endif // !__FRAME_BUFFER_H__
