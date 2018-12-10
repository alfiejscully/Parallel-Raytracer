// Class header include
#include "Window.h"

// System include
#include <iostream>

Window::Window(int _width, int _height)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create window
		m_window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
	}

	m_width = _width;
	m_height = _height;
}

Window::~Window()
{
	// Destorys window m_window
	SDL_DestroyWindow(m_window);
}

SDL_Window * Window::GetWindow() const
{
	return m_window;
}

int Window::GetWidth() const
{
	return m_width;
}

int Window::GetHeight() const
{
	return m_height;
}

