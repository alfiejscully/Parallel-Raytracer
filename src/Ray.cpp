#include "Ray.h"

Ray::Ray(const glm::vec3 & _origin, const glm::vec3 _direction)
{
	m_origin = _origin;
	m_direction = _direction;
}

glm::vec3 Ray::GetOrigin() const
{
	return m_origin;
}

glm::vec3 Ray::GetDirection() const
{
	return m_direction;
}

glm::vec3 Ray::GetRayPoint(float _position) const
{
	return m_origin + _position * m_direction;
}
