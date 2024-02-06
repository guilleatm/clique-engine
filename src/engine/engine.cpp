#include "engine.h"
#include "../game/game_script.h" //DELETE

Engine::Engine()
{
    world = flecs::world();


    update = world.system<GameScript>()
    .each([](flecs::entity entity, const GameScript& gameScript)
    {
        std::cout << entity.name() << " update" << std::endl;
    });

}

Entity Engine::CreateEntity()
{
    flecs::entity flecs_entity = world.entity();
    std::string entity_name = "entity " + std::to_string(flecs_entity.id());
    flecs_entity.set_name(entity_name.c_str());
    flecs_entity.add<Transform>();
    return Entity(flecs_entity);
}

void Engine::Update()
{
    update.run();
    // std::cout << "Engine Update" << std::endl;
}

void Engine::Render()
{
    // std::cout << "Engine Render" << std::endl;
}