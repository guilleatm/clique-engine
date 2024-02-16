#pragma once

#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

struct SDL_Renderer;
struct SDL_Window;

namespace CliqueEngine
{
    class RenderManager
    {

    public:

        RenderManager();
        ~RenderManager();

        SDL_Renderer* renderer_ptr;
        SDL_Window* window_ptr;

        void Render();

    private:

        int InitSDL();
    };
}

#endif // RENDER_MANAGER_H