#pragma once

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>
#include <unordered_map>
#include <queue>

#include <type_traits>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "ui_window.h"
#include "error_macros.h"

#include "engine_settings.h"


// This going to Editor
#include "console.h"
#include "game_view.h"
#include "tree.h"
#include "inspector.h"

class UIWindow;

class UIManager
{
public:
    UIManager(SDL_Window* window_ptr, SDL_Renderer* renderer_ptr);
    ~UIManager();

    void Render();
    void ManageEvent(SDL_Event* event);

    void RemoveUIWindow(std::string key);

    // template <typename T, typename = std::enable_if_t<std::is_base_of<UIWindow, T>::value>>
    template <typename T>
    T* AddUIWindow(std::string key)
    {
        T* ui_window_ptr = new T(this);
        m_windows[key] = ui_window_ptr;
        return ui_window_ptr;
    }

    template <typename T>
    T* GetUIWindow(std::string key)
    {
        return (T*) m_windows[key];
    }

    template <typename T>
    bool TryGetUIWindow(const std::string& key, T*& out)
    {
        auto it = m_windows.find(key);
        if (it != m_windows.end())
        {
            out = (T*)(it->second);
            return true;
        }
        return false;
    }
    
private:

    bool m_show_demo_window = false;

    SDL_Window* m_window_ptr;
    SDL_Renderer* m_renderer_ptr;

    std::unordered_map<std::string, UIWindow*> m_windows;
    std::queue<std::string> m_windows_to_remove;

    void RemoveUIWindows();

};

#endif // UI_MANAGER_H