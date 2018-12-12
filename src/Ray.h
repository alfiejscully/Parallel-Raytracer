#ifndef _RAY_H_
#define _RAY_H_

// Libary includes
#include <glm/glm.hpp>


class Ray
{
private:
	glm::vec3 m_origin = { 0.0f, 0.0f, 0.0f }; // origin point stored in this variable
	glm::vec3 m_direction = { 0.0f, 0.0f, 0.0f }; // drection point stored in this variable

public:
	Ray() {}
	Ray(const glm::vec3& _origin, const glm::vec3 _direction);

	glm::vec3 GetOrigin() const; // Returns the origin point of the ray
	glm::vec3 GetDirection() const; // Returns the direction point of the ray
	glm::vec3 GetRayPoint(float _position) const; // Returns the pos point along the ray
};
#endif