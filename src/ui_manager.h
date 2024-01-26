#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

class UIManager
{
public:
    UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr);
    ~UIManager();
    void Render(SDL_Window* window_ptr);

private:


};

#endif // UI_MANAGER_H