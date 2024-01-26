#ifndef INSPECTOR_UI_H
#define INSPECTOR_UI_H

#include "imgui.h"
#include "ui_window.h"

class InspectorUI : public UIWindow
{
public:
    InspectorUI();

    void Render() override;
};

#endif // INSPECTOR_UI_H