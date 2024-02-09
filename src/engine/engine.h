#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

#include "engine_settings.h"

#include <SDL.h>
#include <SDL_image.h>
#include <flecs.h>

#include "render_manager.h"

#include "entity.h"

#include "transform.h"

#include "sprite.h"
#include "behaviour.h"

namespace CliqueEngine
{

    class Engine
    {

    public:
        Engine();
        ~Engine();

        void Prepare(RenderManager* render_manager_ptr = nullptr);
        void Start();

        void Update();
        void Render();

        Entity CreateEntity();

        flecs::world world;

    private:

        RenderManager* m_render_manager_ptr;
        bool m_render_manager_owner;

        bool m_run;

        flecs::system update;
        flecs::system render;


        // friend Editor;
    };
}

    #endif // ENGINE_H