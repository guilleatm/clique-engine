#include "engine.h"

namespace CliqueEngine
{
    Engine::Engine()
    {
        // Creates RenderManager
        // Creates flecs::world
    }

    Engine::~Engine()
    {
    }

    void Engine::Prepare()
    {
        // render_manager = RenderManager();

        // m_render_manager_owner = render_manager_ptr_or_nullptr == nullptr;
        // if (m_render_manager_owner)
        // {
        //     render_manager_ptr = new RenderManager();
        // }
        // else
        // {
        //     render_manager_ptr = render_manager_ptr_or_nullptr;
        // }


        // update_rule = world.rule<Behaviour>();

        // update_rule.each([](flecs::entity e, Behaviour)
        // {
        //     std::cout << "Unit " << e.name() << " found\n" << std::endl;
        // });


        update = world.system<Behaviour>()
        .kind(flecs::OnUpdate)
        .each([](flecs::entity entity, Behaviour& behaviour)
        {
            behaviour.Update();
        });

        render = world.system<Sprite>()
        .kind(flecs::PostUpdate)
        .each([](flecs::entity entity, const Sprite& sprite)
        {
            sprite.Render();
        });
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
        // my loop
    }

    void Engine::Update()
    {
        update.run();
    }

    void Engine::Render()
    {
        render.run();
    }
}