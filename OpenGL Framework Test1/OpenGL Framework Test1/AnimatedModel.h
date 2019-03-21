#ifndef __ANIMATEDMODEL_H__
#define __ANIMATEDMODEL_H__

#include "Shader.h"
#include "Texture.h"
#include "IModel.h"


class AnimatedModel
{
public:
	AnimatedModel();
	AnimatedModel(const AnimatedModel&);
	~AnimatedModel();

	///<summary>
	///Loads files with the nameing convention (_path/_nameN.imdl,
	///Where N is any number between 0 and FrameCount-1.
	///Unpacked frames (position and normal data) are stored in RAM in 2D float vectors: m_framesPos, m_framesNorm (respectively)
	///The UV data is all based on the first frame.
	///</summary>
	///<param name='_frameCount'>Number of frames to load in.</param>
	///<param name='_name'>Filename (before frame number and after path)</param>
	///<param name='_path'>Folder containing the file; should always end with a slash.</param>
	void loadFromFiles(int _frameCount, const std::string& _name, const std::string& _path = "Resources/Objects/");
	void draw(Shader *shader);

	//TODO: just assume textures are named albedo.png, normals.png, spec.png (etc.) unless specifed.
	//Right now, you have to specify.
	void setAlbedo(Texture* _tex);
	void setEmissive(Texture* _tex);

	void update();


	///<summary>
	///Set frame of index '_frame' to take '_time' seconds to get to the next frame.
	///</summary>
	///<param name='_frame'>Index of frame to set time for.</param>
	///<param name='_time'>Time to get to next frame.</param>
	void setFrameTime(size_t _frame, float _time);

	void reset();

	void setAnimSpeed(float _speed);

private:

	void updateFrames();

	//Vertex attributes
	GLuint m_VAO;
	GLuint m_VBO[NUM_VBO];

	//Textures applied to the model.
	//GLuint m_TEX[NUM_TEX_TYPES];

	Texture* m_albedo;
	Texture* m_emissive;

	const char* m_path;
	const char* m_name;

	unsigned int m_numVertices;

	size_t m_frameCount;

	//C - Current Frame, L - Last Frame
	size_t m_cFrame, m_lFrame; 
	//T-value for interpolation
	float m_t;

	std::vector<std::vector<float>> m_framesPos;
	std::vector<std::vector<float>> m_framesNorm;
	std::vector<float> m_uvs;

	std::vector<float> m_frameTimes;

	float m_animSpeed;
};

#endif