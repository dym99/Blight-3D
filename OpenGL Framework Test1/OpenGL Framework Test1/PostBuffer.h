#ifndef __POSTBUFFER_H__
#define __POSTBUFFER_H__

#include "FrameBuffer.h"


class PostBuffer 
{
public:
	void init(unsigned width, unsigned height);
	void setFormat(GLenum format);
	void setWrap(GLenum wrap);
	void setFilter(GLenum filter);
	void clear();
	void reshape(unsigned width, unsigned height);

	void drawTo();

	void draw();

	void drawToScreen();

protected:
	void swap();
	bool _IsInit = false;
	GLenum m_format = GL_R11F_G11F_B10F;
	GLenum m_filter = GL_NEAREST;
	GLenum m_wrap = GL_CLAMP_TO_EDGE;
	FrameBuffer* m_readBuffer = nullptr;
	FrameBuffer* m_writeBuffer = nullptr;
	FrameBuffer m_frameBuffers[2] = { FrameBuffer(1), FrameBuffer(1) };

};






#endif // !__POSTBUFFER_H__

