#include "engine.h"

Engine::Engine()
{
    m_world = flecs::world();
}

Entity Engine::CreateEntity()
{
    flecs::entity flecs_entity = m_world.entity();
    return Entity(this, flecs_entity);
}

void Engine::Update()
{

}

void Engine::Render()
{

}