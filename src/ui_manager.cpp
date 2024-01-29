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
	ImGuiIO& io = ImGui::GetIO(); //(void) io;
    
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

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

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Windows"))
        {

            // if (ImGui::MenuItem("Console"))
            // {
            //     Console* c = new Console();
            //     AddUIWindow(c);
            // }

            if (ImGui::MenuItem("Demo Window", NULL, &m_show_demo_window))
            {
                ImGui::ShowDemoWindow();
            }

            ImGui::EndMenu();
        }
        // if (ImGui::BeginMenu("Edit"))
        // {
        //     if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
        //     if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        //     ImGui::Separator();
        //     if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        //     if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        //     if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        //     ImGui::EndMenu();
        // }
        ImGui::EndMainMenuBar();
    }


    bool use_work_area = true;
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
    // Based on your use case you may want one or the other.
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    ImGui::Begin("Main", NULL, flags);

    for (int i = 0; i < m_windows.size(); i++)
    {
        m_windows[i]->Render();
    }

    ImGui::End();

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



// static void ShowExampleAppFullscreen(bool* p_open)
// {
//     static bool use_work_area = true;
//     static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

//     // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
//     // Based on your use case you may want one or the other.
//     const ImGuiViewport* viewport = ImGui::GetMainViewport();
//     ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
//     ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

//     if (ImGui::Begin("Example: Fullscreen window", p_open, flags))
//     {
//         ImGui::Checkbox("Use work area instead of main area", &use_work_area);
//         ImGui::SameLine();
//         HelpMarker("Main Area = entire viewport,\nWork Area = entire viewport minus sections used by the main menu bars, task bars etc.\n\nEnable the main-menu bar in Examples menu to see the difference.");

//         ImGui::CheckboxFlags("ImGuiWindowFlags_NoBackground", &flags, ImGuiWindowFlags_NoBackground);
//         ImGui::CheckboxFlags("ImGuiWindowFlags_NoDecoration", &flags, ImGuiWindowFlags_NoDecoration);
//         ImGui::Indent();
//         ImGui::CheckboxFlags("ImGuiWindowFlags_NoTitleBar", &flags, ImGuiWindowFlags_NoTitleBar);
//         ImGui::CheckboxFlags("ImGuiWindowFlags_NoCollapse", &flags, ImGuiWindowFlags_NoCollapse);
//         ImGui::CheckboxFlags("ImGuiWindowFlags_NoScrollbar", &flags, ImGuiWindowFlags_NoScrollbar);
//         ImGui::Unindent();

//         if (p_open && ImGui::Button("Close this window"))
//             *p_open = false;
//     }
//     ImGui::End();
// }