#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <flecs.h>
#include "entity.h"

class Engine
{

public:
    Engine();
    ~Engine() = default;

    void Update();
    void Render();

    Entity CreateEntity();

private:

    bool m_run;
    flecs::world m_world;

};

#endif // ENGINE_H