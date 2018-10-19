#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>


//#include

class Transform {
public:
	//Constructors
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0)) :
		m_position(pos), m_rotation(rot), m_scale(scale) {}

	//Methods
	
	//End Methods

	//Getters and Setters
		inline glm::mat4 GetModel() const
		{
			//Position matrix
			glm::mat4 positionMatrix = glm::translate(m_position);
			//Rotation matrix components
			glm::mat4 rotationXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
			glm::mat4 rotationYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
			glm::mat4 rotationZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
			//Scale Matrix
			glm::mat4 scaleMatrix = glm::scale(m_scale);

			//Must write backwards needs to be written in opposite order you want them to apply.
			glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

			//Apply scale, then rotation, then position here
			//So we reverse it, and do position * rotation * scale
			return positionMatrix * rotationMatrix * scaleMatrix;
		}
		
		inline glm::vec3& GetPos() { return m_position; }
		inline glm::vec3& GetRot() { return m_rotation; }
		inline glm::vec3& GetScale() { return m_scale; }

		inline void SetPos(glm::vec3 pos) {m_position = pos;}
		inline void SetRot(glm::vec3 rot) {m_rotation = rot;}
		inline void SetScale(glm::vec3 scale) {m_scale = scale;}
	//End Getters and Setters

	//Deconstructors
	//~Transform();
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};



#endif // !__TRANSFORM_H__
