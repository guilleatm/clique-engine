#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <flecs.h>

class Engine;

class Entity
{

public:
    Entity(flecs::entity flecs_entity);
    ~Entity() = default;

    template <typename T>
    void AddComponent()
    {
        m_flecs_entity.add<T>();
    }

private:


    flecs::entity m_flecs_entity;
    // Engine* m_engine_ptr;


};

#endif // ENTITY_H