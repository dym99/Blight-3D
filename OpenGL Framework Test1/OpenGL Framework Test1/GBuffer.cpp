#include "GBuffer.h"
#include "ShaderManager.h"
#include "Utilities.h"
#include <iostream>

GBuffer::GBuffer(float _windowWidth, float _windowHeight) : FrameBuffer(3)
{
	InitDepthTexture(_windowWidth, _windowHeight);
	InitColorTexture(0, _windowWidth, _windowHeight, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Albedo Buffer
	InitColorTexture(1, _windowWidth, _windowHeight, GL_RGB8, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Normal Buffer
	InitColorTexture(2, _windowWidth, _windowHeight, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);

	if (!CheckFBO())
	{
		std::cout << "GBuffer failed to load" << std::endl;
		system("pause");
		exit(0);
	}

	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

GBuffer::~GBuffer()
{
	Unload();
}

void GBuffer::bindLighting()
{
	bindTex(0, 0);
	bindTex(1, 1);
	bindTex(2, 2);
}

void GBuffer::unbindLighting()
{
	unbindTex(0);
	unbindTex(1);
	unbindTex(2);
}

void GBuffer::drawBuffers()
{
	glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);					///Top Left
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	bindTex(0, 0);															//Albedo Color
	DrawFullScreenQuad();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	glViewport(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);	///Top Right
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	bindTex(0, 1);															//Normals
	DrawFullScreenQuad();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	glViewport(0, 0, windowWidth / 2, windowHeight / 2);									///Bottom Left
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	bindTex(0, 2);															//Frag Positions 
	DrawFullScreenQuad();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();
}
