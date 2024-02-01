#ifndef INSPECTOR_UI_H
#define INSPECTOR_UI_H

#include "imgui.h"
#include "ui_window.h"
#include <string>
#include <deque>

class InspectorUI : public UIWindow
{

    const int K_MAX_LOG_ENTRIES = 20;

public:
    InspectorUI(UIManager* ui_manager);
    ~InspectorUI() = default;

    void Render() override;

    void Print(std::string message);
    void Clear();

private:

    std::deque<std::string> m_entries;

};

#endif // INSPECTOR_UI_H