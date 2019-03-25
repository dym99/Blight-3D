#ifndef __GBUFFER_H__
#define __GBUFFER_H__


#include "FrameBuffer.h"

enum BufferType {
	ALBEDO,
	NORMAL,
	FRAGPOSITION,
	EMISSIVES,
	METALNESS,
	ROUGHNESS,

	NUM_BUFFERS
};

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

	void drawBuffers(BufferType topLeft, BufferType topRight, BufferType bottomLeft);

private:
	float windowWidth, windowHeight;
};

#endif // !__GBUFFER_H__