#include "engine.h"

namespace CliqueEngine
{

    Engine::Engine()
    {
    
    }

    Engine::~Engine()
    {
        if (m_render_manager_owner)
        {
            delete m_render_manager_ptr;
        }
    }

    void Engine::Prepare(RenderManager* render_manager_ptr)
    {
        m_render_manager_owner = render_manager_ptr == nullptr;
        if (m_render_manager_owner)
        {
            m_render_manager_ptr = new RenderManager();
        }
        else
        {
            m_render_manager_ptr = render_manager_ptr;
        }

        update = world.system<Behaviour>()
        .kind(flecs::OnUpdate)
        .each([](flecs::entity entity, Behaviour& behaviour)
        {
            behaviour.Update();
        });

        // render = world.system<Sprite>()
        // .kind(flecs::PostUpdate)
        // .each([](flecs::entity entity, const Sprite& sprite)
        // {
        //     // sprite.Render();
        // });
    }

    Entity Engine::CreateEntity()
    {
        flecs::entity flecs_entity = world.entity();
        std::string entity_name = "entity " + std::to_string(flecs_entity.id());
        flecs_entity.set_name(entity_name.c_str());
        flecs_entity.add<Transform>();
        return Entity(flecs_entity);
    }


    void Engine::Start()
    {
        
    }

    void Engine::Update()
    {
        update.run();
    }

    void Engine::Render()
    {
        // render.run();
    }
}