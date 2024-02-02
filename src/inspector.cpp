#include "inspector.h"


Inspector::Inspector(UIManager* ui_manager_ptr) : UIWindow(ui_manager_ptr, "Inspector")
{
    m_engine = &Editor::Instance().engine;

}


void Inspector::Render()
{
    if (ImGui::Begin(m_window_name, &m_is_open))
    {
        if (Editor::Instance().inspected_entity_id > -1)
        {
            flecs::entity entity = m_engine->world.entity(Editor::Instance().inspected_entity_id);
            Render(entity);
        }
    }

    ImGui::End();
}

void Inspector::Render(flecs::entity entity)
{
    ImGui::Text(entity.name().c_str());
    m_engine->world.defer_begin();

    entity.each([this](flecs::id id)
    {
        // auto component = m_engine->world.component(component_id);
        // const char* component_name = component.name().c_str();

        ImGui::Text(id.str().c_str());
        // ImGui::Text(std::to_string(component_id).c_str());
    });

    m_engine->world.defer_end();

}

