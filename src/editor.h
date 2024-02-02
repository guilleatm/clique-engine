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

    static Editor& Instance()
    {
        static Editor instance;
        return instance;
    }

    void Prepare();
    void Start();

    // This is a NonCopiableClass
    Editor(const Editor&) = delete;
    Editor& operator=(const Editor&) = delete;

    Engine engine;
    int64_t inspected_entity_id;

private:

    Editor() = default;
    ~Editor();

    // SDL
    SDL_Window* m_window_ptr;
    SDL_Renderer* m_renderer_ptr;

    int InitSDL();
};

#endif // EDITOR_H