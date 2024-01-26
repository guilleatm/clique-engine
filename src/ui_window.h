#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "imgui.h"
#include "ui_manager.h"
#include "error_macros.h"

class UIManager;

class UIWindow
{
public:
    UIWindow(const char* window_name);
    virtual void Render() = 0;

protected:
    const char* m_window_name;
    bool m_is_open;

};

#endif // UI_WINDOW_H