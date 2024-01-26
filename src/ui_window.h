#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "imgui.h"
#include <string>

class UIWindow
{
public:
    UIWindow(const char* window_name);
    void Render();

private:
    const char* m_window_name;
    bool m_is_open;

};

#endif // UI_WINDOW_H