#ifndef _P_COLLIDER_H_
#define _P_COLLIDER_H_
#include <glm/glm.hpp>
#include <vector>

enum P_Collider_Type
{
	BOX,
	SPHERE,
	CAPSULE
};

class P_Collider
{
public:
	P_Collider(P_Collider_Type = BOX, float h = 1.0f, float w = 1.0f, float d = 1.0f);

	float getHeight() { return P_height; }
	float getWidth() { return P_width; }
	float getDepth() { return P_depth; }
	P_Collider_Type getType() { return P_type; }
	int getTag() { return P_tag; }
	float getMaxSize() { return P_maxSize; }
	glm::vec3 getOffset() { return P_offset; }
	void setOffset(glm::vec3 _offset) { P_offset = _offset; }


private:
	P_Collider_Type P_type;

	//Objects can ignore other objects when simulating using ignore tags
	int P_tag;
	std::vector<int> P_tagsToIgnore{};
		
	//Used as radius for SPHERE type
	float P_height;
	//Used as radius for CAPSULE type
	float P_width;
	//Used only by BOX type
	float P_depth;

	//Farthest point of the collider, used for bounding sphere
	float P_maxSize;

	glm::vec3 P_offset;

};

#endif // !_P_COLLIDER_H_
