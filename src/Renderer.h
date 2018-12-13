// Libary include
#include <SDL2/SDL.h>
#include <glm/glm.h>

// System includes
#include <memory>
#include <Vector>
#include <time.h>
#include <thread>

class Window;
class Ray;
class Camera;
class Object;
class RayHitList;
class RayHitAble;

struct Area
{
	glm::vec2 m_min;
	glm::vec2 m_max;
};

class Renderer
{
private:
	// SDL renderer pointer variable
	SDL_Renderer* m_renderer = nullptr;
	// Pointer variable of the window class
	std::shared_ptr<Window> m_window;
	// Pointer variable of the camera class
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Object> m_object = std::make_shared<Object>();

	// value for width of the window
	int m_width;
	// value for height of the window
	int m_height;

	glm::vec3 m_pixels[400][200];

	std::vector<std::shared_ptr<std::thread>> m_threads;
	glm::vec2 m_areaCount;
	glm::vec2 m_areaSize;
	std::vector<Area> m_areas;

	int m_red;
	int m_green;
	int m_blue;

	int check = 100;

public:
	Renderer(std::shared_ptr<Window> _window, std::shared_ptr<Camera> _camera);
	~Renderer();

	// Get the rendering window value
	SDL_Renderer* GetRenderer() const;

	// Sets the colour to draw
	void DrawColour(glm::vec4 const _colour);

	// Sets the point to draw at
	void DrawPoint(glm::vec2 _point);

	// Clears renderer
	void ClearRenderer();

	// Presents the renderer 
	void PresentRenderer();

	// Draws the Pixels
	void Draw();

	float RandomNumber();

	void HandleAreas(Area _area, RayHitAble* _world);

	//// Colour function using ray in parameters
	//glm::vec3 Colour(std::shared_ptr<Ray> _ray);

};