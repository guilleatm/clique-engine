#include "editor.h"

const float K_TARGET_DELTA_TIME = 1000.0f / K_EDITOR_TARGET_FRAMERATE;


Editor::Editor()
{
	if (InitSDL() < 0)
	{
		throw;
	}
}

Editor::~Editor()
{
    SDL_DestroyRenderer(m_renderer_ptr);
	SDL_DestroyWindow(m_window_ptr);
	SDL_Quit();
}


void Editor::Start()
{
    UIManager ui_manager = UIManager(m_window_ptr, m_renderer_ptr);

	bool run = true;

	uint32_t last_frame_ticks;

	while (run)
	{
		uint32_t this_frame_ticks = SDL_GetTicks();
		float delta_time = this_frame_ticks - last_frame_ticks;
		last_frame_ticks = this_frame_ticks;

		if (delta_time < K_EDITOR_TARGET_FRAMERATE)
		{
			SDL_Delay(K_EDITOR_TARGET_FRAMERATE - delta_time);
			delta_time = K_EDITOR_TARGET_FRAMERATE;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ui_manager.ManageEvent(&event);

			if (event.type == SDL_QUIT)
			{
				run = false;
			}
		}

		SDL_SetRenderDrawColor(m_renderer_ptr, 120, 180, 255, 255);
		SDL_RenderClear(m_renderer_ptr);

		ui_manager.Render();

		SDL_RenderPresent(m_renderer_ptr);
	}
}


int Editor::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return -1;
	}

	uint32_t flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_SHOWN;
	m_window_ptr = SDL_CreateWindow
	(
		"Clique Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600,400,
		flags
	);

	if (!m_window_ptr)
	{
		SDL_Quit();
		return -1;
	}

	m_renderer_ptr = SDL_CreateRenderer(m_window_ptr, -1, 0);

	if (!m_renderer_ptr)
	{
		SDL_DestroyWindow(m_window_ptr);
		SDL_Quit();
		return -1;
	}

	return 0;
}