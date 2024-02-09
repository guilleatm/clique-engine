#pragma once

#include "../engine/engine.h"

using namespace CliqueEngine;

struct GameScript : public Behaviour
{
public:

    GameScript() = default;
    ~GameScript() = default;

    virtual void Update()
    {
        std::cout << "update Game script" << std::endl;
    }


private:

};