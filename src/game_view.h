#pragma once

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SDL.h>
#include <SDL_image.h>

#include "imgui.h"
#include "ui_window.h"
#include "error_macros.h"

// #include "Engine/engine.h"


#include "console.h"

class GameView : public UIWindow
{

public:
    GameView();
    ~GameView();

    void Prepare(SDL_Renderer* renderer_ptr);

    void Render() override;

    
private:

    SDL_Texture* m_texture_ptr;
    // Engine* m_engine;


};

#endif // GAME_VIEW_H