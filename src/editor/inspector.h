#pragma once

#ifndef INSPECTOR_H
#define INSPECTOR_H

// // #include "engine/engine.h"
// #include "ui_manager.h"
// #include "console.h"

#include "ui_window.h"

#include "flecs.h"

struct ImGuiInputTextCallbackData;

namespace CliqueEngine
{
    class Engine;

    class Inspector : public UIWindow
    {

    public:
        
        Inspector(UIManager* ui_manager_ptr);
        virtual void Render() override;

        void RenderEntity(flecs::entity entity);
        void RenderComponent(flecs::entity entity, flecs::entity component);

    private:

        Engine* m_engine_ptr;

        ~Inspector() = default;

        static int Callback(ImGuiInputTextCallbackData* data);


    };

}
#endif // INSPECTOR_H