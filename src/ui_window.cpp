#include "ui_window.h"



UIWindow::UIWindow(const char* window_name)
{
    m_window_name = window_name;
}

void UIWindow::Render()
{
    if (ImGui::Begin(m_window_name, &m_is_open))
    {

    }

    ImGui::End();
}