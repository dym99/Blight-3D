#ifndef __GBUFFER_H__
#define __GBUFFER_H__


#include "FrameBuffer.h"

class GBuffer : public FrameBuffer 
{
public:
	GBuffer(float _windowWidth, float _windowHeight);
	~GBuffer();

	void bindLighting();
	void unbindLighting();

	//Make sure to bind a shader before calling this
	void drawBuffers();

private:
	float windowWidth, windowHeight;
};

#endif // !__GBUFFER_H__