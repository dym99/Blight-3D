#include "BVH.h"
#include "Utilities.h"

JOINT * BVH::loadJoint(std::istream & stream, JOINT * parent)
{
	JOINT* joint = new JOINT;
	joint->parent = parent;

	//Load joint name
	std::string* name = new std::string;
	stream >> *name;
	joint->name = name->c_str();

	std::string tmp;

	joint->matrix = glm::mat4(1.0f);

	static int _channel_start = 0;
	unsigned channel_order_index = 0;

	while (stream.good())
	{
		stream >> tmp;
		tmp = trim(tmp);

		//loading channels
		char c = tmp.at(0);
		if (c == 'X' || c == 'Y' || c == 'Z')
		{
			if (tmp == "Xposition")
			{
				joint->channels_order[channel_order_index++] = Xposition;
			}
			if (tmp == "Yposition")
			{
				joint->channels_order[channel_order_index++] = Yposition;
			}
			if (tmp == "Zposition")
			{
				joint->channels_order[channel_order_index++] = Zposition;
			}

			if (tmp == "Xrotation")
			{
				joint->channels_order[channel_order_index++] = Xrotation;
			}
			if (tmp == "Yrotation")
			{
				joint->channels_order[channel_order_index++] = Yrotation;
			}
			if (tmp == "Zrotation")
			{
				joint->channels_order[channel_order_index++] = Zrotation;
			}
		}


		if (tmp == "OFFSET")
		{
			//Reading in offset values
			stream >> joint->offset.x
				   >> joint->offset.y
				   >> joint->offset.z;
		}
		else if (tmp == "CHANNELS")
		{
			//loading num of channels
			stream >> joint->num_channels;

			//Adding to the motion data
			motionData.num_motion_channels += joint->num_channels;

			//Increasing static counter of channel index startin motion section
			joint->channel_start = _channel_start;
			_channel_start += joint->num_channels;

			//creating array for channel order specifications
			joint->channels_order = new short[joint->num_channels];

		}
		else if (tmp == "JOINT")
		{
			//Loading child joint and setting this as a parent
			JOINT* tmp_joint = loadJoint(stream, joint);

			tmp_joint->parent = joint;
			joint->children.push_back(tmp_joint);
		}
		else if (tmp == "End")
		{
			//loading end site joint
			stream >> tmp >> tmp; // site {
			
			JOINT* tmp_joint = new JOINT;

			tmp_joint->parent = joint;
			tmp_joint->num_channels = 0;
			tmp_joint->name = "EndSite";
			joint->children.push_back(tmp_joint);

			stream >> tmp;
			if (tmp == "OFFSET")
			{
				stream >> tmp_joint->offset.x
					   >> tmp_joint->offset.y
					   >> tmp_joint->offset.z;
			}
				stream >> tmp;
		}
		else if (tmp == "}")
		{
			return joint;
		}
	}
	return nullptr;
}

void BVH::loadHierarchy(std::istream & stream)
{
	std::string tmp;

	while (stream.good())
	{
		stream >> tmp;

		if (trim(tmp) == "ROOT")
			rootJoint = loadJoint(stream);
		else if (trim(tmp) == "MOTION")
			loadMotion(stream);
	}
}

void BVH::loadMotion(std::istream & stream)
{
	std::string tmp;

	while (stream.good())
	{
		stream >> tmp;

		if (trim(tmp) == "Frames:")
		{
			//Loading frame number
			stream >> motionData.num_frames;
		}
		else if (trim(tmp) == "Frame")
		{
			//loading frame time
			float frame_time;
			stream >> tmp >> frame_time;

			int num_frames		= motionData.num_frames;
			int num_channels	= motionData.num_motion_channels;

			//creating motion data array
			motionData.data = new float[num_frames * num_channels];

			//foreach frame read and store floats'
			for (int frame = 0; frame < num_frames; ++frame)
			{
				for (int channel = 0; channel < num_channels; ++channel)
				{
					float x;
					std::stringstream ss;
					stream >> tmp;
					ss << tmp;
					ss >> x;

					// calculating index for storage
					int index = frame * num_channels + channel;
					motionData.data[index] = x;
				}
			}
		}
	}
}

BVH::BVH()
{
}

BVH::~BVH()
{
}

void BVH::load(const std::string & filename)
{
	std::fstream file;
	file.open(filename.c_str(), std::ios_base::in);

	if (file.is_open())
	{
		std::string line;

		while (file.good())
		{
			file >> line;
			if (std::strstr(line.c_str(), "HIERARCHY") != nullptr)
				loadHierarchy(file);
			break;
		}

		file.close();
	}
}

void BVH::loadTransforms(const JOINT * joint, unsigned frame, bool _nextFrame)
{
	std::vector<glm::mat4>* vector = _nextFrame ? &nextFrame : &currentFrame;

	vector->push_back(joint->matrix);

	for (auto child : joint->children)
	{
		loadTransforms(joint, frame, _nextFrame);
	}
}


/**
			Calculates JOINT's local transformation matrix for
			specified from starting index
*/
void BVH::moveJoint(JOINT * joint, MOTION * motionData, int frame_starts_index)
{
	//We'll need index of motion data's array with start of this specified joint
	int start_index = frame_starts_index + joint->channel_start;

	//Translate identity matrix to this joint's offset parameters
	joint->matrix = glm::translate(glm::mat4(1.0),
								   glm::vec3(joint->offset.x,
											 joint->offset.y,
											 joint->offset.z));

	//Here we transform joint's local matrix with each specified channel's values
	//Which are read from motion data
	for (int i = 0; i < joint->num_channels; i++)
	{
		const short& channel = *joint->channels_order;

		float value = motionData->data[start_index + i];

		//Translations
		if (channel & Xposition)
		{
			joint->matrix = glm::translate(joint->matrix, glm::vec3(value, 0.f, 0.f));
		}
		if (channel & Yposition)
		{
			joint->matrix = glm::translate(joint->matrix, glm::vec3(0.f, value, 0.f));
		}
		if (channel & Zposition)
		{
			joint->matrix = glm::translate(joint->matrix, glm::vec3(0.f, 0.f, value));
		}

		//Rotations
		if (channel & Xrotation)
		{
			joint->matrix = glm::rotate(joint->matrix, value, glm::vec3(1.f, 0.f, 0.f));
		}
		if (channel & Yrotation)
		{
			joint->matrix = glm::rotate(joint->matrix, value, glm::vec3(0.f, 1.f, 0.f));
		}
		if (channel & Zrotation)
		{
			joint->matrix = glm::rotate(joint->matrix, value, glm::vec3(0.f, 0.f, 1.f));
		}
	}

	if (joint->parent != NULL)
		joint->matrix = joint->parent->matrix * joint->matrix;

	
	for (auto& child : joint->children)
		moveJoint(child, motionData, frame_starts_index);
}

void BVH::moveTo(unsigned frame)
{
	// we calculate motion data's array start index for a frame
	unsigned start_index = frame * motionData.num_motion_channels;

	//Recursively transform skeleton
	moveJoint(rootJoint, &motionData, start_index);
}

