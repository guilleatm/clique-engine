#pragma once

#ifndef TREE_H
#define TREE_H

#include "ui_window.h"

// #include "editor.h"
// #include "ui_manager.h"
// #include "ui_window.h"
// #include "console.h"

#include "flecs.h"


namespace CliqueEngine
{

    class Engine;
    class UIManager;

    class Tree : public UIWindow
    {

    public:
        
        Tree(UIManager* ui_manager_ptr);
        void Render() override;

        void Render(flecs::entity entity);

        void HandleClick(int id);
        void DragDropSource(const int& id);
        void DragDropTarget(int id);


    private:

        Engine* m_engine_ptr;

        ~Tree();

    };
}

#endif // TREE_H