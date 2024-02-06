#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

#include "engine_settings.h"

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

    flecs::world world;

private:

    bool m_run;

    flecs::system update;

};

#endif // ENGINE_H