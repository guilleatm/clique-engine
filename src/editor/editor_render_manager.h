#pragma once

#ifndef EDITOR_RENDER_MANAGER_H
#define EDITOR_RENDER_MANAGER_H

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;

namespace CliqueEngine
{
    class RenderManager;

    class EditorRenderManager
    {

    public:

        EditorRenderManager(RenderManager* renderer_manager_ptr);
        ~EditorRenderManager();

        SDL_Renderer* renderer_ptr;
        SDL_Window* window_ptr;

        SDL_Texture* target_texture_ptr;

    private:

        // We dont need to store but just in case
        RenderManager* m_render_manager_ptr;
    };
}

#endif // EDITOR_RENDER_MANAGER_H