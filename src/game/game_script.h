#pragma once

// #include "../engine/engine.h"

#include "../engine/behaviour.h"

using namespace CliqueEngine;

struct GameScript : public Behaviour
{
public:

    GameScript() = default;
    ~GameScript() = default;

    int bullets = 17;
    bool player_alive = false;
    float speed = 543.6;
    const char* m_char = "aaaaaaa";

    virtual void Register() const override
    {
        REGISTER(GameScript, int, bullets);
        REGISTER(GameScript, float, speed);
        REGISTER(GameScript, bool, player_alive);
        REGISTER(GameScript, const char*, m_char);

    }

    virtual void Update() override
    {
        std::cout << "I am Game Script struct" << std::endl;
    }

};