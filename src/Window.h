// Libary include
#include <SDL2/SDL.h>

class Window
{
private:
	// The window we'll be rendering to
	SDL_Window* m_window = nullptr;

	// The surface contained by the window
	SDL_Surface* m_screenSurface = nullptr;

	// Stores the windows width value
	int m_width;
	// Stores the windows height value
	int m_height;

public:
	Window(int _width, int _height);
	~Window();

	// Get the window value
	SDL_Window* GetWindow() const;

	// Returns width value 
	int GetWidth() const;
	// Returns height value 
	int GetHeight() const;

};