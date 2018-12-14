/// Tutorial used for ray tracer is ray tracing in a weekend by Peter Shirley
/// Author of this code Alfie Scully

// Libaries included
#include <SDL2/SDL.h>
#include <glm.h>

// System includes
#include <iostream>
#include <memory>

// Class header include
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Ray.h"

int main(int argc, char* args[])
{
	// Event Created
	SDL_Event event;

	// Window, camera and renderer created
	std::shared_ptr<Window> window = std::make_shared<Window>(400, 200);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(window, camera);

	// Clears renderer 
	renderer->ClearRenderer();
	
	// Draws parallel
	/*renderer->DrawParallel();*/

	// Draw without parallel
	renderer->DrawWithoutParallel();

	// Presents renderer
	renderer->PresentRenderer();

	// Loops until Esc is pressed
	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}
	}

	// Quit SDL
	SDL_Quit();

	return 0;
}