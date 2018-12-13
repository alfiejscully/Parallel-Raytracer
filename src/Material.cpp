#include "Material.h"
#include "RayHitAble.h"
#include "Ray.h"
#include "Randomizer.h"


bool Lambertain::Scatter(std::shared_ptr<Ray> _ray, const RayHit & _rayHit, glm::vec3 _attenuation, std::shared_ptr<Ray> _scattered) const
{
	glm::vec3 target = _rayHit.m_point + _rayHit.m_normal + RandomNumInObj();
	_scattered = std::make_shared<Ray>(_rayHit.m_point, target - _rayHit.m_point);
	_attenuation = m_albedo;
	return true;
}

bool Metal::Scatter(std::shared_ptr<Ray> _ray, const RayHit & _rayHit, glm::vec3 _attenuation, std::shared_ptr<Ray> _scattered) const
{
	glm::vec3 reflected = Reflect(glm::normalize(_ray->GetDirection()), _rayHit.m_normal);
	_scattered = std::make_shared<Ray>(_rayHit.m_point, reflected);
	_attenuation = m_albedo;
	return(glm::dot(_scattered->GetDirection(), _rayHit.m_normal) > 0);
}












glm::vec3 Reflect(glm::vec3 _v, glm::vec3 _n)
{
	return _v - 2 * glm::dot(_v, _n) * _n;
}

glm::vec3 RandomNumInObj()
{
	glm::vec3 point = { 0.0f, 0.0f, 0.0f };

	Randomizer rand;

	do
	{
		point = 2.0f * glm::vec3(rand.RandomNumber(), rand.RandomNumber(), rand.RandomNumber()) - glm::vec3(1.0f, 1.0f, 1.0f);
	} while (point.x * point.x + point.y * point.y + point.z * point.z >= 1.0f);
	return point;
}

