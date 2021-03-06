// Libary includes
#include <glm/glm.hpp>

// System includes 
#include <memory>
#include <time.h>

// Included for inheritance
#include "RayHitAble.h"

// Forward declares
class Ray;
struct RayHit;
class Material;

class Object : public RayHitAble
{
private:
	// Value of centre
	glm::vec3 m_centre = { 0.0f, 0.0f, 0.0f };

	// Value of radius
	float m_radius = 0.0f;

	Material* m_material;

public:
	Object() {};
	Object(glm::vec3 _centre, float _radius, Material* m_material);

	virtual bool Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit& _rayHit) const;

	glm::vec3 RandomNumInObj();

	glm::vec3 Colour(std::shared_ptr<Ray> _ray, RayHitAble* _world, int _depth);

};