#include "Camera.h"

Camera *Camera::mainCamera = nullptr;
glm::mat4 *Camera::mainCameraTransform = nullptr;

Camera::Camera(ProjectionType type)
{
	if (type == ProjectionType::Perspective)
		Perspective(60.0f, 1.0f, 0.1f, 100.0f);
	else
		Orthographic(-10, 10, -10, 10, -100, 100);

	m_position = glm::vec3(0.f, 0.f, 3.f);

	m_forward = glm::vec3(0.f, 0.f, -1.f);
	m_sideways = glm::vec3(-1.f, 0.f, 0.f);
	m_up = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
}

void Camera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
	m_projection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Camera::Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}