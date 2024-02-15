#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

namespace CliqueEngine
{

    #define REGISTER(class, type, var) Engine::Instance().world.component<class>().member<type>(#var)


    struct Behaviour
    {

    public:

        Behaviour() = default;
        ~Behaviour() = default;

        virtual void Register() const {}
        
        virtual void Update()
        {
            std::cout << "I am Behaviour struct" << std::endl;
        }
    };
}

#endif // BEHAVIOUR_H