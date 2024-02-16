#include "render_manager.h"

#include <SDL.h>
#include <SDL_image.h> // DELETE

namespace CliqueEngine
{

	RenderManager::RenderManager()
	{
		if (InitSDL() < 0)
		{
			throw;
		}
	}

	RenderManager::~RenderManager()
	{
		SDL_DestroyRenderer(renderer_ptr);
		SDL_DestroyWindow(window_ptr);
		SDL_Quit();
	}

	int RenderManager::InitSDL()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return -1;
		}

		uint32_t flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_SHOWN;
		window_ptr = SDL_CreateWindow
		(
			"Clique Engine",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			600,400,
			flags
		);

		if (!window_ptr)
		{
			SDL_Quit();
			return -1;
		}

		renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);

		if (!renderer_ptr)
		{
			SDL_DestroyWindow(window_ptr);
			SDL_Quit();
			return -1;
		}

		return 0;
	}


	void RenderManager::Render()
	{
		SDL_RenderClear(renderer_ptr);

		SDL_Surface* surface_ptr = IMG_Load("build/assets/frog_square.png");
		SDL_Texture* t = SDL_CreateTextureFromSurface(renderer_ptr, surface_ptr);
        SDL_FreeSurface(surface_ptr);

		const SDL_Rect r = SDL_Rect({0, 0, 100, 100});
        SDL_RenderCopy(renderer_ptr, t, NULL, &r);

    }
}