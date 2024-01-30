#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <flecs.h>

class Engine;

class Entity
{

public:
    Entity(Engine* engine_ptr, flecs::entity_t flecs_entity);
    ~Entity();

    // template <typename T>
    // void AddComponent()
    // {
    //     m_flecs_entity.add<T>();
    // }

private:

    flecs::entity m_flecs_entity;
    Engine* m_engine_ptr;


};

#endif // ENTITY_H