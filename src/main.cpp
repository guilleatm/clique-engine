#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Program running" << std::endl;

	
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

	// IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	// ImGuiIO& io = ImGui::GetIO(); (void) io;

	// ImGui_ImplSDL2_InitForSDLRenderer(window_ptr, renderer_ptr);
	// ImGui_ImplSDLRenderer2_Init(renderer_ptr);


	bool run = true;

	while (run)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				run = false;
			}
		}

		// ImGui_ImplSDLRenderer2_NewFrame();
		// ImGui_ImplSDL2_NewFrame(window_ptr);
		// ImGui::NewFrame();

		// ImGui::Begin("Test");

		// ImGui::Text("Hi, I am text ...");

		// ImGui::End();

		// ImGui::Render();

		SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255);
		SDL_RenderClear(renderer_ptr);


		// ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer_ptr);
		
	}

	// ImGui_ImplSDLRenderer2_Shutdown();
	// ImGui_ImplSDL2_Shutdown();
	// ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	SDL_Quit();

	return 0;
}