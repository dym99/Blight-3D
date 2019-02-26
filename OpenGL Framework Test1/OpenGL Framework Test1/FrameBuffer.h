#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

#include <GL/glew.h>
#include <vector>

class FrameBuffer {
public:
	FrameBuffer() = delete;
	FrameBuffer(unsigned int _NumColorAttachments);
	~FrameBuffer();

	static void initFSQ();
	static void drawFSQ();

	//Call everythin
	void init(unsigned int _NumColorAttachments);

	//Init the different textures
	void initDepthTexture(unsigned int width, unsigned int height);
	void initColorTexture(unsigned int index, unsigned int width, unsigned int height,
							GLint internalFormat, GLint filter, GLint wrap);

	//Checks to make sure that everything is loaded in correctly
	bool checkFBO();

	//Clears OpenGL memory
	void unload();

	//Clears all attached textures
	void clear();

	//Binds and unbinds the FBO
	void bind();
	void unbind();

	//Resize the frame buffer
	void resize(int windowWidth, int windowHeight);

	void renderToFSQ();

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

	virtual void drawBuffers();

	//Getters
	GLuint getFBO() const;
	GLuint getDepthHandle() const;
	GLuint getColorHandle(unsigned int index) const;

private:
	static GLuint fullScreenQuadVBO;
	static GLuint fullScreenQuadVAO;

	GLuint FBO = GL_NONE;
	GLuint depthAttachment = GL_NONE;
	GLuint *colorAttachments = nullptr;
	GLenum *bufs = nullptr;

	std::vector<GLint> formats;
	std::vector<GLint> filters;
	std::vector<GLint> wraps;

	unsigned int numColorAttachments = 0;
};

#endif // !__FRAME_BUFFER_H__
