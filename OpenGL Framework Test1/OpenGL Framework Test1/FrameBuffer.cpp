#include "FrameBuffer.h"
#include <iostream>

GLuint FrameBuffer::fullScreenQuadVBO = GL_NONE;
GLuint FrameBuffer::fullScreenQuadVAO = GL_NONE;

FrameBuffer::FrameBuffer(unsigned int _NumColorAttachments)
{
	init(_NumColorAttachments);
}

FrameBuffer::~FrameBuffer()
{
	unload();
}

void FrameBuffer::initFSQ()
{
	float VBO_DATA[]{
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		-1.f, 1.f, 0.f,

		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f,
		1.f, -1.f, 0.f,

		0.f, 0.f,
		1.f, 0.f,
		0.f, 1.f,

		1.f, 1.f,
		0.f, 1.f,
		1.f, 0.f,
	};

	int vertexSize = 6 * 3 * sizeof(float);
	int texCoordSize = 6 * 2 * sizeof(float);

	glGenVertexArrays(1, &fullScreenQuadVAO);
	glBindVertexArray(fullScreenQuadVAO);

	glEnableVertexAttribArray(0); //vertices
	glEnableVertexAttribArray(1); //UV coordinates

	glGenBuffers(1, &fullScreenQuadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, fullScreenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize + texCoordSize, VBO_DATA, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));			//send vertex attributes
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(vertexSize)); //send uv attributes

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void FrameBuffer::drawFSQ()
{
	glBindVertexArray(fullScreenQuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(GL_NONE);
}

void FrameBuffer::init(unsigned int _NumColorAttachments)
{
	numColorAttachments = _NumColorAttachments;

	glGenFramebuffers(1, &FBO);

	colorAttachments = new GLuint[numColorAttachments];

	//Required parameter for gldrawbuffers()
	bufs = new GLenum[numColorAttachments];
	for (unsigned int i = 0; i < numColorAttachments; i++) {
		bufs[i] = GL_COLOR_ATTACHMENT0 + i;
	}
	formats.resize(numColorAttachments);
	filters.resize(numColorAttachments);
	wraps.resize(numColorAttachments);
}

void FrameBuffer::initDepthTexture(unsigned int width, unsigned int height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	//Create depth texture
	glGenTextures(1, &depthAttachment);
	glBindTexture(GL_TEXTURE_2D, depthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//bind it
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::initColorTexture(unsigned int index, unsigned int width, unsigned int height, 
									GLint internalFormat, GLint filter, GLint wrap)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	//Create depth texture
	glGenTextures(1, &colorAttachments[index]);
	glBindTexture(GL_TEXTURE_2D, colorAttachments[index]);
	glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	//bind it
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, colorAttachments[index], 0);
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

bool FrameBuffer::checkFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		unload();
		return false;
	}
	return true;
}

void FrameBuffer::unload()
{
	if (bufs != nullptr) {
		delete[] bufs;
		bufs = nullptr;
	}
	if (colorAttachments != nullptr) {
		for (int i = 0; i < numColorAttachments; i++) {
			glDeleteTextures(1, &colorAttachments[i]);
		}

		delete[] colorAttachments;
		colorAttachments = nullptr;
	}

	if (depthAttachment != GL_NONE) {
		glDeleteTextures(1, &depthAttachment);
		depthAttachment = GL_NONE;
	}
}

void FrameBuffer::clear()
{
	GLbitfield temp = 0x0;

	if (depthAttachment != GL_NONE) {
		temp = temp | GL_DEPTH_BUFFER_BIT;
	}
	if (colorAttachments != nullptr) {
		temp = temp | GL_COLOR_BUFFER_BIT;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClear(temp);
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glDrawBuffers(numColorAttachments, bufs);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::resize(int windowWidth, int windowHeight)
{
	unload();
	init(numColorAttachments);
	for (unsigned int i = 0; i < numColorAttachments; i++)
	{
		initColorTexture(i, windowWidth, windowHeight, formats[i], filters[i], wraps[i]);
	}
	initDepthTexture(windowWidth, windowHeight);
}

void FrameBuffer::renderToFSQ()
{
	bind();
	FrameBuffer::drawFSQ();
	unbind();
}

void FrameBuffer::bindTex(GLuint textureUnit, unsigned int colorIndex)
{
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glBindTexture(GL_TEXTURE_2D, getColorHandle(colorIndex));
}

void FrameBuffer::bindTex(GLuint textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, getDepthHandle());
}

void FrameBuffer::unbindTex(GLuint textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void FrameBuffer::copyTo(GLuint FBODraw, GLbitfield mask, int windowWidth, int windowHeight)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBODraw);

	glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth,
						windowHeight, mask, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::copyFrom(GLuint FBORead, GLbitfield mask, int windowWidth, int windowHeight)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FBORead);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);

	glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth,
						windowHeight, mask, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::drawBuffers()
{
	std::cout << "Non-Implemented Function called in FrameBuffer" << std::endl;
}

GLuint FrameBuffer::getFBO() const
{
	return FBO;
}

GLuint FrameBuffer::getDepthHandle() const
{
	return depthAttachment;
}

GLuint FrameBuffer::getColorHandle(unsigned int index) const
{
	return colorAttachments[index];
}