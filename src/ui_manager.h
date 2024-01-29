#pragma once

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <type_traits>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ui_window.h"

#include "console.h"

class UIWindow;

class UIManager
{
public:
    UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr);
    ~UIManager();

    void Render();
    void ManageEvent(SDL_Event* event);

    void RemoveUIWindow(UIWindow* ui_window);

    template <typename T, typename = std::enable_if_t<std::is_base_of<UIWindow, T>::value>>
    T* AddUIWindow()
    {
        T* window = new T();
        m_windows.push_back(window);
        return window;
    }

    
private:

    bool m_show_demo_window = false;

    SDL_Window* m_window_ptr;
    SDL_Renderer* m_renderer_ptr;

    std::vector<UIWindow*> m_windows;
};

#endif // UI_MANAGER_H