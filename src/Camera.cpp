#include "Camera.h"

Camera::Camera()
{
	// Values set
	m_origin = { 0.0f, 0.0f, 0.0f };
	m_horizontal = { 4.0f, 0.0f, 0.0f };
	m_vertical = { 0.0f, 2.0f, 0.0f };
	m_bottomLeftCorner = { -2.0f, -1.0, -1.0f };
}

glm::vec3 Camera::GetOrigin() const
{
	return m_origin;
}

glm::vec3 Camera::GetHorizontal() const
{
	return m_horizontal; 
}

glm::vec3 Camera::GetVertical() const
{
	return m_vertical; 
}

glm::vec3 Camera::GetBottomLeftCorner() const
{
	return m_bottomLeftCorner;
}
