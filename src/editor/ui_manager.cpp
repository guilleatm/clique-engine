#include "ui_manager.h"

#include "imgui.h"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "editor_settings.h"
#include "error_macros.h"

#include "ui_window.h"

#include "console.h"
#include "game_view.h"
#include "tree.h"
#include "inspector.h"

namespace CliqueEngine
{
    const int K_DEFAULT_WINDOW_COUNT = 5;


    class Console;
    class Tree;
    class GameView;
    class Inspector;

    UIManager::UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr)
    {
        m_window_ptr = window_ptr;
        m_renderer_ptr = renderer_ptr;

        m_windows = std::unordered_map<std::string, UIWindow*>();
        m_windows.reserve(K_DEFAULT_WINDOW_COUNT);

        m_windows_to_remove = std::queue<std::string>();
    
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); //(void) io;
        
        io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

        ImGui_ImplSDL2_InitForSDLRenderer(m_window_ptr, m_renderer_ptr);
        ImGui_ImplSDLRenderer2_Init(m_renderer_ptr);

        // Defaults, // This going to Editor?
        AddUIWindow<Console>(K_CONSOLE_KEY);
        AddUIWindow<Tree>(K_TREE_KEY);
        AddUIWindow<Inspector>(K_INSPECTOR_KEY);
        AddUIWindow<GameView>(K_GAME_VIEW_KEY)->Prepare(renderer_ptr);
    }

    UIManager::~UIManager()
    {
        for (auto it = m_windows.begin(); it != m_windows.end(); it++)
        {
            delete it->second;
        }

        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void UIManager::ManageEvent(SDL_Event* event)
    {
        ImGui_ImplSDL2_ProcessEvent(event);
    }

    void UIManager::Render()
    {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Windows"))
            {

                if (ImGui::MenuItem("Tree"))
                {
                    auto it = m_windows.find(K_TREE_KEY);
                    if (it == m_windows.end())
                    {
                        AddUIWindow<Tree>(K_TREE_KEY);
                    }
                }

                if (ImGui::MenuItem("Inspector"))
                {
                    auto it = m_windows.find(K_INSPECTOR_KEY);
                    if (it == m_windows.end())
                    {
                        AddUIWindow<Tree>(K_INSPECTOR_KEY);
                    }
                }
                
                if (ImGui::MenuItem("Game View"))
                {
                    auto it = m_windows.find(K_GAME_VIEW_KEY);
                    if (it == m_windows.end())
                    {
                        AddUIWindow<Tree>(K_GAME_VIEW_KEY);
                    }
                }

                if (ImGui::MenuItem("Console"))
                {
                    auto it = m_windows.find(K_CONSOLE_KEY);
                    if (it == m_windows.end())
                    {
                        AddUIWindow<Console>(K_CONSOLE_KEY);
                    }
                }

                ImGui::MenuItem("Demo Window", NULL, &m_show_demo_window);

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if (m_show_demo_window)
        {
            ImGui::ShowDemoWindow();
        }


        bool use_work_area = true;
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        ImGui::Begin("###Main", NULL, flags);

        for (auto it = m_windows.begin(); it != m_windows.end(); it++)
        {
            it->second->Render();

            if (!it->second->m_is_open)
            {
                RemoveUIWindow(it->first);
            }
        }

        RemoveUIWindows();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    }

    void UIManager::RemoveUIWindow(std::string key)
    {
        m_windows_to_remove.push(key);
    }

    void UIManager::RemoveUIWindows()
    {
        while (!m_windows_to_remove.empty())
        {
            std::string key = m_windows_to_remove.front();
            m_windows_to_remove.pop();

            auto it = m_windows.find(key);
            ERROR_MSG_IF(it == m_windows.end(), "Window " << key << " not found.");
            delete it->second;
            m_windows.erase(it);
        }
    }
}