#include "entity.h"

namespace CliqueEngine
{
    Entity::Entity(flecs::entity flecs_entity)
    {
        m_flecs_entity = flecs_entity;
    }
}
