#pragma once

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SDL.h>
#include <SDL_image.h>

#include "imgui.h"
#include "ui_window.h"
#include "error_macros.h"

#include "Engine/engine.h"

#include "ui_manager.h"


#include "console.h"


enum GameViewState
{
    Stop,
    Pause,
    Play
};

class GameView : public UIWindow
{

public:
    GameView(UIManager* ui_manager);
    ~GameView();

    void Prepare(SDL_Renderer* renderer_ptr);

    void Render() override;

    
private:

    SDL_Texture* m_texture_ptr;
    Engine* m_engine;

    GameViewState m_state;

};

#endif // GAME_VIEW_H