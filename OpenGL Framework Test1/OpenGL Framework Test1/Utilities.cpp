//#include "Utilities.h"
//#include <GL/glew.h>
//
//void printDebugControls()
//{
//	std::cout << "Non-Debug Mode Controls:\n\n";
//	std::cout << "Q - exit program\n";
//	std::cout << "Insert - Enable Debug Mode\n\n";
//	std::cout << "When Debug Mode Enabled:\n\n";
//	std::cout << "Camera Controls:\n";
//	std::cout << "Esc - toggle relative mouse motion (starts enabled after you hit insert, Esc makes it so when you tab out\n the camera won't go nuts)\n";
//	std::cout << "Mouse Movement - rotaates camera and rotates the various axes the camera moves on (camera moves relative to rotation)\n";
//	std::cout << "W - Move camera forward\n";
//	std::cout << "A - Move camera left\n";
//	std::cout << "S - Move camera backwards\n";
//	std::cout << "D - Move camera right\n";
//	std::cout << "Q - Move camera up\n";
//	std::cout << "E - Move camera down\n\n";
//	std::cout << "Model Controls:\n";
//	std::cout << "Tab - Cycle through model lists (environments, waterplane)\n";
//	std::cout << "I - Move camera forward\n";
//	std::cout << "J - Move camera left\n";
//	std::cout << "K - Move camera backwards\n";
//	std::cout << "L - Move camera right\n";
//	std::cout << "U - Move camera up\n";
//	std::cout << "O - Move camera down\n";
//	std::cout << "Left Arrow - Cycle through model list backwards (are no separate models in here)\n";
//	std::cout << "Right Arrow - Cycle through the model lsit forwards (are no separate models in here)\n\n";
//	std::cout << "Shader controls:\n";
//	std::cout << "F1 - Toggles post processing effect (like greyscale or sepia or vignette)\n";
//	std::cout << "F2 - Toggles Bloom effect (don't recommend for this project, may actually just make everything bloom)\n";
//	std::cout << "F5 - Reloads the shaders\n";
//	std::cout << "Plus - Moves up in the shader list (there's only one shader in the list, won't do anything)\n";
//	std::cout << "Minus - Moves down in the shader list (there's only one shader in the list, won't do anything)\n\n";
//	std::cout << "IF ANY POST PROCESSING EFFECT IS ENABLED:\n";
//	std::cout << "Page Up - Moves up in the post processing shader list\n";
//	std::cout << "Page down - Moves down in the post processing shader list\n\n";
//	std::cout << "This was a long debug control list\n";
//}
//
//void BloomHighPass(Shader & BloomHighPass, FrameBuffer & _main, FrameBuffer & _work1)
//{
//	/// Compute High pass ///
//	glViewport(0, 0, window_width / BLOOM_DOWNSCALE, window_height / BLOOM_DOWNSCALE);
//
//	BloomHighPass.bind();
//	BloomHighPass.sendUniform("uTex", 0);
//	BloomHighPass.sendUniform("uThreshold", BLOOM_THRESHOLD);
//
//	_work1.bind();
//
//	//Gets result of the previous render
//	glBindTexture(GL_TEXTURE_2D, _main.getColorHandle(0));
//	FrameBuffer::drawFSQ();
//	glBindTexture(GL_TEXTURE_2D, GL_NONE);
//
//	_work1.unbind();
//	BloomHighPass.unbind();
//}
//
//void ComputeBlur(Shader & BlurVertical, Shader & BlurHorizontal, FrameBuffer & _work1, FrameBuffer & _work2)
//{
//	/// Computer Blur ///
//	for (int i = 0; i < BLOOM_BLUR_PASSES; i++) {
//		//Horizontal Blur
//		BlurHorizontal.bind();
//		BlurHorizontal.sendUniform("uTex", 0);
//		BlurHorizontal.sendUniform("uPixelSize", 1.0f / window_width);
//
//		_work2.bind();
//
//		glBindTexture(GL_TEXTURE_2D, _work1.getColorHandle(0));
//		FrameBuffer::drawFSQ();
//		glBindTexture(GL_TEXTURE_2D, GL_NONE);
//
//		_work2.unbind();
//		BlurHorizontal.unbind();
//
//		//Vertical Blur
//		BlurVertical.bind();
//		BlurVertical.sendUniform("uTex", 0);
//		BlurVertical.sendUniform("uPixelSize", 1.0f / window_height);
//
//		_work1.bind();
//
//		glBindTexture(GL_TEXTURE_2D, _work2.getColorHandle(0));
//		FrameBuffer::drawFSQ();
//		glBindTexture(GL_TEXTURE_2D, GL_NONE);
//
//		_work1.unbind();
//		BlurVertical.unbind();
//	}
//}
//
//void BloomComposite(Shader & BloomComposite, FrameBuffer & _main, FrameBuffer & _work1, FrameBuffer& _work3, bool postProc)
//{
//	/// Composite the Scene ///
//	glViewport(0, 0, window_width, window_height);
//
//	BloomComposite.bind();
//	BloomComposite.sendUniform("uScene", 0);
//	BloomComposite.sendUniform("uBloom", 1);
//
//	if (postProc) {
//		_work3.bind();
//	}
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, _main.getColorHandle(0));
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, _work1.getColorHandle(0));
//	FrameBuffer::drawFSQ();
//	glBindTexture(GL_TEXTURE_2D, GL_NONE);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, GL_NONE);
//
//	_work3.unbind();
//	BloomComposite.unbind();
//}
//
//void ProcessBloom(FrameBuffer & _main, FrameBuffer & _work1, FrameBuffer & _work2, FrameBuffer& _work3, std::vector<Shader*>& bloomComponents, bool postProc)
//{
//	BloomHighPass(*bloomComponents[0], _main, _work1);
//	ComputeBlur(*bloomComponents[1], *bloomComponents[2], _work1, _work2);
//	BloomComposite(*bloomComponents[3], _main, _work1, _work3, postProc);
//}
//
//void ProcessPostProc(FrameBuffer & _buffer, Shader & shader)
//{
//	shader.bind();
//	shader.sendUniform("uTex", 0);
//
//	glBindTexture(GL_TEXTURE_2D, _buffer.getColorHandle(0));
//	FrameBuffer::drawFSQ();
//	glBindTexture(GL_TEXTURE_2D, GL_NONE);
//
//	Shader::unbind();
//}
//
//void ProcessFramebufferStuff(FrameBuffer & _main, FrameBuffer & _work1, FrameBuffer & _work2, FrameBuffer & _work3, 
//								std::vector<Shader*>& bloomComponents, Shader & postProcShader, bool postProc, bool hasBloom)
//{
//	if (hasBloom) {
//		ProcessBloom(_main, _work1, _work2, _work3, bloomComponents, postProc);
//	}
//	if (postProc) {
//		FrameBuffer* temp;
//		if (hasBloom)
//			temp = &_work3;
//		else
//			temp = &_main;
//
//		ProcessPostProc(*temp, postProcShader);
//	}
//}
