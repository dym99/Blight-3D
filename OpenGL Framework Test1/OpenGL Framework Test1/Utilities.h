////This file is for functions that have use but wouldn't fit 
////into the functionality of a certain class
//#ifndef __UTILITIES_H__
//#define __UTILITES_H__
//
//#include "Shader.h"
//#include "FrameBuffer.h"
//#include <vector>
//
////#define window_width			1280.f
////#define window_height			720.f
//#define BLOOM_THRESHOLD         0.15f
//#define BLOOM_DOWNSCALE			4.0f
//#define BLOOM_BLUR_PASSES		4
//
//void printDebugControls();
//
////Runs the high pass for the bloom effect
//void BloomHighPass(Shader& BloomHighPass, FrameBuffer& _main, FrameBuffer& _work1);
//
////Computes the blur horizontally and vertically
//void ComputeBlur(Shader& BlurVertical, Shader& BlurHorizontal, FrameBuffer& _work1, FrameBuffer& _work2);
//
////Composites the effect 
//void BloomComposite(Shader& BloomComposite, FrameBuffer& _main, FrameBuffer& _work1, FrameBuffer& _work3, bool postProc);
//
////Creates your bloom effect based on macros set in this file
//void ProcessBloom(FrameBuffer& _main, FrameBuffer& _work1, FrameBuffer& _work2, FrameBuffer& _work3,
//					std::vector<Shader*>& bloomComponents, bool postProc);
//
//void ProcessPostProc(FrameBuffer& _buffer, Shader& shader);
//
//void ProcessFramebufferStuff(FrameBuffer& _main, FrameBuffer& _work1, FrameBuffer& _work2, FrameBuffer& _work3,
//								std::vector<Shader*>& bloomComponents, Shader& postProcShader, bool postProc, bool hasBloom);
//#endif // !__UTILITIES_H__