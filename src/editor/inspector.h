#pragma once

#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <cstring>

#include "editor.h"

// // #include "engine/engine.h"
// #include "ui_manager.h"
// #include "ui_window.h"
// #include "console.h"

// #include "flecs.h"

class Inspector : public UIWindow
{

public:
    
    Inspector(UIManager* ui_manager_ptr);
    void Render() override;

    void RenderEntity(flecs::entity entity);
    void RenderComponent(flecs::entity component);

private:

    Engine* m_engine;

    ~Inspector() = default;

    static int Callback(ImGuiInputTextCallbackData* data);


};

#endif // INSPECTOR_H