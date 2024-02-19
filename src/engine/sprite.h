#pragma once

#ifndef SPRITE_H
#define SPRITE_H

// #include <SDL.h>
// #include <SDL_image.h>
// #include "engine.h"
#include "component.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace CliqueEngine
{
    struct Sprite : public Component
    {

    public:
        Sprite();
        ~Sprite();

        void Render();
        
    private:

        SDL_Texture* m_texture_ptr;
        SDL_Renderer* m_renderer_ptr;

    };
}

#endif // SPRITE_H