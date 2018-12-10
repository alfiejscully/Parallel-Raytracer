#ifndef _RAY_H_
#define _RAY_H_

// Libary includes
#include <glm/glm.hpp>


class Ray
{
private:
	glm::vec3 m_origin = { 0.0f, 0.0f, 0.0f }; // a
	glm::vec3 m_direction = { 0.0f, 0.0f, 0.0f }; // b

public:
	Ray() {}
	Ray(const glm::vec3& _origin, const glm::vec3 _direction);

	glm::vec3 GetOrigin() const; // Gets the origin of the ray
	glm::vec3 GetDirection() const; // Gets the direction of the ray
	glm::vec3 GetRayPoint(float _position) const; // Gets the posistion of ray
};
#endif