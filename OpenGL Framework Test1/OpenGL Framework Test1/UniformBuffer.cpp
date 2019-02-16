#include "UniformBuffer.h"

UniformBuffer::UniformBuffer()
{

}

UniformBuffer::UniformBuffer(unsigned int bytes)
{
	allocateMemory(bytes);
}

UniformBuffer::~UniformBuffer()
{
	unload();
}

void UniformBuffer::unload()
{
	if (_Handle)
	{
		glDeleteBuffers(1, &_Handle);
	}
}

bool UniformBuffer::isInit()
{
	return _IsInit;
}

void UniformBuffer::allocateMemory(unsigned int bytes)
{
	if (_Handle)
	{
		unload();
	}
	glGenBuffers(1, &_Handle);
	_IsInit = true;
	bind();
	// This allocates 'n' bytes on the GPU, after which, data can now be sent to the Buffer
	glBufferData(GL_UNIFORM_BUFFER, bytes, GL_NONE, GL_DYNAMIC_DRAW);
	unbind();
}

void UniformBuffer::sendMatrix(const glm::mat4 &matrix, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::mat4), &matrix);
	unbind();
}

void UniformBuffer::sendVector(const glm::vec3 &vector, const int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), &vector);
	unbind();
}

void UniformBuffer::sendVector(const glm::vec4 &vector, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec4), &vector);
	unbind();
}

void UniformBuffer::sendFloat(float scalar, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &scalar);
	unbind();
}

void UniformBuffer::sendInt(int number, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(int), &number);
	unbind();
}

void UniformBuffer::sendUInt(unsigned int number, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(unsigned int), &number);
	unbind();
}

void UniformBuffer::sendBool(bool boolean, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(bool), &boolean);
	unbind();
}

void UniformBuffer::sendData(void * data, int size, int offset) const
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	unbind();
}

void UniformBuffer::bind(GLuint slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, _Handle);
	_BindLocation = slot;
}

void UniformBuffer::bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, _Handle);
}

void UniformBuffer::unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, GL_NONE);
}
