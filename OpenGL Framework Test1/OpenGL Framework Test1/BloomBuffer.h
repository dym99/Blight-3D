#ifndef __BLOOM_BUFFER_H__
#define __BLOOM_BUFFER_H__

#include "FrameBuffer.h"
#include "ShaderManager.h"

class BloomBuffer {
public:
	void init(float windowWidth, float windowHeight, float bloomDownscale);

	void drawTo();

	void drawBuffers();
	void drawBuffer(int index);

	void applyBloom(float bloomThreshold, int bloomPasses);
	void bindTexColor(int index, int textureUnit);
	void unbindTexColor(int index, int textureUnit);

private:
	void compositeBloom();
	void computeBlur(int bloomPasses);
	void bloomHighPass(float bloomThreshold);
	GLenum m_format = GL_R11F_G11F_B10F;
	GLenum m_filter = GL_NEAREST;
	GLenum m_wrap = GL_CLAMP_TO_EDGE;
	float bloomDownscale = 0;
	bool _isInit = false;
	float windowWidth, windowHeight = 0;
	FrameBuffer m_frameBuffers[4] = { FrameBuffer(1), FrameBuffer(1), FrameBuffer(1), FrameBuffer(1) };
};





#endif // !__BLOOM_BUFFER_H__