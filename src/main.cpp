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

	SDL_Event event;

	std::shared_ptr<Window> window = std::make_shared<Window>(400, 200);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(window, camera);

	renderer->ClearRenderer();

	renderer->Draw();

	renderer->PresentRenderer();
	

	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}
	}

	SDL_Quit();

	return 0;
}