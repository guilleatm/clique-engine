#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "flecs.h"
#include "entity.h"

namespace CliqueEngine
{
    // struct Entity;

    struct Component
    {

    public:
        Component();
        ~Component() = default;

        // Entity entity;

    private:

        flecs::entity m_flecs_component;
    
        void Prepare(flecs::entity flecs_component);

        friend Entity;
    };
}

#endif // COMPONENT_H