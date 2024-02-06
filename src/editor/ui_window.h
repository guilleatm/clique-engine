#pragma once

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

class UIManager;

class UIWindow
{
public:
    UIWindow(UIManager* ui_manager, const char* window_name);
    virtual void Render() = 0;

protected:
    const char* m_window_name;
    bool m_is_open;

    UIManager* m_ui_manager;

    friend class UIManager;
};

#endif // UI_WINDOW_H