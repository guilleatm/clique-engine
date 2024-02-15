#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

// #include <SDL.h>
// #include <SDL_image.h>
#include "flecs.h"

#include "engine_settings.h"

#include "render_manager.h"

#include "entity.h"

#include "transform.h"
#include "sprite.h"
#include "behaviour.h"


namespace CliqueEngine
{

    class Behaviour;

    class Engine
    {

    public:

        static Engine& Instance()
        {
            static Engine instance;
            return instance;
        }

        
        void Prepare();
        void Start();

        void Update();
        void Render();

        Entity CreateEntity(std::string name = std::string());

        flecs::world world;
        RenderManager render_manager;

    private:

        Engine();
        ~Engine();

        bool m_run;

        flecs::system update;
        flecs::system render;

        flecs::rule<Behaviour> update_rule;
    };
}


#endif // ENGINE_H