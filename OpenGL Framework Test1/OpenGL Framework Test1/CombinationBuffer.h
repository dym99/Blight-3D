#ifndef __COMBINATION_BUFFER_H__
#define __COMBINATION_BUFFER_H__


#include "FrameBuffer.h"
#include "ShaderManager.h"

//Exists but for some reason nothing is drawing to the buffers created within this class

class CombinationBuffer : public FrameBuffer
{
public:
	CombinationBuffer(float _windowWidth, float _windowHeight);
	~CombinationBuffer();

	void combineColorBuffers(FrameBuffer* buffer1, FrameBuffer* buffer2, ShaderTypes type, int shaderIndex);

	virtual void drawBuffers() override;
};

#endif // !__COMBINATION_BUFFER_H__