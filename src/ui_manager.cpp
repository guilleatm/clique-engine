#include "ui_manager.h"

const int K_DEFAULT_WINDOW_COUNT = 5;

UIManager* UIManager::Instance(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr)
{
    static UIManager instance = UIManager(window_ptr, renderer_ptr);
    return &instance;
}

UIManager::UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr)
{
    m_window_ptr = window_ptr;
    m_renderer_ptr = renderer_ptr;

    m_windows = std::vector<UIWindow*>();
    m_windows.reserve(K_DEFAULT_WINDOW_COUNT);
 
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void) io;

	ImGui_ImplSDL2_InitForSDLRenderer(m_window_ptr, m_renderer_ptr);
	ImGui_ImplSDLRenderer2_Init(m_renderer_ptr);
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


    for (int i = 0; i < m_windows.size(); i++)
    {
        m_windows[i]->Render();
    }


    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}


void UIManager::AddUIWindow(UIWindow* ui_window)
{
    m_windows.push_back(ui_window);
}

void UIManager::RemoveUIWindow(UIWindow* ui_window)
{
    std::vector<UIWindow*>::iterator it = std::find(m_windows.begin(), m_windows.end(), ui_window);
    m_windows.erase(it);
    delete *it;
}