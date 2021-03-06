#include "Object.h"
#include "Ray.h"
#include "Randomizer.h"
#include "Material.h"

Object::Object(glm::vec3 _centre, float _radius, Material* _material)
{
	// Values being stored 
	m_centre = _centre;
	m_radius = _radius;
	m_material = _material;
}

bool Object::Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit & _rayHit) const
{
	// calulates the distance of the start point to the centre of the object
	glm::vec3 objectCentre = _ray->GetOrigin() - m_centre;

	// calculating using the quadratic formula 
	float a = glm::dot(_ray->GetDirection(), _ray->GetDirection());
	float b = glm::dot(objectCentre, _ray->GetDirection());
	float c = glm::dot(objectCentre, objectCentre) - m_radius * m_radius;
	float discriminant = b * b - a * c;

	// check if it is greater than 0 
	if (discriminant > 0)
	{
		// First soultion of quadratic
		float rayPos = (-b - glm::sqrt(b * b - a * c)) / a;

		// Checks if ray pos is in bound
		if (rayPos < _max && rayPos > _min)
		{
			// Hit values of ray set
			_rayHit.m_position = rayPos;
			_rayHit.m_point = _ray->GetRayPoint(_rayHit.m_position);
			_rayHit.m_normal = (_rayHit.m_point - m_centre) / m_radius;
			_rayHit.m_material = m_material;

			// Returns true after intersection to object
			return true;
		}

		// Second soultion of quadratic
		rayPos = (-b + glm::sqrt(b * b - a * c)) / a;

		// Checks if ray pos is in bound
		if (rayPos < _max && rayPos > _min)
		{
			// Hit values of ray set
			_rayHit.m_position = rayPos;
			_rayHit.m_point = _ray->GetRayPoint(_rayHit.m_position);
			_rayHit.m_normal = (_rayHit.m_point - m_centre) / m_radius;
			_rayHit.m_material = m_material;

			// Returns true after intersection to obj
			return true;
		}
	}

	// Returns false if no intersection is made to obj
	return false;
}

glm::vec3 Object::RandomNumInObj()
{
	// point has been set
	glm::vec3 point = { 0.0f, 0.0f, 0.0f };

	// Randomizer insatnace created
	Randomizer rand;

	do
	{
		// point is timed by two and randomized
		point = 2.0f * glm::vec3(rand.RandomNumber(), rand.RandomNumber(), rand.RandomNumber()) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (point.x * point.x + point.y * point.y + point.z * point.z >= 1.0f);
	return point;
}

glm::vec3 Object::Colour(std::shared_ptr<Ray> _ray, RayHitAble* _world, int _depth)
{
	// creates the hit point from ray
	RayHit rayHit;

	// Check in the table for any ray hits to any objects
	if (_world->Hit(_ray, 0.001f, std::numeric_limits<float>::max(), rayHit))
	{
		std::shared_ptr<Ray> scattered = std::make_shared<Ray>();
		glm::vec3 attenuation = { 0.0f, 0.0f, 0.0f };

		if (_depth < 50 && rayHit.m_material->Scatter(_ray, rayHit, attenuation, scattered))
		{
			return attenuation * Colour(scattered, _world, _depth + 1);
		}
		else
		{
			return glm::vec3 { 0.0f, 0.0f, 0.0f };
		}
		/*glm::vec3 target = rayHit.m_point + rayHit.m_normal + RandomNumInObj();

		std::shared_ptr<Ray> m_ray = std::make_shared<Ray>(rayHit.m_point, target - rayHit.m_point);

		return 0.5f * Colour(m_ray, _world, 0);*/
	}
	else
	{
		glm::vec3 unitDirection = glm::normalize(_ray->GetDirection());

		float t = 0.5f * (unitDirection.y + 1.0f);

		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}
}