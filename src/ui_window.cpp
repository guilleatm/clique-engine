#include "ui_window.h"

UIWindow::UIWindow(const char* window_name)
{
    m_window_name = window_name;

    ERROR_IF(true);
    //ERROR_IF(UIManager::instance == nullptr);

    // UIManager::instance->AddUIWindow(this);
}