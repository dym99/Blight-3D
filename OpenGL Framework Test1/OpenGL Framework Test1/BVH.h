#ifndef __BVH_H__
#define __BVH_H__

/*
//https://www.gamedev.net/articles/programming/general-and-gameplay-programming/bvh-file-loading-and-displaying-r3295/
//The class is from this site
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cstring>

#include "glm/glm.hpp"

#define Xposition 0x01
#define Yposition 0x02
#define Zposition 0x04
#define Zrotation 0x10
#define	Xrotation 0x20
#define Yrotation 0x40

typedef struct
{
	float x, y, z;
} OFFSET;

//typedef struct JOINT JOINT;

struct JOINT
{
	const char* name = nullptr;					//Joint name
	JOINT* parent = nullptr;					//Joing parent
	OFFSET offset;								//Bone offset
	unsigned int num_channels = 0;				//Number of channels joint has
	short* channels_order = nullptr;			//ordered list of channels
	std::vector<JOINT*> children;				//Joint's children
	glm::mat4 matrix;							//local transformation matrix (premultiplied with parent's
	unsigned int channel_start = 0;				//Index of joint's channel data in motion array
};

typedef struct
{
	JOINT* rootJoint = nullptr;
	int num_channels;
} HIERARCHY;

typedef struct
{
	unsigned int num_frames;					//Number of frames
	unsigned int num_motion_channels = 0;		//Number of motion channels
	float* data = nullptr;						//Motion float data array
	unsigned* joint_channel_offsets = nullptr;	//Number of channels from beginning of hierarchy for the i-th joint
} MOTION;


class BVH
{
	JOINT* loadJoint(std::istream& stream, JOINT* parent = NULL);
	void loadHierarchy(std::istream& stream);
	void loadMotion(std::istream& stream);
public:
	BVH();
	~BVH();

	//Loading
	void load(const std::string& filename);
	void loadTransforms(const JOINT* joint, unsigned frame, bool _nextFrame = false);

	/** Loads motion data from a frame into local matrices */
	static void moveJoint(JOINT* joint, MOTION* motionData, int frame_starts_index);
	void moveTo(unsigned frame);

	const JOINT* getRootJoint() const { return rootJoint; }
	unsigned getNumFrames() const { return motionData.num_frames; }
	std::vector<glm::mat4> getCurrentFrame() const { return currentFrame; }
	std::vector<glm::mat4> getNextFrame() const { return nextFrame; }
private:
	JOINT* rootJoint;
	MOTION motionData;

	std::vector<glm::mat4> currentFrame;
	std::vector<glm::mat4> nextFrame;
};

#endif // !__BVH_H__
