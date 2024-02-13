#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "engine.h"

namespace CliqueEngine
{

    struct Behaviour : public Component
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