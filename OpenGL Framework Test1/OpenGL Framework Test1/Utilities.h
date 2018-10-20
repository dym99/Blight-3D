#ifndef __UTILITIES_H__
#define __UTILITES_H__

#include "Shader.h"
#include "FrameBuffer.h"
#include <vector>

#define WINDOW_HEIGHT			600
#define WINDOW_WIDTH			800
#define BLOOM_THRESHOLD         0.15f
#define BLOOM_DOWNSCALE			4.0f
#define BLOOM_BLUR_PASSES		4

void InitFullScreenQuad();

void DrawFullScreenQuad();

//Runs the high pass for the bloom effect
void BloomHighPass(Shader& BloomHighPass, FrameBuffer& _main, FrameBuffer& _work1);

//Computes the blur horizontally and vertically
void ComputeBlur(Shader& BlurVertical, Shader& BlurHorizontal, FrameBuffer& _work1, FrameBuffer& _work2);

//Composites the effect 
void BloomComposite(Shader& BloomComposite, FrameBuffer& _main, FrameBuffer& _work1, FrameBuffer& _work3, bool postProc);

//Creates your bloom effect based on macros set in this file
void ProcessBloom(FrameBuffer& _main, FrameBuffer& _work1, FrameBuffer& _work2, FrameBuffer& _work3,
					std::vector<Shader*>& bloomComponents, bool postProc);
#endif // !__UTILITIES_H__
