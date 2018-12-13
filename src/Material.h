// System includes
#include <memory>

// Libary includes
#include <glm/glm.hpp>

class Ray;
struct RayHit;

class Material
{
public:
	virtual bool Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3 _attenuation, std::shared_ptr<Ray> _scattered) const;

};

class Lambertain : public Material
{
private:
	glm::vec3 m_albedo;

public:
	Lambertain(glm::vec3 _a);

	virtual bool Scatter(std::shared_ptr<Ray> _ray, const RayHit& _rayHit, glm::vec3 _attenuation, std::shared_ptr<Ray> _scattered) const;
};

glm::vec3 RandomNumInObj();

float RandomNumber();