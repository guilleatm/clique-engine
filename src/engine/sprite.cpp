#include "sprite.h"

#include <SDL.h>
#include <SDL_image.h>
#include "engine.h"

namespace CliqueEngine
{
    Sprite::Sprite()
    {
        m_renderer_ptr = Engine::Instance().render_manager.renderer_ptr;

        SDL_Surface* surface_ptr = IMG_Load("build/assets/frog_square.png");
        m_texture_ptr = SDL_CreateTextureFromSurface(m_renderer_ptr, surface_ptr);
        SDL_FreeSurface(surface_ptr);
    }

    Sprite::~Sprite()
    {
        SDL_DestroyTexture(m_texture_ptr);
    }

    void Sprite::Render() const
    {
        std::cout << "rendering" << std::endl;
        const SDL_Rect r = SDL_Rect({0, 0, 100, 100});
        SDL_RenderCopy(m_renderer_ptr, m_texture_ptr, NULL, &r);
    }
}