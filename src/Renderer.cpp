// Class header include
#include "Renderer.h"
#include "Window.h"
#include "Ray.h"
#include "Camera.h"
#include "Object.h"
#include "RayHitList.h"
#include "RayHitTable.h"

Renderer::Renderer(std::shared_ptr<Window> _window, std::shared_ptr<Camera> _camera)
{
	// Renderer is created
	m_renderer = SDL_CreateRenderer(_window->GetWindow(), -1, SDL_RENDERER_ACCELERATED);
	// Window is equal to the value passed in
	m_window = _window;

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

void Renderer::Draw()
{
	int check = 100;

	srand(time(NULL));

	RayHitTable* list[2];

	list[0] = new Object(glm::vec3(0, 0, -1), 0.5f);
	list[1] = new Object(glm::vec3(0, -100.5, -1), 100.0f);

	RayHitTable* world = new RayHitList(list, 2);

	m_areaCount = { 16, 16 };
	m_areaSize = { m_width / m_areaCount.x, m_height / m_areaCount.y };

	for (unsigned int y = 0; y < m_areaCount.y; y++)
	{
		for (unsigned int x = 0; x < m_areaCount.x; x++)
		{
			Area area;

			area.m_min.x = x * m_areaSize.x;
			area.m_min.y = y * m_areaSize.y;

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

float Renderer::RandomNumber()
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	if (r == 1.0f)
	{
		RandomNumber();
	}

	return r;
}

void Renderer::HandleAreas(Area _area, RayHitTable* _world)
{
	for (int y = _area.m_min.y; y < _area.m_max.y; y++)
	{
		for (int x = _area.m_min.x; x < _area.m_max.x; x++)
		{
			glm::vec3 pixelColour = { 0.0f, 0.0f, 0.0f };

			for (int antialias = 0; antialias < check; antialias++)
			{
				//float u and v help with Antialiasing
				float u = float(x + RandomNumber()) / float(m_width);
				float v = float(y + RandomNumber()) / float(m_height);

				std::shared_ptr<Ray> ray = std::make_shared<Ray>(m_camera->GetOrigin(), m_camera->GetBottomLeftCorner() + (u * m_camera->GetHorizontal()) + (v * m_camera->GetVertical()));

				glm::vec3 p = ray->GetRayPoint(2.0f);
				pixelColour += m_object->Colour(ray, _world);

			}


			pixelColour /= float(check);
			pixelColour = glm::vec3(glm::sqrt(pixelColour[0]), glm::sqrt(pixelColour[1]), glm::sqrt(pixelColour[2]));
			
			int red = int(255.99 * pixelColour[0]);
			int green = int(255.99 * pixelColour[1]);
			int blue = int(255.99 * pixelColour[2]);

			m_pixels[x][y] = { red, green, blue };

		}
	}
}
