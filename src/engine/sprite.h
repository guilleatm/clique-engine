#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include "engine.h"

namespace CliqueEngine
{

    struct Sprite
    {

    public:
        Sprite();
        void Render();
        
    private:

        SDL_Texture* m_texture_ptr;
        ~Sprite() = default;

    };
}

#endif // SPRITE_H