#include "component.h"

namespace CliqueEngine
{
    Component::Component(flecs::entity flecs_entity, flecs::entity flecs_component) :
        m_flecs_entity(flecs_entity),
        m_flecs_component(flecs_component)
    {
        
    }
}