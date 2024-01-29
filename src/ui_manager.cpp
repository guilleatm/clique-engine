#include "ui_manager.h"

const int K_DEFAULT_WINDOW_COUNT = 5;

UIManager::UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr)
{
    m_window_ptr = window_ptr;
    m_renderer_ptr = renderer_ptr;

    m_windows = std::vector<UIWindow*>();
    m_windows.reserve(K_DEFAULT_WINDOW_COUNT);
 
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); //(void) io;
    
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForSDLRenderer(m_window_ptr, m_renderer_ptr);
	ImGui_ImplSDLRenderer2_Init(m_renderer_ptr);

    // Defaults
    AddUIWindow<Console>();
}

UIManager::~UIManager()
{
    for (int i = 0; i < m_windows.size(); i++)
    {
        delete m_windows[i];
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

            if (ImGui::MenuItem("Console"))
            {
                AddUIWindow<Console>();
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

    ImGui::Begin("Main", NULL, flags);

    for (int i = 0; i < m_windows.size(); i++)
    {
        m_windows[i]->Render();

        if (!m_windows[i]->m_is_open)
        {
            RemoveUIWindow(m_windows[i]);
        }
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::RemoveUIWindow(UIWindow* ui_window)
{
    std::vector<UIWindow*>::iterator it = std::find(m_windows.begin(), m_windows.end(), ui_window);
    delete *it;
    m_windows.erase(it);
}