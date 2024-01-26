#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>
#include <vector>
#include <algorithm>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ui_window.h"

class UIWindow;

class UIManager
{
public:

    static UIManager* Instance(SDL_Window* window_ptr = nullptr, SDL_Renderer* renderer_ptr = nullptr);
    
    void Render();
    void ManageEvent(SDL_Event* event);

    void AddUIWindow(UIWindow* ui_window);
    void RemoveUIWindow(UIWindow* ui_window);

    
private:

    UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr);
    ~UIManager();

    SDL_Window* m_window_ptr;
    SDL_Renderer* m_renderer_ptr;

    std::vector<UIWindow*> m_windows;

};

#endif // UI_MANAGER_H