#include "game_view.h"

GameView::GameView(UIManager* ui_manager) : UIWindow(ui_manager, "Game View")
{
    m_engine = new Engine();
}

GameView::~GameView()
{
    delete m_engine;
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
            Console::EditorPrint(m_ui_manager, "Play");
            m_state = GameViewState::Play;
        }

        ImGui::SameLine();

        if (ImGui::Button("Pause"))
        {
            Console::EditorPrint(m_ui_manager, "Pause");
            m_state = GameViewState::Pause;
        }

        ImGui::SameLine();

        if(ImGui::Button("Stop"))
        {
            Console::EditorPrint(m_ui_manager, "Stop");
            m_state = GameViewState::Stop;
        }

        ImGui::Separator();

        switch (m_state)
        {
        case GameViewState::Play:
            m_engine->Update();
            // No break

        case GameViewState::Pause:
            m_engine->Render();
            break;
        
        case GameViewState::Stop:
        default:
            break;
        }


        //ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 size = ImVec2(200, 200);
        ImGui::Image((ImTextureID) m_texture_ptr, size);

    }

    ImGui::End();
} 