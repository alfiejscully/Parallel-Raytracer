// Class header include
#include "Renderer.h"
#include "Window.h"
#include "Ray.h"
#include "Camera.h"

Renderer::Renderer(std::shared_ptr<Window> _window)
{
	// Eenderer is created
	m_renderer = SDL_CreateRenderer(_window->GetWindow(), -1, SDL_RENDERER_ACCELERATED);

	// Window is equal to the value passed in
	m_window = _window;
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
	for (int j = m_height - 1; j >= 0; j--)
	{
		for (size_t i = 0; i < m_width; i++)
		{
			float u = float(i) / float(m_width);
			float v = float(j) / float(m_height);
			//gradient for position

			Ray r(m_camera->GetOrigin(), m_camera->GetBottomLeftCorner() + (u * m_camera->GetHorizontal()) + (v * m_camera->GetVertical()));

			glm::vec3 pixelColour = Colour(r);

			int red = int(255.99 * pixelColour[0]);
			int green = int(255.99 * pixelColour[1]);
			int blue = int(255.99 * pixelColour[2]);

			m_pixels[i][j] = { red, green, blue };
			DrawColour({ m_pixels[i][j].r, m_pixels[i][j].g, m_pixels[i][j].b, 255 });
			DrawPoint({ i, j });


		}
	}



	
	
	//for (int y = 0; y < m_height; y++)
	//{
	//	for (int x = 0; x < m_width; x++)
	//	{
	//		m_pixels[x][y] = { 0.0f, 0.0f, 255.0f };
	//		DrawColour({ m_pixels[x][y].r, m_pixels[x][y].g, m_pixels[x][y].b, 255 });
	//		DrawPoint({ x, y });
	//	}
	//}
}

glm::vec3 Renderer::Colour(Ray _ray)
{
	glm::vec3 rayDirection = glm::normalize(_ray.GetDirection());
	float t = 0.5f * (rayDirection.y + 1.0f);
	return (1.0f - t) * glm::vec3{ 1.0f, 1.0f, 1.0f } + (t * glm::vec3{ 0.5f, 0.7f, 1.0f });
}
