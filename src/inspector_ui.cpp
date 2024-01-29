#include "inspector_ui.h"

InspectorUI::InspectorUI() : UIWindow("Inspector")
{
    m_entries.resize(K_MAX_LOG_ENTRIES);

    Print("This");

    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");
    Print("This");

    Print("Hello");
    Print("Worlf");
    Print("This");
    Print("Is my console");
    Print("This");
    Print("This");
    Print("This is a super long parr that I dont know if it fits, This is a super long parr that I dont know if it fits, This is a super long parr that I dont know if it fits, This is a super long parr that I dont know if it fits, This is a super long parr that I dont know if it fits");
    Print("This");
    Print("This");

}

void InspectorUI::Print(std::string message)
{
    if (m_entries.size() >= K_MAX_LOG_ENTRIES)
    {
        m_entries.pop_back();
    }

    m_entries.push_front(message);
}

void InspectorUI::Clear()
{
    m_entries.clear();
}

void InspectorUI::Render()
{

    ImGui::ShowDemoWindow();

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar;
    if (ImGui::Begin(m_window_name, &m_is_open, flags))
    {
        ImGui::BeginChild("scrolling", ImVec2(-10.0f, -10.0f));

        // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));

        for (int i = 0; i < m_entries.size(); i++)
        {
            ImGui::TextUnformatted(m_entries[i].c_str());
        }

        // if (true)
        // {
        //     ImGui::SetScrollHereY(1.0f);
        // }

        // // ScrollToBottom = false;
        
        // ImGui::PopStyleVar();
        ImGui::EndChild();
    
        ImGui::Separator();

        if (ImGui::Button("Clear"))
        {
            Clear();
        }

        ImGui::SameLine();

        if (ImGui::Button("Copy"))
        {
            ImGui::SetClipboardText(m_entries.front().c_str());
        }    
    }

    ImGui::End();

}