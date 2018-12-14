#include "Material.h"
#include "RayHitAble.h"
#include "Ray.h"
#include "Randomizer.h"


bool Lambertain::Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3& _attenuation, std::shared_ptr<Ray> _scattered) const
{
	glm::vec3 target = _rayHit.m_point + _rayHit.m_normal + RandomNumInObj();
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(_rayHit.m_point, target - _rayHit.m_point);
	_scattered = ray;
	_attenuation = m_albedo;
	return true;
}

Metal::Metal(const glm::vec3 _a, float _fuzz)
{
	m_albedo = _a;
	m_fuzz = _fuzz;

	if (_fuzz < 1)
	{
		m_fuzz = _fuzz;
	}
	else
	{
		m_fuzz = 1;
	}
}

bool Metal::Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3& _attenuation, std::shared_ptr<Ray> _scattered) const
{
	glm::vec3 reflected = Reflect(glm::normalize(_ray->GetDirection()), _rayHit.m_normal);
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(_rayHit.m_point, reflected + m_fuzz * RandomNumInObj());
	_scattered = ray;
	_attenuation = m_albedo;
	return(glm::dot(_scattered->GetDirection(), _rayHit.m_normal) > 0);
}

bool Dielectric::Scatter(std::shared_ptr<Ray> _ray, const RayHit & _rayHit, glm::vec3 & _attenuation, std::shared_ptr<Ray> _scattered) const
{
	Randomizer rand;

	glm::vec3 outwardNormal = { 0.0f, 0.0f, 0.0f };
	glm::vec3 reflected = Reflect(_ray->GetDirection(), _rayHit.m_normal);

	float niOverNt = 0.0f;

	_attenuation = { 1.0f, 1.0f, 1.0f };

	glm::vec3 refracted = { 1.0f, 1.0f, 1.0f };

	float reflectProb;
	float cosine;

	if (glm::dot(_ray->GetDirection(), _rayHit.m_normal) > 0.0f)
	{
		outwardNormal = -_rayHit.m_normal;
		niOverNt = m_refIndex;
		cosine = m_refIndex * glm::dot(_ray->GetDirection(), _rayHit.m_normal) / glm::length(_ray->GetDirection());
	}
	else
	{
		outwardNormal = -_rayHit.m_normal;
		niOverNt = 1.0f / m_refIndex;
		cosine = -glm::dot(_ray->GetDirection(), _rayHit.m_normal) / glm::length(_ray->GetDirection());
	}
	if (Refract(_ray->GetDirection(), outwardNormal, niOverNt, refracted))
	{
		reflectProb = Schlick(cosine, m_refIndex);
	}
	else
	{
		reflectProb = 1.0f;
	}

	std::shared_ptr<Ray> ray = std::make_shared<Ray>(_rayHit.m_point, reflected);
	_scattered = ray;

	if (rand.RandomNumber() < reflectProb)
	{
		_scattered = ray;
	}
	else
	{
		_scattered = ray;
	}
	return true;
}


glm::vec3 Reflect(glm::vec3 _v, glm::vec3 _n)
{
	return _v - 2.0f * glm::dot(_v, _n) * _n;
}

bool Refract(const glm::vec3 & _v, const glm::vec3 _n, float _niOverNt, glm::vec3 & _refracted)
{
	glm::vec3 uv = glm::normalize(_v);
	float dt = glm::dot(uv, _n);
	float discriminant = 1.0f - _niOverNt * _niOverNt * (1 - dt * dt);
	if (discriminant > 0)
	{
		_refracted = _niOverNt * (uv - _n * dt) - _n * glm::sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

float Schlick(float _cosine, float _refIndex)
{
	float r0 = (1 - _refIndex) / (1 + _refIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * glm::pow((1 - _cosine), 5);
}

glm::vec3 RandomNumInObj()
{
	// points set to 0.0f
	glm::vec3 point = { 0.0f, 0.0f, 0.0f };

	// rand created
	Randomizer rand;

	do
	{
		point = 2.0f * glm::vec3(rand.RandomNumber(), rand.RandomNumber(), rand.RandomNumber()) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (point.x * point.x + point.y * point.y + point.z * point.z >= 1.0f);
	return point;
}

