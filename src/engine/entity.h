#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "flecs.h"

// #include "engine.h"

namespace CliqueEngine
{
    struct Component;

    struct Entity
    {

    public:
        Entity(flecs::entity flecs_entity);
        ~Entity() = default;

        template <typename T>
        void AddComponent()
        {
            m_flecs_entity.add<T>();
        }

        template <typename T>
        const T* GetComponent()
        {
            return m_flecs_entity.get<T>();
        }

    private:


        flecs::entity m_flecs_entity;
        // Engine* m_engine_ptr;

    };
}

#endif // ENTITY_H