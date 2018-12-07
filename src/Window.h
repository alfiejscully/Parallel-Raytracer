// Libary include
#include <SDL2/SDL.h>

class Window
{
private:
	// The window we'll be rendering to
	SDL_Window* m_window = nullptr;

	// The surface contained by the window
	SDL_Surface* m_screenSurface = nullptr;

	int m_width;
	int m_height;

public:
	Window();
	~Window();

	// Get the window value
	SDL_Window* GetWindow() const { return m_window; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

};