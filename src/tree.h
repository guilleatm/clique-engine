#pragma once

#ifndef TREE_H
#define TREE_H

#include "editor.h"
#include "Engine/engine.h"
#include "ui_manager.h"
#include "ui_window.h"
#include "console.h"

#include "flecs.h"

#include "Engine/transform.h"

class Tree : public UIWindow
{

public:
    
    Tree(UIManager* ui_manager_ptr);
    void Render() override;

    void Render(flecs::entity entity);

    void DragDropSource(const int& id);
    void DragDropTarget(int id);

private:

    Engine* m_engine;
    int m_node_selected = -1;


    ~Tree();

};

#endif // TREE_H