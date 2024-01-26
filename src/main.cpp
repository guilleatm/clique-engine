#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

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

	SDL_Texture* texture_ptr = SDL_CreateTexture(
		renderer_ptr,
		SDL_PIXELFORMAT_BGRA8888,
		SDL_TEXTUREACCESS_TARGET,
		100,
		100
	);

	int img_init_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(img_init_flags)) & img_init_flags)
	{
		return -1;
	}

	SDL_Surface* surface_ptr = IMG_Load("frog_square.png");
	SDL_Texture* player_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, surface_ptr);
	
	// std::cout << surface_ptr << std::endl;
	
	SDL_FreeSurface(surface_ptr);


	// std::cout << texture_ptr << std::endl;
	// std::cout << window_ptr << std::endl;

	SDL_SetRenderTarget(renderer_ptr, texture_ptr);
	SDL_SetRenderDrawColor(renderer_ptr, 255, 0, 0, 255);
	SDL_RenderClear(renderer_ptr);

	SDL_Rect rect { 0, 0, 10, 10 };
	SDL_RenderCopy(renderer_ptr, player_texture_ptr, NULL, &rect);

	SDL_SetRenderTarget(renderer_ptr, NULL);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void) io;

	ImGui_ImplSDL2_InitForSDLRenderer(window_ptr, renderer_ptr);
	ImGui_ImplSDLRenderer2_Init(renderer_ptr);


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

			ImGui_ImplSDL2_ProcessEvent(&event);
		}

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window_ptr);
		ImGui::NewFrame();

		ImGui::Begin("Test");
		ImGui::Text("Hi, I am text ...");
		ImGui::End();

		ImGui::Begin("Image");
		ImGui::Image( texture_ptr, ImVec2(100, 100));
		ImGui::End();

		ImGui::Render();

		SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255);
		SDL_RenderClear(renderer_ptr);


		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer_ptr);
		
	}

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyTexture(texture_ptr);

	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	SDL_Quit();

	return 0;
}