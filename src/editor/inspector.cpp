#include "inspector.h"

namespace CliqueEngine
{
        
    Inspector::Inspector(UIManager* ui_manager_ptr) : UIWindow(ui_manager_ptr, "Inspector")
    {
        m_engine_ptr = &Editor::Instance().engine;

    }


    void Inspector::Render()
    {

        if (ImGui::Begin(m_window_name, &m_is_open))
        {
            if (Editor::Instance().inspected_entity_id > -1)
            {
                flecs::entity entity = m_engine_ptr->world.entity(Editor::Instance().inspected_entity_id);
                RenderEntity(entity);
            }
        }

        ImGui::End();
    }

    int Inspector::Callback(ImGuiInputTextCallbackData* data)
    {
        if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
        {
            Editor* m_editor = &Editor::Instance();
            m_editor->engine.world.defer_begin();

            flecs::entity entity = m_editor->engine.world.entity(m_editor->inspected_entity_id);
            entity.set_name(data->Buf);

            m_editor->engine.world.defer_end();        
        }
        return 0;
    }

    void Inspector::RenderEntity(flecs::entity entity)
    {
        // ImGui::Text(entity.name().c_str());

        char entity_name_buffer[SHORT_STRING_INPUT_BUFFER] = {};


        ImGui::InputTextWithHint("###EntityName", entity.name().c_str(), entity_name_buffer, SHORT_STRING_INPUT_BUFFER, ImGuiInputTextFlags_CallbackCompletion, Inspector::Callback);

        ImGui::Separator();

        m_engine_ptr->world.defer_begin();

        entity.each([this](flecs::id id)
        {
            // auto component = m_engine->world.component(component_id);
            // const char* component_name = component.name().c_str();

            if (id.is_entity())
            {
                RenderComponent(m_engine_ptr->world.entity(id));
                // flecs::entity c = m_engine->world.entity(id);
                // c.add<int>();
                // int p = c.get<int>();
            }

            // ImGui::Text(std::to_string(component_id).c_str());
        });

        m_engine_ptr->world.defer_end();

    }

    void Inspector::RenderComponent(flecs::entity component)
    {
        if (ImGui::BeginTabBar("_Component", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem(component.name().c_str()))
            {
                ImGui::EndTabItem();
            }
            // if (ImGui::BeginTabItem("Details"))
            // {
            //     ImGui::Text("ID: 0123456789");
            //     ImGui::EndTabItem();
            // }
            ImGui::EndTabBar();
        }
    }
}