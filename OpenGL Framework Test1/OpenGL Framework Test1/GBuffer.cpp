#include "GBuffer.h"
#include "ShaderManager.h"
#include "Utilities.h"
#include <iostream>

GBuffer::GBuffer(float _windowWidth, float _windowHeight) : FrameBuffer(4)
{
	initDepthTexture(_windowWidth, _windowHeight);
	initColorTexture(0, _windowWidth, _windowHeight, GL_RGBA8, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Albedo Buffer
	initColorTexture(1, _windowWidth, _windowHeight, GL_RGB8, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Normal Buffer
	initColorTexture(2, _windowWidth, _windowHeight, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Positions Buffer
	initColorTexture(3, _windowWidth, _windowHeight, GL_RGB32F, GL_NEAREST, GL_CLAMP_TO_EDGE);		//Emissives Buffer

	if (!checkFBO())
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
	unload();
}

void GBuffer::bindLighting()
{
	bindTex(0, 0);			// Bind Albedo
	bindTex(1, 1);			// Bind Normal
	bindTex(2, 2);			// Bind Positions
	bindTex(3, 3);			// Bind Emissives
}

void GBuffer::unbindLighting()
{
	unbindTex(3);			// Unbind Emissives
	unbindTex(2);			// Unbind Positions
	unbindTex(1);			// Unbind Normal
	unbindTex(0);			// Unbind Albedo
}

void GBuffer::bindEdge()
{
	bindTex(0, 1);
	bindTex(1);
}

void GBuffer::unbindEdge()
{
	unbindTex(1);
	unbindTex(0);
}

void GBuffer::reshape(unsigned windowWidth, unsigned windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	resize(windowWidth, windowHeight);
}

void GBuffer::drawBuffers()
{
	glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);					///Top Left
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	bindTex(0, 0);															//Albedo Color
	FrameBuffer::drawFSQ();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	glViewport(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);	///Top Right
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	bindTex(0, 1);															//Normals
	FrameBuffer::drawFSQ();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();

	glViewport(0, 0, windowWidth / 2, windowHeight / 2);									///Bottom Left
	ShaderManager::getPost(PASSTHROUGH_POST)->bind();
	ShaderManager::getPost(PASSTHROUGH_POST)->sendUniform("uTex", 0);
	bindTex(0, 3);															//Frag Positions 
	FrameBuffer::drawFSQ();
	unbindTex(0);
	ShaderManager::getPost(PASSTHROUGH_POST)->unbind();
}
