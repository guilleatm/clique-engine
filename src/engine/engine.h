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

        flecs::system m_update_system = world.system<Behaviour>("update_system")
        .kind(flecs::OnUpdate)
        .each([](flecs::entity entity, Behaviour& behaviour)
        {
            behaviour.Update();
        });

        flecs::system m_render_system = world.system<Sprite>("render_system")
        .kind(flecs::PostUpdate)
        .each([](flecs::entity entity, Sprite& sprite)
        {
            sprite.Render();
        });

        flecs::rule<Behaviour> update_rule;
    };
}


#endif // ENGINE_H