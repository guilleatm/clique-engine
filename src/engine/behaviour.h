#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "engine.h"


struct Behaviour
{

public:

    Behaviour() = default;
    ~Behaviour() = default;

    virtual void Update()
    {
        std::cout << m_tick++ << std::endl;
    }
    
private:

    int m_tick = 0;

};

#endif // BEHAVIOUR_H