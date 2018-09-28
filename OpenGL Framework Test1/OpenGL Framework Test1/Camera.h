#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Transform.h"

class Camera {
public:
	//Constructs our camera
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, const glm::vec3& forward=glm::vec3(0.0,0.0,-1.0), const glm::vec3& up=glm::vec3(0.0,1.0,0.0))
	{
		//Uses the GLM libray to create the perspective matrix.
		//Fov refers to the field of view you want your perspective to have
		//Aspect is the aspect ratio for the screen you're using, such that things adjust correctly
		//when you perform transformations on them.
		//Znear and zFar refer to the distance at which you can see things, these prevent you from
		//seeing things that are infinitely far away from your camera or are infinitely close to your camera.
		//The perspective matrix doesn't really change from when you run the program.
		//Will need to add something for recalculating the perspective matrix for after the program runs.
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	
		//Sets the position to the postion we passed in the beginning
		m_position = pos;

		//Used for the movement of the camera, (and obviously the creation but these are used as axes of movement more than anything else)
		m_forward = forward;
		m_sideways = glm::vec3(-1, 0, 0);
		m_up = up;
		m_rotation = glm::vec3(0, 0, 0);
	}

	//gets our perspective projection
	inline glm::mat4 getProjection() const
	{
		return m_perspective;
	}

	//Gets our view projections matrix, that allows us to see what we needed to see
	inline glm::mat4 getView() const
	{
		return glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	//So here I'm attempting to figure out how to rotate the camera based on the mouse, which means
	//It needs to be passed a value
	inline void rotate(const glm::mat4& rot) 
	{
		m_forward = rot * glm::vec4(m_forward, 1.0f);
		//m_sideways = rot * glm::vec4(m_sideways, 1.0f);
	}
	
	//Rotates the sideways axis so that it isn't slanted or messed up (work in progress cuz it's still slanted and messed up)
	inline void rotateSideways(const glm::mat4& rot)
	{
		m_sideways = rot * glm::vec4(m_sideways, 1.0f);
	}

	inline void translate(const glm::mat4& translate)
	{
		m_position = translate * glm::vec4(m_position, 1.0f);
	}


	//Getters
	inline glm::vec3& getPos() { return m_position; }
	inline glm::vec3& getForward() { return m_forward; }
	inline glm::vec3& getSideways() { return m_sideways; }
	inline glm::vec3& getUp() { return m_up; }

	//Setters
	inline void setPos(glm::vec3& pos) { m_position = pos; }
	inline void setForward(glm::vec3& forward) { m_forward = forward; }
	inline void setSideways(glm::vec3& sideways) { m_sideways = sideways; }
	inline void setUp(glm::vec3& up) { m_up = up; }

private:
	Transform transform;

	//Perspective for the camera
	glm::mat4 m_perspective;
	//Position the camera is in
	glm::vec3 m_position;

	//This is a ghetto way of representing rotation
	//Essentially forward is whatever direction vector applies to what the camera
	//sees as forward
	///Have this set to a default of glm::vec3(0,0,-1) which is literally a line in the z axis
	glm::vec3 m_forward;
	glm::vec3 m_sideways;

	//Used in tandem with up, which is whatever direction your camera perceives as directly up
	glm::vec3 m_up;
	
	//For the rotation of the camera
	glm::vec3 m_rotation;
};



#endif // !__CAMERA_H__
