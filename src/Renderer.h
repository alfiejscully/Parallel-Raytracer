// Libary include
#include <SDL2/SDL.h>
#include <glm/glm.h>

// System includes
#include <memory>
#include <Vector>

class Camera;
class Window;
class Ray;

class Renderer
{
private:
	// SDL renderer pointer variable
	SDL_Renderer* m_renderer = nullptr;

	// Pointer variable of the window class
	std::shared_ptr<Window> m_window;

	// value for width of the window
	int m_width;
	// value for height of the window
	int m_height;

	std::shared_ptr<Camera> m_camera = std::make_shared<Camera>();

	glm::vec3 m_pixels[800][600];

public:
	Renderer(std::shared_ptr<Window> _window);
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

	glm::vec3 Colour(Ray _ray);

};