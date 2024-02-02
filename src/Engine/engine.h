#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <flecs.h>
#include "entity.h"

#include "transform.h"

class Engine
{

public:
    Engine();
    ~Engine() = default;

    void Update();
    void Render();

    Entity CreateEntity();

    flecs::world m_world;

private:

    bool m_run;

};

#endif // ENGINE_H