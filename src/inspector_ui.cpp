#include "inspector_ui.h"

InspectorUI::InspectorUI() : UIWindow("Inspector")
{

}

void InspectorUI::Render()
{
    if (ImGui::Begin(m_window_name, &m_is_open))
    {
        ImGui::Text("I am the imgui text");
    }

    ImGui::End();
}