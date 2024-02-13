#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#define EDITOR 1

#include <iostream>
#include <string>

#include "engine_settings.h"

#include <SDL.h>
#include <SDL_image.h>
#include "flecs.h"

#include "render_manager.h"

#include "entity.h"
#include "component.h"

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

        Entity CreateEntity(std::string name = std::string());

        flecs::world world;

    private:


        RenderManager* m_render_manager_ptr;
        bool m_render_manager_owner;

        bool m_run;

        flecs::system update;
        flecs::system render;

        flecs::rule<Behaviour> update_rule;    
    };

    static Engine my_engine;

}


#endif // ENGINE_H