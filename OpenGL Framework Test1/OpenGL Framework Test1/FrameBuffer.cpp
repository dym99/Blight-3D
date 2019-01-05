#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int _NumColorAttachments)
{
	numColorAttachments = _NumColorAttachments;

	glGenFramebuffers(1, &FBO);

	colorAttachments = new GLuint[numColorAttachments];

	//Required parameter for gldrawbuffers()
	bufs = new GLenum[numColorAttachments];
	for (int i = 0; i < numColorAttachments; i++) {
		bufs[i] = GL_COLOR_ATTACHMENT0 + i;
	}
}

FrameBuffer::~FrameBuffer()
{
	Unload();
}

void FrameBuffer::InitDepthTexture(unsigned int width, unsigned int height)
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

void FrameBuffer::InitColorTexture(unsigned int index, unsigned int width, unsigned int height, 
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

bool FrameBuffer::CheckFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Unload();
		return false;
	}
	return true;
}

void FrameBuffer::Unload()
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

	numColorAttachments = 0;
}

void FrameBuffer::Clear()
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

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glDrawBuffers(numColorAttachments, bufs);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::bindTex(GLuint textureUnit, unsigned int colorIndex)
{
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glBindTexture(GL_TEXTURE_2D, GetColorHandle(colorIndex));
}

void FrameBuffer::bindTex(GLuint textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, GetDepthHandle());
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

GLuint FrameBuffer::getFBO() const
{
	return FBO;
}

GLuint FrameBuffer::GetDepthHandle() const
{
	return depthAttachment;
}

GLuint FrameBuffer::GetColorHandle(unsigned int index) const
{
	return colorAttachments[index];
}