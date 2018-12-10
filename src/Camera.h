// Libary includes
#include <glm/glm.h>

class Camera
{
private:
	glm::vec3 m_origin; // Stores value of the origin
	glm::vec3 m_horizontal;
	glm::vec3 m_vertical;
	glm::vec3 m_bottomLeftCorner;

public:
	Camera();

	glm::vec3 GetOrigin() const;
	glm::vec3 GetHorizontal() const;
	glm::vec3 GetVertical() const;
	glm::vec3 GetBottomLeftCorner() const;

};