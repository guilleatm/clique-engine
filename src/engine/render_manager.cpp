#include "render_manager.h"

#include <SDL.h>
#include "flecs.h"
namespace CliqueEngine
{

	RenderManager::RenderManager(const flecs::system& render_system) : m_render_system(render_system)
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
    
		m_render_system.run();
	}
}