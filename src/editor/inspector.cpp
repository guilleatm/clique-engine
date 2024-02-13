#include "inspector.h"

namespace CliqueEngine
{
        
    Inspector::Inspector(UIManager* ui_manager_ptr) : UIWindow(ui_manager_ptr, "Inspector")
    {
        m_engine_ptr = &my_engine;

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
            my_engine.world.defer_begin();

            flecs::entity entity = my_engine.world.entity(m_editor->inspected_entity_id);
            entity.set_name(data->Buf);

            my_engine.world.defer_end();        
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
        // if (ImGui::BeginTabBar("_Component", ImGuiTabBarFlags_None))
        // {
        //     if (ImGui::BeginTabItem(component.name().c_str()))
        //     {
        //         ImGui::EndTabItem();
        //     }
        //     // if (ImGui::BeginTabItem("Details"))
        //     // {
        //     //     ImGui::Text("ID: 0123456789");
        //     //     ImGui::EndTabItem();
        //     // }
        //     ImGui::EndTabBar();
        // }

    
        const char* componentName = component.name().c_str();
        const flecs::Struct* struct_data = nullptr;
        
        if (component.has<flecs::Struct>())
        {
            struct_data = component.get<flecs::Struct>();
        }

        const size_t members_size = struct_data ? (size_t) ecs_vec_count(&struct_data->members) : 0;
        
        if (ImGui::CollapsingHeader(componentName, nullptr, 0))
        {
            if (struct_data)
            {
                auto members = (ecs_member_t*) ecs_vec_first(&struct_data->members);
                auto ptr = (uint8_t*) component.get_mut( component.id() );
                
                ImGui::PushID(ptr);
                
                for (size_t i = 0; i < members_size; ++i)
                {
                    if (i > 0)
                    {
                        ImGui::Separator();
                    }

                    ImGui::PushID(i);
                    const auto& member = members[i];
                    auto member_type = flecs::entity { m_engine_ptr->world, member.type };
                    const auto offset = member.offset;
                    ImGui::Text("%s:", member.name);

                    if (member_type == flecs::F32)
                    {
                        auto value = (float*)(ptr + offset);
                        ImGui::Indent();
                        ImGui::DragFloat("###value", value, 0.05f);
                        ImGui::Unindent();
                    }
                    else if (member_type == flecs::I32)
                    {
                        auto value = (int*)(ptr + offset);
                        ImGui::Indent();
                        ImGui::DragInt("###value", value);
                        ImGui::Unindent();
                    }
                    else if (member_type == flecs::Bool)
                    {
                        auto value = (bool*)(ptr + offset);
                        ImGui::Indent();
                        ImGui::Checkbox("###value", value);
                        ImGui::Unindent();
                    }

                    ImGui::PopID();
                }

                ImGui::PopID();
                ImGui::Spacing();
            }
            else
            {
                ImGui::Text("No fields serialized");
            }
        }
    }
}