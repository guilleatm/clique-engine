#pragma once

#include "../engine/engine.h"

using namespace CliqueEngine;

struct GameScript : Behaviour
{
public:

    GameScript()
    {
        // SERIALIZE(GameScript, int32_t, m_int);

        // Editor::Instance().engine.world.component<GameScript>().member<int32_t>("m_int");
    }

    ~GameScript() = default;

    int32_t m_int = 27;

    virtual void Register() const override
    {
        RegisterMember<GameScript, int>("m_int");
    }

    virtual void Update() override
    {
        std::cout << "I am Game Script struct" << std::endl;
    }

};