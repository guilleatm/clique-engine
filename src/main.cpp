#include <SDL.h>
#include <SDL_image.h>

#include "engine_settings.h"
#include "ui_manager.h"

#include <iostream>


#include "ui_window.h"

const float K_TARGET_DELTA_TIME = 1000.0f / K_TARGET_FRAMERATE;

int main(int argc, char* argv[])
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return -1;
	}

	SDL_Window* window_ptr = SDL_CreateWindow
	(
		"Clique Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600,400,
		SDL_WINDOW_SHOWN
	);

	if (!window_ptr)
	{
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);

	if (!renderer_ptr)
	{
		SDL_DestroyWindow(window_ptr);
		SDL_Quit();
		return -1;
	}


	// ImGui context
	// IMGUI_CHECKVERSION();
	// ImGui::CreateContext();
	// ImGuiIO& io = ImGui::GetIO(); (void) io;

	// ImGui_ImplSDL2_InitForSDLRenderer(window_ptr, renderer_ptr);
	// ImGui_ImplSDLRenderer2_Init(renderer_ptr);

	UIManager ui_manager = UIManager(window_ptr, renderer_ptr);


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
			if (event.type == SDL_QUIT)
			{
				run = false;
			}

			//ImGui_ImplSDL2_ProcessEvent(&event);
		}

		
		ui_manager.Render(window_ptr);

		SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255);
		SDL_RenderClear(renderer_ptr);


		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer_ptr);
		
	}

	// ImGui_ImplSDLRenderer2_Shutdown();
	// ImGui_ImplSDL2_Shutdown();
	// ImGui::DestroyContext();

	// SDL_DestroyTexture(texture_ptr);

	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	SDL_Quit();

	return 0;
}