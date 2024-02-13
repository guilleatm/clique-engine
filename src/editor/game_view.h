#pragma once

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "editor.h"

namespace CliqueEngine
{

    enum GameViewState
    {
        Stop,
        Pause,
        Play
    };

    class GameView : public UIWindow
    {

    public:
        GameView(UIManager* ui_manager_ptr);
        ~GameView();

        void Prepare(SDL_Renderer* renderer_ptr);

        void Render() override;

        
    private:

        SDL_Texture* m_texture_ptr;
        Engine* m_engine;

        GameViewState m_state;

    };
}

#endif // GAME_VIEW_H