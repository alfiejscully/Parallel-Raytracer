// System includes
#include <memory>

// Libary includes
// System includes
#include <memory>

// Libary includes
#include <glm/glm.hpp>

class Ray;
struct RayHit;

class Material
{
public:
	virtual bool Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3& _attenuation, std::shared_ptr<Ray> _scattered) const = 0;

};

////////////////////////////////////////////////////////////////////////////////////////

class Lambertain : public Material
{
private:
	glm::vec3 m_albedo;

public:
	Lambertain(const glm::vec3 _a) : m_albedo(_a) {};

	virtual bool Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3& _attenuation, std::shared_ptr<Ray> _scattered) const;
};

////////////////////////////////////////////////////////////////////////////////////////

class Metal : public Material
{
private:
	glm::vec3 m_albedo;
	float m_fuzz;

public:
	Metal(const glm::vec3 _a, float _fuzz);

	virtual bool Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3& _attenuation, std::shared_ptr<Ray> _scattered) const;
};

////////////////////////////////////////////////////////////////////////////////////////

class Dielectric : public Material
{
private:
	float m_refIndex;

public:
	Dielectric(float _ri) : m_refIndex(_ri) {};

	virtual bool Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3& _attenuation, std::shared_ptr<Ray> _scattered) const;
};

////////////////////////////////////////////////////////////////////////////////////////

glm::vec3 Reflect(glm::vec3 _v, glm::vec3 _n);

bool Refract(const glm::vec3& _v, const glm::vec3 _n, float _niOverNt, glm::vec3& _refracted);

float Schlick(float _cosine, float _refIndex);

glm::vec3 RandomNumInObj();