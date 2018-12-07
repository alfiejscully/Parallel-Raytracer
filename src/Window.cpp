// Class header include
#include "Window.h"

// System include
#include <iostream>

//// Screen dimension constants
//const int WINDOW_WIDTH = 640;
//const int WINDOW_HEIGHT = 480;

Window::Window()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create window
		m_window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 200, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}

		/*m_width = WINDOW_WIDTH;
		m_height = WINDOW_HEIGHT;*/
	}

}

Window::~Window()
{
	// Destorys window
	SDL_DestroyWindow(GetWindow());
}

