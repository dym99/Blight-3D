#include "BloomBuffer.h"

void BloomBuffer::init(float windowWidth, float windowHeight, float bloomDownscale)
{
	if (!_isInit)
	{
		m_frameBuffers[0].initColorTexture(0, windowWidth, windowHeight, GL_RGBA8, m_filter, m_wrap);
		m_frameBuffers[1].initColorTexture(0, windowWidth/bloomDownscale, windowHeight/bloomDownscale, GL_RGB8, m_filter, m_wrap);
		m_frameBuffers[2].initColorTexture(0, windowWidth/bloomDownscale, windowHeight/bloomDownscale, GL_RGB8, m_filter, m_wrap);
		m_frameBuffers[3].initColorTexture(0, windowWidth, windowHeight, GL_RGBA8, m_filter, m_wrap);

		_isInit = true;
		this->windowWidth = windowWidth;
		this->windowHeight = windowHeight;
		this->bloomDownscale = bloomDownscale;
	}
}

void BloomBuffer::drawTo()
{
	m_frameBuffers[0].renderToFSQ();
}

void BloomBuffer::drawBuffers()
{
	glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);					///Top Left
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	m_frameBuffers[0].bindTex(0, 0);															//Orignal Color
	FrameBuffer::drawFSQ();
	m_frameBuffers[0].unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	glViewport(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);	///Top Right
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	m_frameBuffers[2].bindTex(0, 0);															//Blurred
	FrameBuffer::drawFSQ();
	m_frameBuffers[2].unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	glViewport(0, 0, windowWidth / 2, windowHeight / 2);									///Bottom Left
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	m_frameBuffers[3].bindTex(0, 0);															//Combined
	FrameBuffer::drawFSQ();
	m_frameBuffers[3].unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();
}

void BloomBuffer::drawBuffer(int index)
{
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	m_frameBuffers[index].bindTex(0, 0);															//Combined
	FrameBuffer::drawFSQ();
	m_frameBuffers[index].unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();
}

void BloomBuffer::applyBloom(float bloomThreshold, int bloomPasses)
{
	bloomHighPass(bloomThreshold);
	computeBlur(bloomPasses);
	compositeBloom();
}

void BloomBuffer::bindTexColor(int index, int textureUnit)
{
	m_frameBuffers[index].bindTex(textureUnit, 0);
}

void BloomBuffer::unbindTexColor(int index, int textureUnit)
{
	m_frameBuffers[index].unbindTex(textureUnit);
}

void BloomBuffer::compositeBloom()
{
	glViewport(0, 0, windowWidth, windowHeight);

	ShaderManager::getBloom(COMPOSITE_PASS)->bind();
	
	m_frameBuffers[3].bind();
	
	m_frameBuffers[0].bindTex(0, 0);
	m_frameBuffers[1].bindTex(1, 0);
	FrameBuffer::drawFSQ();
	m_frameBuffers[1].unbindTex(1);
	m_frameBuffers[0].unbindTex(0);

	m_frameBuffers[3].unbind();
	
	ShaderManager::getBloom(COMPOSITE_PASS)->unbind();
}

void BloomBuffer::computeBlur(int bloomPasses)
{
	/// Compute Blur ///
	for (int i = 0; i < bloomPasses; ++i)
	{
		//Horizontal Blurring
		ShaderManager::getBloom(HORIZONTAL_PASS)->bind();
		ShaderManager::getBloom(HORIZONTAL_PASS)->sendUniform("uPixelSize", 1.0f / windowWidth);
		
		m_frameBuffers[2].bind();

		m_frameBuffers[1].bindTex(0, 0);
		FrameBuffer::drawFSQ();
		m_frameBuffers[1].unbindTex(0);

		m_frameBuffers[2].unbind();
		ShaderManager::getBloom(HORIZONTAL_PASS)->unbind();

		//Vertical Blurring
		ShaderManager::getBloom(VERTICAL_PASS)->bind();
		ShaderManager::getBloom(VERTICAL_PASS)->sendUniform("uPixelSize", 1.0f / windowHeight);
		m_frameBuffers[1].bind();

		m_frameBuffers[2].bindTex(0, 0);
		FrameBuffer::drawFSQ();
		m_frameBuffers[2].unbindTex(0);

		m_frameBuffers[1].unbind();
		ShaderManager::getBloom(VERTICAL_PASS)->bind();
	}
}

void BloomBuffer::bloomHighPass(float bloomThreshold)
{
	glViewport(0, 0, windowWidth / bloomDownscale, windowHeight / bloomDownscale);

	ShaderManager::getBloom(HIGH_PASS)->bind();
	ShaderManager::getBloom(HIGH_PASS)->sendUniform("uThreshold", bloomThreshold);;

	m_frameBuffers[1].bind();

	m_frameBuffers[0].bindTex(0, 0);
	FrameBuffer::drawFSQ();
	m_frameBuffers[0].unbindTex(0);

	m_frameBuffers[1].unbind();
	ShaderManager::getBloom(HIGH_PASS)->unbind();
}
