#include <SDL.h>
#include <SDL_image.h>

#include "engine_settings.h"
#include "ui_manager.h"

#include <iostream>

#include "inspector_ui.h"
#include "console.h"

const float K_TARGET_DELTA_TIME = 1000.0f / K_TARGET_FRAMERATE;


int InitSDL(SDL_Window*& window_ptr, SDL_Renderer*& renderer_ptr)
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

void ShutdownSDL(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr)
{
	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	SDL_Quit();
}


int main(int argc, char* argv[])
{
	SDL_Window* window_ptr;
	SDL_Renderer* renderer_ptr;

	if (InitSDL(window_ptr, renderer_ptr) < 0)
	{
		return -1;
	}

	// SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255);

	

	// SDL_Texture* texture = SDL_CreateTexture(renderer_ptr, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
	// SDL_SetRenderTarget(renderer_ptr, texture);
	// SDL_SetRenderDrawColor(renderer_ptr, 255, 21, 32, 255);


	// SDL_SetRenderTarget(renderer_ptr, NULL);

	UIManager* ui_manager = UIManager::Instance(window_ptr, renderer_ptr);
	InspectorUI* inspector = new InspectorUI();
	Console* console = new Console();

	

	// UIManager ui_manager = UIManager(window_ptr, renderer_ptr);
	// UIManager::instance = ui_manager;

	bool run = true;

	uint32_t last_frame_ticks;

	while (run)
	{
		uint32_t this_frame_ticks = SDL_GetTicks();
		float delta_time = this_frame_ticks - last_frame_ticks;
		last_frame_ticks = this_frame_ticks;

		if (delta_time < K_TARGET_DELTA_TIME)
		{
			SDL_Delay(K_TARGET_DELTA_TIME - delta_time);
			delta_time = K_TARGET_DELTA_TIME;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ui_manager->ManageEvent(&event);

			if (event.type == SDL_QUIT)
			{
				run = false;
			}
		}

		SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255);
		SDL_RenderClear(renderer_ptr);

		ui_manager->Render();

		SDL_RenderPresent(renderer_ptr);
		
	}

	ShutdownSDL(window_ptr, renderer_ptr);

	return 0;
}