// Class header include
#include "Renderer.h"
#include "Window.h"
#include "Ray.h"
#include "Camera.h"
#include "Object.h"
#include "RayHitList.h"
#include "RayHitAble.h"
#include "Randomizer.h"
#include "Material.h"

Renderer::Renderer(std::shared_ptr<Window> _window, std::shared_ptr<Camera> _camera)
{
	// Renderer is created
	m_renderer = SDL_CreateRenderer(_window->GetWindow(), -1, SDL_RENDERER_ACCELERATED);

	// Value passed into Window
	m_window = _window;

	// Value pass into Camera
	m_camera = _camera;

	// Gets the windows width
	m_width = m_window->GetWidth();

	// Gets the windows height 
	m_height = m_window->GetHeight();

}

Renderer::~Renderer()
{
	// Destorys the renderer m_renderer 
	SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer * Renderer::GetRenderer() const
{
	// Value of renderer returned
	return m_renderer;
}

void Renderer::DrawColour(glm::vec4 const _colour)
{
	// Sets the colour to be rendered
	SDL_SetRenderDrawColor(m_renderer, int(_colour.r), int(_colour.g), int(_colour.b), int(_colour.a));
}

void Renderer::DrawPoint(glm::vec2 _point)
{
	// Renders the draw point
	SDL_RenderDrawPoint(m_renderer, int(_point.x), int(_point.y));
}

void Renderer::ClearRenderer()
{
	// Clears the renderer
	SDL_RenderClear(m_renderer);
}

void Renderer::PresentRenderer()
{
	// Presents the renderer
	SDL_RenderPresent(m_renderer);
}

void Renderer::DrawParallel()
{
	// checks 100 times 
	check = 100;

	// Helps deal with Randomizer
	srand(time(NULL));

	RayHitAble* list[5];

	// Objects in world created 
	list[0] = new Object(glm::vec3(0.0, 0.0, -1.0), 0.5f, new Lambertain(glm::vec3(0.8, 0.3, 0.3)));
	list[1] = new Object(glm::vec3(0.0, -100.5, -1.0f), 100.0f, new Lambertain(glm::vec3(0.8, 0.8, 0.0)));
	list[2] = new Object(glm::vec3(1.0, 0.0, -1.0), 0.5f, new Metal(glm::vec3(0.8, 0.6, 0.2), 0.0f));
	list[3] = new Object(glm::vec3(-1.0, 0.0f, -1.0), -0.5f, new Dielectric(3.5f));
	list[4] = new Object(glm::vec3(-1.0, 0.0f, -1.0), -0.45f, new Dielectric(3.5f));

	RayHitAble* world = new RayHitList(list, 5);

	m_areaCount = { 8, 8 };
	m_areaSize = { m_width / m_areaCount.x, m_height / m_areaCount.y };

	// calculates the amount of areas on the y
	for (unsigned int y = 0; y < m_areaCount.y; y++)
	{
		// calculates the amount of areas on the x
		for (unsigned int x = 0; x < m_areaCount.x; x++)
		{
			Area area;

			// find the min of x and y  
			area.m_min.x = x * m_areaSize.x;
			area.m_min.y = y * m_areaSize.y;

			// find the max of  x and y
			area.m_max.x = (x + 1) * m_areaSize.x;
			area.m_max.y = (y + 1) * m_areaSize.y;

			m_areas.push_back(area);
		}
	}


	for (Area area : m_areas)
	{
		std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(&Renderer::HandleAreas, this, area, world);

		m_threads.push_back(thread);
	}

	for (std::shared_ptr<std::thread> thread : m_threads)
	{
		thread->join();
	}

	for (int j = m_height - 1; j >= 0; j--)
	{
		for (int i = 0; i < m_width; i++)
		{
			DrawColour({ m_pixels[i][j].r, m_pixels[i][j].g, m_pixels[i][j].b, 255 });
			DrawPoint({ i, m_height - j });
		}
	}

}



void Renderer::DrawWithoutParallel()
{
	// checks 100 times 
	check = 100;

	// rand created
	Randomizer rand;

	// Helps deal with Randomizer
	srand(time(NULL));

	// 5 spot created for objects
	RayHitAble* list[5];

	// Objects in world created 
	list[0] = new Object(glm::vec3(0.0, 0.0, -1.0), 0.5f, new Lambertain(glm::vec3(0.8, 0.3, 0.3)));
	list[1] = new Object(glm::vec3(0.0, -100.5, -1.0f), 100.0f, new Lambertain(glm::vec3(0.8, 0.8, 0.0)));
	list[2] = new Object(glm::vec3(1.0, 0.0, -1.0), 0.5f, new Metal(glm::vec3(0.8, 0.6, 0.2), 1.0f /*0.0f*/));
	list[3] = new Object(glm::vec3(-1.0, 0.0f, -1.0), -0.5f, new Dielectric(3.5f));
	list[4] = new Object(glm::vec3(-1.0, 0.0f, -1.0), -0.45f, new Dielectric(3.5f));

	// 5 objects stored into the list and shown in scene
	RayHitAble* world = new RayHitList(list, 5);


	for (int j = m_height - 1; j >= 0; j--)
	{
		for (int i = 0; i < m_width; i++)
		{
			glm::vec3 pixelColour = { 0.0f, 0.0f, 0.0f };


			for (int anit = 0; anit < check; anit++)
			{
				//float u and v help with Antialiasing
				float u = float(i + rand.RandomNumber()) / float(m_width);
				float v = float(j + rand.RandomNumber()) / float(m_height);

				std::shared_ptr<Ray> ray = std::make_shared<Ray>(m_camera->GetOrigin(), m_camera->GetBottomLeftCorner() + (u * m_camera->GetHorizontal()) + (v * m_camera->GetVertical()));

				glm::vec3 p = ray->GetRayPoint(2.0f);
				pixelColour += m_object->Colour(ray, world, 0);

			}


			pixelColour /= float(check);
			pixelColour = glm::vec3(glm::sqrt(pixelColour[0]), glm::sqrt(pixelColour[1]), glm::sqrt(pixelColour[2])); //makes the colouring lighter 
			int red = int(255.99 * pixelColour[0]);
			int green = int(255.99 * pixelColour[1]);
			int blue = int(255.99 * pixelColour[2]);

			m_pixels[i][j] = { red, green, blue };
			DrawColour({ m_pixels[i][j].r, m_pixels[i][j].g, m_pixels[i][j].b, 255 });
			DrawPoint({ i, m_height - j });

		}
	}

}

void Renderer::HandleAreas(Area _area, RayHitAble* _world)
{
	for (int y = _area.m_min.y; y < _area.m_max.y; y++)
	{
		for (int x = _area.m_min.x; x < _area.m_max.x; x++)
		{
			Randomizer rand;

			glm::vec3 pixelColour = { 0.0f, 0.0f, 0.0f };

			for (int anti = 0; anti < check; anti++)
			{
				//float u and v help with Antialiasing
				float u = float(x + rand.RandomNumber()) / float(m_width);
				float v = float(y + rand.RandomNumber()) / float(m_height);

				std::shared_ptr<Ray> ray = std::make_shared<Ray>(m_camera->GetOrigin(), m_camera->GetBottomLeftCorner() + (u * m_camera->GetHorizontal()) + (v * m_camera->GetVertical()));

				// Gets ray point
				glm::vec3 p = ray->GetRayPoint(2.0f);
				// Gets the colour
				pixelColour += m_object->Colour(ray, _world, 0);

			}

			//colour is divided by check
			pixelColour /= float(check);
			// Square roots RGB values
			pixelColour = glm::vec3(glm::sqrt(pixelColour[0]), glm::sqrt(pixelColour[1]), glm::sqrt(pixelColour[2]));

			int red = int(255.99 * pixelColour[0]);
			int green = int(255.99 * pixelColour[1]);
			int blue = int(255.99 * pixelColour[2]);

			m_pixels[x][y] = { red, green, blue };

		}
	}
}
