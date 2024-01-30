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
    SDL_Surface* surface_ptr = IMG_Load("build/frog_square.png");
    m_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, surface_ptr);
    SDL_FreeSurface(surface_ptr);

    ERROR_IF(m_texture_ptr == nullptr);

    std::cout << m_texture_ptr << std::endl;
}

void GameView::Render()
{
    if(ImGui::Begin(m_window_name, &m_is_open))
    {
        ImVec2 size = ImVec2(200, 200);
        ImGui::Image((ImTextureID) m_texture_ptr, size);

    }

    ImGui::End();
} 