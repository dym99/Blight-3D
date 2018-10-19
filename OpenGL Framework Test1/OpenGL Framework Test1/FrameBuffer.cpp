#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int _NumColorAttachments)
{
	numColorAttachment = _NumColorAttachments;
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::InitDepthTexture(unsigned int width, unsigned int height)
{
}

void FrameBuffer::InitColorTexture(unsigned int index, unsigned int width, unsigned int height, 
									GLint internalFormat, GLint filter, GLint wrap)
{
}

bool FrameBuffer::CheckFBO()
{
	return false;
}

void FrameBuffer::Unload()
{
}

void FrameBuffer::Clear()
{
}

void FrameBuffer::Bind()
{
}

void FrameBuffer::Unbind()
{
}

void FrameBuffer::MoveToBackBuffer(int windowWidth, int windowHeight)
{
}

GLuint FrameBuffer::GetDepthHandle() const
{
	return depthAttachment;
}

GLuint FrameBuffer::GetColorHandle(unsigned int index) const
{
	return GLuint();
}
