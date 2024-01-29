#pragma once

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

class UIManager;

class UIWindow
{
public:
    UIWindow(const char* window_name);
    virtual void Render() = 0;

protected:
    const char* m_window_name;
    bool m_is_open;


    friend class UIManager;
};

#endif // UI_WINDOW_H