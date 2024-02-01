#pragma once

#ifndef EDITOR_H
#define EDITOR_H


#include <SDL.h>
#include <SDL_image.h>

#include "Engine/engine.h"
#include "engine_settings.h"

#include "ui_manager.h"

class Editor
{

public:
    Editor();
    ~Editor();

    // This is a NonCopiableClass
    Editor(const Editor&);
    Editor& operator=(const Editor&);

    void Start();

private:

    Engine m_engine;

    SDL_Window* m_window_ptr;
    SDL_Renderer* m_renderer_ptr;

    int InitSDL();
};

#endif // EDITOR_H