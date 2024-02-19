#include "component.h"

#include <iostream> //DELETE

namespace CliqueEngine
{
    Component::Component()
    {
    }

    void Component::Prepare(flecs::entity flecs_component)
    {
        m_flecs_component = flecs_component;

        bool r = m_flecs_component.has_relation(flecs::Entity);

        std::cout << r << std::endl;
    }
}