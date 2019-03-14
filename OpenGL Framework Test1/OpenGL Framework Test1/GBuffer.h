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

	void bindEdge();
	void unbindEdge();

	void reshape(unsigned windowWidth, unsigned windowHeight);

	virtual void drawBuffers() override;

private:
	float windowWidth, windowHeight;
};

#endif // !__GBUFFER_H__