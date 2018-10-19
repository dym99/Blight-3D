#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Transform.h"

enum class ProjectionType {
	Perspective,
	Orthographic
};

class Camera {
public:
	//Default camera constructor
	Camera() : Camera(ProjectionType::Perspective) { }

	//Camera construction based on default params
	Camera(ProjectionType type);

	//Methods
	void Perspective(float fovy, float aspect, float zNear, float zFar);
	void Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
	inline void Rotate(const glm::mat4& rot) { m_forward = rot * glm::vec4(m_forward, 1.0f); }
	inline void RotateSideways(const glm::mat4& rot) { m_sideways = rot * glm::vec4(m_sideways, 1.0f); }
	inline void Translate(const glm::mat4& translate) { m_position = translate * glm::vec4(m_position, 1.0f); }

	//gets our perspective projection
	inline glm::mat4 GetProjection() const { return m_projection; }
	//Gets our view projections matrix, that allows us to see what we needed to see
	inline glm::mat4 GetView() const { return glm::lookAt(m_position, m_position + m_forward, m_up); }
	
	//Getters
	inline glm::vec3& GetPos() { return m_position; }
	inline glm::vec3& GetForward() { return m_forward; }
	inline glm::vec3& GetSideways() { return m_sideways; }
	inline glm::vec3& GetUp() { return m_up; }

	//Setters
	inline void SetPos(glm::vec3 pos) { m_position = pos; }
	inline void SetForward(glm::vec3 forward) { m_forward = forward; }
	inline void SetSideways(glm::vec3 sideways) { m_sideways = sideways; }
	inline void SetUp(glm::vec3 up) { m_up = up; }

private:
	//Projection for the camera
	glm::mat4 m_projection;

	//Position the camera is in
	glm::vec3 m_position;

	//This is a ghetto way of representing rotation
	//Essentially forward is whatever direction vector applies to what the camera
	//sees as forward
	glm::vec3 m_forward;
	glm::vec3 m_sideways;

	//Used in tandem with up, which is whatever direction your camera perceives as directly up
	glm::vec3 m_up;
};



#endif // !__CAMERA_H__
