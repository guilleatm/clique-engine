#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "flecs.h"

namespace CliqueEngine
{
    struct Component
    {

    public:
        Component(flecs::entity flecs_entity, flecs::entity flecs_component);
        ~Component() = default;

    private:

        flecs::entity m_flecs_entity;
        flecs::entity m_flecs_component;
    };
}

#endif // COMPONENT_H