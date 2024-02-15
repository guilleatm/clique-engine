#include "editor_render_manager.h"

#include "../engine/render_manager.h"

namespace CliqueEngine
{
    EditorRenderManager::EditorRenderManager(RenderManager* render_manager_ptr)
    {
        m_render_manager_ptr = render_manager_ptr;

        window_ptr = render_manager_ptr->window_ptr;
        renderer_ptr = render_manager_ptr->renderer_ptr;
    }

    EditorRenderManager::~EditorRenderManager() {}
}