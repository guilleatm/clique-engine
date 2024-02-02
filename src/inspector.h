#pragma once

#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "editor.h"
#include "Engine/engine.h"
#include "ui_manager.h"
#include "ui_window.h"
#include "console.h"

#include "flecs.h"

class Inspector : public UIWindow
{

public:
    
    Inspector(UIManager* ui_manager_ptr);
    void Render() override;

    void Render(flecs::entity entity);

private:

    Engine* m_engine;

    ~Inspector() = default;

};

#endif // INSPECTOR_H