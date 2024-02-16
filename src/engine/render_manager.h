#pragma once

#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "flecs.h"

struct SDL_Renderer;
struct SDL_Window;

namespace CliqueEngine
{
    class RenderManager
    {

    public:

        RenderManager( const flecs::system& render_system );
        ~RenderManager();

        SDL_Renderer* renderer_ptr;
        SDL_Window* window_ptr;

        void Render();

    private:

        const flecs::system& m_render_system;

        int InitSDL();
    };
}

#endif // RENDER_MANAGER_H