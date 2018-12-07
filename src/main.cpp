#include <SDL2/SDL.h>
#include <glm.h>

#include <iostream>
#include <memory>

#include "Window.h"


int main(int argc, char* args[])
{

	SDL_Event event;

	std::shared_ptr<Window> window = std::make_shared<Window>();






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