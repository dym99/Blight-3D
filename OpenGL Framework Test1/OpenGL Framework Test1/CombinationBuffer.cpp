#include "CombinationBuffer.h"
#include <iostream>
#include "Utilities.h"

CombinationBuffer::CombinationBuffer(float _windowWidth, float _windowHeight) : FrameBuffer(1)
{
	InitDepthTexture(_windowWidth, _windowHeight);
	InitColorTexture(0, _windowWidth, _windowHeight, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);

	if (!CheckFBO())
	{
		std::cout << "Combination Buffer Failed to Load" << std::endl;
		system("pause");
		exit(0);
	}
}

CombinationBuffer::~CombinationBuffer()
{
	Unload();
}

void CombinationBuffer::combineColorBuffers(FrameBuffer * buffer1, FrameBuffer * buffer2, ShaderTypes type, int shaderIndex)
{
	//Grabs correct shader
	Shader* shader = nullptr;
	switch (type)
	{
	case 0:
		shader = ShaderManager::getShader(shaderIndex);
		break;
	case 1:
		shader = ShaderManager::getGeom(shaderIndex);
		break;
	case 2:
		shader = ShaderManager::getPost(shaderIndex);
		break;
	default:
		std::cout << "Invalid shader type given" << std::endl;
		return;
		break;
	}

	//Bind framebuffer
	this->Bind();
	//Bind shader
	shader->bind();
	//Bind the buffer color textures
	buffer1->bindTex(0, 0);
	buffer2->bindTex(1, 0);
	//Activates all pixels on screen
	DrawFullScreenQuad();
	//Unbinds the buffer color textures
	buffer2->unbindTex(1);
	buffer1->unbindTex(0);
	//Unbinds shader
	shader->unbind();
	//Unbind framebuffer
	this->Unbind();
}

void CombinationBuffer::drawBuffers()
{
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	bindTex(0, 0);
	DrawFullScreenQuad();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();
}
