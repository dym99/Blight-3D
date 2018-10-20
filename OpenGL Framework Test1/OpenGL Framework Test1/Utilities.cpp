#include "Utilities.h"
#include <GL/glew.h>

#define BUFFER_OFFSET(i) ((char *) 0 + (i))

GLuint fullScreenQuadVAO = GL_NONE;
GLuint fullScreenQuadVBO = GL_NONE;


void InitFullScreenQuad()
{
	float VBO_DATA[]{
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		-1.f, 1.f, 0.f,

		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f,
		1.f, -1.f, 0.f,

		0.f, 0.f,
		1.f, 0.f,
		0.f, 1.f,

		1.f, 1.f,
		0.f, 1.f,
		1.f, 0.f,
	};

	int vertexSize = 6 * 3 * sizeof(float);
	int texCoordSize = 6 * 2 * sizeof(float);

	glGenVertexArrays(1, &fullScreenQuadVAO);
	glBindVertexArray(fullScreenQuadVAO);

	glEnableVertexAttribArray(0); //vertices
	glEnableVertexAttribArray(1); //UV coordinates

	glGenBuffers(1, &fullScreenQuadVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, fullScreenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize + texCoordSize, VBO_DATA, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));			//send vertex attributes
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSize)); //send uv attributes

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);
}

void DrawFullScreenQuad()
{
	glBindVertexArray(fullScreenQuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(GL_NONE);
}

void BloomHighPass(Shader & BloomHighPass, FrameBuffer & _main, FrameBuffer & _work1)
{
	/// Compute High pass ///
	glViewport(0, 0, WINDOW_WIDTH / BLOOM_DOWNSCALE, WINDOW_HEIGHT / BLOOM_DOWNSCALE);

	BloomHighPass.Bind();
	BloomHighPass.SetInt("uTex", 0);
	BloomHighPass.SetFloat("uThreshold", BLOOM_THRESHOLD);

	_work1.Bind();

	//Gets result of the previous render
	glBindTexture(GL_TEXTURE_2D, _main.GetColorHandle(0));
	DrawFullScreenQuad();
	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	_work1.Unbind();
	BloomHighPass.Unbind();
}

void ComputeBlur(Shader & BlurVertical, Shader & BlurHorizontal, FrameBuffer & _work1, FrameBuffer & _work2)
{
	/// Computer Blur ///
	for (int i = 0; i < BLOOM_BLUR_PASSES; i++) {
		//Horizontal Blur
		BlurHorizontal.Bind();
		BlurHorizontal.SetInt("uTex", 0);
		BlurHorizontal.SetFloat("uPixelSize", 1.0f / WINDOW_WIDTH);

		_work2.Bind();

		glBindTexture(GL_TEXTURE_2D, _work1.GetColorHandle(0));
		DrawFullScreenQuad();
		glBindTexture(GL_TEXTURE_2D, GL_NONE);

		_work2.Unbind();
		BlurHorizontal.Unbind();

		//Vertical Blur
		BlurVertical.Bind();
		BlurVertical.SetInt("uTex", 0);
		BlurVertical.SetFloat("uPixelSize", 1.0f / WINDOW_HEIGHT);

		_work1.Bind();

		glBindTexture(GL_TEXTURE_2D, _work2.GetColorHandle(0));
		DrawFullScreenQuad();
		glBindTexture(GL_TEXTURE_2D, GL_NONE);

		_work1.Unbind();
		BlurVertical.Unbind();
	}
}

void BloomComposite(Shader & BloomComposite, FrameBuffer & _main, FrameBuffer & _work1, FrameBuffer& _work3, bool postProc)
{
	/// Composite the Scene ///
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	BloomComposite.Bind();
	BloomComposite.SetInt("uScene", 0);
	BloomComposite.SetInt("uScene", 1);

	if (postProc) {
		_work3.Bind();
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _main.GetColorHandle(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _work1.GetColorHandle(0));
		DrawFullScreenQuad();
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	_work3.Unbind();
	BloomComposite.Unbind();
}

void ProcessBloom(FrameBuffer & _main, FrameBuffer & _work1, FrameBuffer & _work2, FrameBuffer& _work3, std::vector<Shader*>& bloomComponents, bool postProc)
{
	BloomHighPass(*bloomComponents[0], _main, _work1);
	ComputeBlur(*bloomComponents[1], *bloomComponents[2], _work1, _work2);
	BloomComposite(*bloomComponents[3], _main, _work1, _work3, postProc);
}
