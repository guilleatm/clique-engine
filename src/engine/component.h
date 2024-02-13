#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H


namespace CliqueEngine
{

    struct Component
    {

    public:

        template<typename Class, typename Type>
        void RegisterMember(std::string name) const
        {
            // CliqueEngine::engine->world.component<Class>().member<Type>(name);    
        }

    private:

    };
}

#endif // ENTITY_H