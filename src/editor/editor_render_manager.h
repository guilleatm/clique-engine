#pragma once

#ifndef EDITOR_RENDER_MANAGER_H
#define EDITOR_RENDER_MANAGER_H

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;

namespace CliqueEngine
{
    class RenderManager;
    class UIManager;

    class EditorRenderManager
    {

    public:

        EditorRenderManager(RenderManager* renderer_manager_ptr);
        ~EditorRenderManager();

        SDL_Renderer* renderer_ptr;
        SDL_Window* window_ptr;

        SDL_Texture* target_texture_ptr;

        void Render(UIManager& ui_manager);

    private:

        RenderManager* m_render_manager_ptr;
    };
}

#endif // EDITOR_RENDER_MANAGER_H