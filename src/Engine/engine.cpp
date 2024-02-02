#include "engine.h"

Engine::Engine()
{
    world = flecs::world();
}

Entity Engine::CreateEntity()
{
    flecs::entity flecs_entity = world.entity();
    std::string entity_name = "entity " + std::to_string(flecs_entity.id());
    flecs_entity.set_name(entity_name.c_str());
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