#include "tree.h"


Tree::Tree(UIManager* ui_manager_ptr) : UIWindow(ui_manager_ptr, "Tree")
{
    m_engine = &Editor::Instance().engine;
}

Tree::~Tree()
{
    
}

void Tree::Render(flecs::entity entity)
{
    int64_t id = entity.id();
    ImGui::PushID(id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();

    const bool is_selected = Editor::Instance().inspected_entity_id == id;
    
    bool has_children = m_engine->world.count(flecs::ChildOf, entity) != 0;

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;

    if (is_selected)
    {
        node_flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (has_children)
    {
        bool node_open = ImGui::TreeNodeEx("_Entity", node_flags, entity.name().c_str());

        DragDropSource(id);
        DragDropTarget(id);

        if (node_open)
        {
            entity.children([&](flecs::entity child)
            {
                Render(child);
            });

            ImGui::TreePop();
        }
    }
    else
    {
        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
        ImGui::TreeNodeEx("_Entity", node_flags, entity.name().c_str());

        DragDropSource(id);
        DragDropTarget(id);
    }

    if (ImGui::IsItemClicked())
    {
        Editor::Instance().inspected_entity_id = id;
    }

    ImGui::PopID();
}


void Tree::Render()
{
    if (ImGui::Begin(m_window_name, &m_is_open))
    {

        if (ImGui::Button("Add Entity"))
        {
            m_engine->CreateEntity();
        }

        ImGui::SameLine();

        ImGui::TextDisabled("(?)");
        if (ImGui::BeginItemTooltip())
        {
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted("Powered by flecs.");
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        if (ImGui::BeginTable("_TreeTable", 1, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Entities");
            ImGui::TableHeadersRow();


            m_engine->world.defer_begin();

            m_engine->world.filter_builder()
            .without(flecs::ChildOf, flecs::Wildcard)
            .each([this](flecs::entity root_entity)
            {
                Render(root_entity);
            });

            m_engine->world.defer_end();


            ImGui::EndTable();
        }
        ImGui::PopStyleVar();
    }

    ImGui::End();
}



void Tree::DragDropSource(const int& source_id)
{
    if (ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("ID", &source_id, sizeof(int));
        ImGui::Text("The claaaaaw");
        ImGui::EndDragDropSource();
    }
}

void Tree::DragDropTarget(int target_id)
{
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ID"))
        {
            int source_id = *(const int*) payload->Data;
           
            flecs::entity entity = m_engine->world.entity(source_id);
            flecs::entity new_parent = m_engine->world.entity(target_id);

            entity.child_of(new_parent);
        }

        ImGui::EndDragDropTarget();
    }
}