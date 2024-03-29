#include "editor.h"

#include "SDL.h"
#include "editor_render_manager.h"

namespace CliqueEngine
{
	const float K_TARGET_EDITOR_DELTA_TIME = 1000.0f / K_EDITOR_TARGET_FRAMERATE;

	Editor::Editor() : m_editor_render_manager(&Engine::Instance().render_manager)
	{

	}

	Editor::~Editor()
	{
	}

	void Editor::Start()
	{
		// TO CONSTUCTOR
		UIManager ui_manager = UIManager(m_editor_render_manager.window_ptr, m_editor_render_manager.renderer_ptr);

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

			m_editor_render_manager.Render(ui_manager);
		}
	}

}