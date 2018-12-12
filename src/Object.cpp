#include "Object.h"
#include "Ray.h"

Object::Object(glm::vec3 _centre, float _radius)
{
	m_centre = _centre;
	m_radius = _radius;
}

bool Object::Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit & _rayHit) const
{
	glm::vec3 objectCentre = _ray->GetOrigin() - m_centre;

	float a = glm::dot(_ray->GetDirection(), _ray->GetDirection());
	float b = glm::dot(objectCentre, _ray->GetDirection());
	float c = glm::dot(objectCentre, objectCentre) - m_radius * m_radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float rayPos = (-b - glm::sqrt(b * b - a * c)) / a;

		if (rayPos < _max && rayPos > _min)
		{
			_rayHit.m_position = rayPos;
			_rayHit.m_point = _ray->GetRayPoint(_rayHit.m_position);
			_rayHit.m_normal = (_rayHit.m_point - m_centre) / m_radius;
			return true;
		}

		rayPos = (-b + glm::sqrt(b * b - a * c)) / a;

		if (rayPos < _max && rayPos > _min)
		{
			_rayHit.m_position = rayPos;
			_rayHit.m_point = _ray->GetRayPoint(_rayHit.m_position);
			_rayHit.m_normal = (_rayHit.m_point - m_centre) / m_radius;
			return true;
		}
	}

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

glm::vec3 Object::Colour(std::shared_ptr<Ray> _ray, RayHitTable* _world)
{
	RayHit rayHit;

	if (_world->Hit(_ray, 0.001f, std::numeric_limits<float>::max(), rayHit))
	{
		glm::vec3 target = rayHit.m_point + rayHit.m_normal + RandomNumInObj();

		m_ray = std::make_shared<Ray>(rayHit.m_point, target - rayHit.m_point);

		return 0.5f * Colour(m_ray, _world);
	}
	else
	{
		glm::vec3 unit_direction = glm::normalize(_ray->GetDirection());

		float t = 0.5f * (unit_direction.y + 1.0f);

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
