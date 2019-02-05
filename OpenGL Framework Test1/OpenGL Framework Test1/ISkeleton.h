#ifndef __ISKELETON_H__
#define __ISKELETON_H__

#include <glm/glm.hpp>
#include <vector>

#include "GameObject.h"


//GameObject that acts as a parent for all bones.
//Make this the parent of a skeleton's root bone.
class ISkeleton : public GameObject
{
public:
	ISkeleton(const std::string& _name);
	~ISkeleton();

	//References to bones in orger of group indeces (for sending to OpenGL)
	std::vector<glm::mat4> m_bones;
};

#endif