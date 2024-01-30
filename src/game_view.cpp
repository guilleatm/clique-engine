#include "game_view.h"

GameView::GameView() : UIWindow("Game View")
{
}

GameView::~GameView()
{  
    SDL_DestroyTexture(m_texture_ptr);
}

void GameView::Prepare(SDL_Renderer* renderer_ptr)
{
    SDL_Surface* surface_ptr = IMG_Load("assets/frog_square.png");
    m_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, surface_ptr);
    SDL_FreeSurface(surface_ptr);

    ERROR_IF(m_texture_ptr == nullptr);

    std::cout << m_texture_ptr << std::endl;
}

void GameView::Render()
{
    if(ImGui::Begin(m_window_name, &m_is_open))
    {
        if (ImGui::Button("Play"))
        {
            // m_engine = new Engine();
        }

        ImGui::SameLine();

        // if(ImGui::Button("Stop"))
        // {
        //     delete m_engine;
        // }

        // ImGui::Separator();
        

        // if (m_engine != nullptr)
        // {
        //     m_engine->Update();
        // }


        //ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 size = ImVec2(200, 200);
        ImGui::Image((ImTextureID) m_texture_ptr, size);

    }

    ImGui::End();
} 