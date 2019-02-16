#ifndef __COMBINATION_BUFFER_H__
#define __COMBINATION_BUFFER_H__


#include "FrameBuffer.h"

class CombinationBuffer : public FrameBuffer
{
public:
	CombinationBuffer(float _windowWidth, float _windowHeight);
	~CombinationBuffer();
};

#endif // !__COMBINATION_BUFFER_H__