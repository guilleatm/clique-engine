#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "engine.h"

struct Behaviour
{

public:

    virtual void Update() const
    {
        std::cout << "updating beha" << std::endl;
    }
    
private:

};

#endif // BEHAVIOUR_H