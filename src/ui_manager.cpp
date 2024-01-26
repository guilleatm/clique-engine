#include "ui_manager.h"

UIManager::UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr)
{
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void) io;

	ImGui_ImplSDL2_InitForSDLRenderer(window_ptr, renderer_ptr);
	ImGui_ImplSDLRenderer2_Init(renderer_ptr);
}

UIManager::~UIManager()
{
    ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}


void UIManager::ManageEvent(SDL_Event* event)
{
    ImGui_ImplSDL2_ProcessEvent(event);
}

void UIManager::PreRender(SDL_Window* window_ptr)
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    Draw();
}

void UIManager::Render()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::Draw()
{

}
