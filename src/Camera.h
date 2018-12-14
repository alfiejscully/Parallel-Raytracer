// Libary includes
#include <glm/glm.h>

class Camera
{
private:
	glm::vec3 m_origin; // Stores value of the origin
	glm::vec3 m_horizontal; // Stores value of horizontal
	glm::vec3 m_vertical; // Stores value of vertical
	glm::vec3 m_bottomLeftCorner; // Stores value of bottom left corner

public:
	Camera();

	glm::vec3 GetOrigin() const; // Returns the value of start point
	glm::vec3 GetHorizontal() const; // Returns the value of  horizontal
	glm::vec3 GetVertical() const; // Returns the value of vertical
	glm::vec3 GetBottomLeftCorner() const; // Returns the value of bottom left corner

};