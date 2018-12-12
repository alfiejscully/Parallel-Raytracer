#ifndef _RAYHITABLE_H_
#define _RAYHITABLE_H_
// System includes
#include<memory>

// Libary includes
#include <glm/glm.hpp>

class Ray;

struct RayHit
{
	float m_position = 0.0f;
	glm::vec3 m_point = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_normal = { 0.0f, 0.0f, 0.0f };


};

class RayHitTable
{
private:


public:
	virtual bool Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit& _rayHit) const = 0;

};
#endif