// Libary include
#include <SDL2/SDL.h>
#include <glm/glm.h>

// System includes
#include <memory>
#include <Vector>

class Camera;
class Window;
class Ray;
class Camera;
class Object;
class RayHitList;
class RayHitTable;

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

	// Colour function using ray in parameters
	glm::vec3 Colour(std::shared_ptr<Ray> _ray);

};