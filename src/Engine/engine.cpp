#include "engine.h"

Engine::Engine()
{
    m_world = flecs::world();
}

Entity Engine::CreateEntity()
{
    flecs::entity flecs_entity = m_world.entity();
    std::string name = "entity " + std::to_string(flecs_entity.id());
    flecs_entity.set_name(name.c_str());
    flecs_entity.add<Transform>();
    return Entity(this, flecs_entity);
}

void Engine::Update()
{
    std::cout << "Engine Update" << std::endl;
}

void Engine::Render()
{
    std::cout << "Engine Render" << std::endl;
}