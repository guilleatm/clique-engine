#include "engine.h"

namespace CliqueEngine
{
    Engine::Engine() : render_manager(m_render_system)
    {
        // Creates flecs::world

        // update_rule = world.rule<Behaviour>();

        // update_rule.each([](flecs::entity e, Behaviour)
        // {
        //     std::cout << "Unit " << e.name() << " found\n" << std::endl;
        // });
    }

    Engine::~Engine()
    {
    }

    Entity Engine::CreateEntity(std::string name)
    {
        flecs::entity flecs_entity = world.entity();

        if (name == std::string())
        {
            name = "entity " + std::to_string(flecs_entity.id());
        }

        flecs_entity.set_name(name.c_str());
        // flecs_entity.add<Transform>();
        return Entity(flecs_entity);
    }


    void Engine::Start()
    {
        // engine loop
    }

    void Engine::Update()
    {
        m_update_system.run();
    }

    void Engine::Render()
    {
        render_manager.Render();
    }
}