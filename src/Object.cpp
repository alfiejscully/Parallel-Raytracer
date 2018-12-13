#include "Object.h"
#include "Ray.h"

Object::Object(glm::vec3 _centre, float _radius)
{
	// Values being set 
	m_centre = _centre;
	m_radius = _radius;
}

bool Object::Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit & _rayHit) const
{
	// Calculates the distnace between the start point(Origin) of the ray and objects centre
	glm::vec3 objectCentre = _ray->GetOrigin() - m_centre;

	// following floats below are calculating using the quadratic formula 
	float a = glm::dot(_ray->GetDirection(), _ray->GetDirection());
	float b = glm::dot(objectCentre, _ray->GetDirection());
	float c = glm::dot(objectCentre, objectCentre) - m_radius * m_radius;
	float discriminant = b * b - a * c;

	// Checks for the discriminant being greater than 0 and if so an intersection is done
	if (discriminant > 0)
	{
		// Use of the first solution of the quadratic for the rays position
		float rayPos = (-b - glm::sqrt(b * b - a * c)) / a;

		// Checking if the ray poistion is within the bounds
		if (rayPos < _max && rayPos > _min)
		{
			// Hit values of ray set
			_rayHit.m_position = rayPos;
			_rayHit.m_point = _ray->GetRayPoint(_rayHit.m_position);
			_rayHit.m_normal = (_rayHit.m_point - m_centre) / m_radius;
			
			// Returns true after intersection to object
			return true;
		}

		// Use of the second solution of the quadratic for the rays position
		rayPos = (-b + glm::sqrt(b * b - a * c)) / a;

		// Checking if the ray poistion is within the bounds
		if (rayPos < _max && rayPos > _min)
		{
			// Hit values of ray set
			_rayHit.m_position = rayPos;
			_rayHit.m_point = _ray->GetRayPoint(_rayHit.m_position);
			_rayHit.m_normal = (_rayHit.m_point - m_centre) / m_radius;

			// Returns true after intersection to sphere
			return true;
		}
	}

	// Returns false if no intersection is made
	return false;
}

glm::vec3 Object::RandomNumInObj()
{
	glm::vec3 point = { 0.0f, 0.0f, 0.0f };

	do
	{
		point = 2.0f * glm::vec3(RandomNumber(), RandomNumber(), RandomNumber()) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (point.x * point.x + point.y * point.y + point.z * point.z >= 1.0f);
	return point;
}

glm::vec3 Object::Colour(std::shared_ptr<Ray> _ray, RayHitAble* _world)
{
	// creates the hit point from ray
	RayHit rayHit;

	// Check in the table for any ray hits to any objects
	if (_world->Hit(_ray, 0.001f, std::numeric_limits<float>::max(), rayHit))
	{
		glm::vec3 target = rayHit.m_point + rayHit.m_normal + RandomNumInObj();

		std::shared_ptr<Ray> m_ray = std::make_shared<Ray>(rayHit.m_point, target - rayHit.m_point);

		return 0.5f * Colour(m_ray, _world);
	}
	else
	{
		glm::vec3 unitDirection = glm::normalize(_ray->GetDirection());

		float t = 0.5f * (unitDirection.y + 1.0f);

		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}
}

float Object::RandomNumber()
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	if (r == 1.0f)
	{
		RandomNumber();
	}

	return r;
}
