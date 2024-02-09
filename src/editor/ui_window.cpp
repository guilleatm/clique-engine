#include "ui_window.h"

namespace CliqueEngine
{    
    UIWindow::UIWindow(UIManager* ui_manager_ptr, const char* window_name)
    {
        m_is_open = true;
        m_window_name = window_name;
        m_ui_manager = ui_manager_ptr;
    }
}
