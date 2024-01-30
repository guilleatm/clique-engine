#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL.h>
#include <flecs.h>
// #include <SDL_image.h>

// #include "imgui.h"
// #include "ui_window.h"
// #include "error_macros.h"

// #include "console.h"


class Sprite
{

public:
    Sprite();
    ~Sprite();

    void Render();
    
private:

    SDL_Texture* m_texture_ptr;


};

#endif // SPRITE_H