#include "PostBuffer.h"

void PostBuffer::init(unsigned width, unsigned height)
{
	if (!_IsInit)
	{
		for (int i = 0; i < 2; ++i)
		{
			m_frameBuffers[i].init(1);
			m_frameBuffers[i].initColorTexture(0, width, height, m_format, m_filter, m_wrap);
		}
		m_readBuffer = &m_frameBuffers[0];
		m_writeBuffer = &m_frameBuffers[1];
		_IsInit = true;
	}
}

void PostBuffer::setFormat(GLenum format)
{
	m_format = format;
}

void PostBuffer::setWrap(GLenum wrap)
{
	m_wrap = wrap;
}

void PostBuffer::setFilter(GLenum filter)
{
	m_filter = filter;
}

void PostBuffer::clear()
{
	for (int i = 0; i < 2; ++i)
	{
		m_frameBuffers[i].clear();
	}
}

void PostBuffer::reshape(unsigned width, unsigned height)
{
	for (int i = 0; i < 2; ++i)
	{
		m_frameBuffers[i].resize(width, height);
	}
}

void PostBuffer::bindColorTex(unsigned textureUnit)
{
	m_readBuffer->bindTex(textureUnit, 0);
}

void PostBuffer::unbindColorTex(unsigned textureUnit)
{
	m_readBuffer->unbindTex(textureUnit);
}

void PostBuffer::drawTo()
{
	m_writeBuffer->renderToFSQ();
	swap();
}

void PostBuffer::draw()
{
	m_readBuffer->bindTex(0, 0);
	m_writeBuffer->renderToFSQ();
	m_readBuffer->unbindTex(0);

	swap();
}

void PostBuffer::drawToScreen()
{
	m_writeBuffer->unbind();
	m_readBuffer->bindTex(0, 0);
	FrameBuffer::drawFSQ();
	m_readBuffer->unbindTex(0);
}

void PostBuffer::swap()
{
	std::swap(m_readBuffer, m_writeBuffer);
}
