#pragma once

#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

namespace CliqueEngine
{
    class RenderManager
    {

    public:

        RenderManager();
        ~RenderManager();

        SDL_Renderer* renderer_ptr;
        SDL_Window* window_ptr;

    private:

        int InitSDL();
    };
}

#endif // RENDER_MANAGER_H