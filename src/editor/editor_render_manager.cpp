#include "editor_render_manager.h"

#include <SDL.h>
#include "ui_manager.h"
#include "../engine/render_manager.h"

namespace CliqueEngine
{
    EditorRenderManager::EditorRenderManager(RenderManager* render_manager_ptr)
    {
        m_render_manager_ptr = render_manager_ptr;

        window_ptr = render_manager_ptr->window_ptr;
        renderer_ptr = render_manager_ptr->renderer_ptr;

        target_texture_ptr = SDL_CreateTexture(
            renderer_ptr,
            // SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA32,
            SDL_PixelFormatEnum::SDL_PIXELFORMAT_BGRA8888,
            SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET,
            100, 100
        );
    }

    EditorRenderManager::~EditorRenderManager()
    {
        SDL_DestroyTexture(target_texture_ptr);
    }


    void EditorRenderManager::Render(UIManager& ui_manager)
    {
        // SDL_SetRenderDrawColor(renderer_ptr, 120, 180, 255, 255); // ALL FRAMES?
        SDL_RenderClear(renderer_ptr);

        SDL_SetRenderTarget(renderer_ptr, target_texture_ptr);

        m_render_manager_ptr->Render();

        SDL_SetRenderTarget(renderer_ptr, NULL);

        ui_manager.Render();

        SDL_RenderPresent(renderer_ptr);
    }
}