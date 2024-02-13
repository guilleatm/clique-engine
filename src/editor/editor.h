#pragma once

#ifndef EDITOR_H
#define EDITOR_H


#include "../engine/engine.h"

#include "editor_settings.h"
#include "error_macros.h"

#include "ui_manager.h"


namespace CliqueEngine
{
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
        // Editor(const Editor&) = delete;
        // Editor& operator=(const Editor&) = delete;

        int64_t inspected_entity_id = -1;

    private:

        Editor();
        ~Editor();

        RenderManager m_render_manager;

        // SDL
        // SDL_Window* m_window_ptr;
        // SDL_Renderer* m_renderer_ptr;

        // int InitSDL();
    };
}

#endif // EDITOR_H