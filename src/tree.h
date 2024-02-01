#pragma once

#ifndef TREE_H
#define TREE_H

#include "editor.h"
#include "Engine/engine.h"
#include "ui_manager.h"
#include "ui_window.h"

#include "flecs.h"

#include "Engine/transform.h"

class Tree : public UIWindow
{

public:
    
    Tree(UIManager* ui_manager_ptr);
    void Render() override;


    void Render(int i);
    void Render(flecs::entity entity);

private:

    Engine* m_engine;

    ~Tree();

};

#endif // TREE_H