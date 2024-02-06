#ifndef CONSOLE_H
#define CONSOLE_H

#include "ui_manager.h"

class Console : public UIWindow
{
private:
    char                  m_input_buffer[256];
    ImVector<char*>       m_items;
    ImVector<const char*> m_commands;
    ImVector<char*>       m_history;
    int                   m_history_pos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       m_filter;
    bool                  m_auto_scroll;
    bool                  m_scroll_to_bottom;

    static int Stricmp(const char* s1, const char* s2);
    static int Strnicmp(const char* s1, const char* s2, int n);
    static char* Strdup(const char* s);
    static void  Strtrim(char* s);

public:
    Console(UIManager* ui_manager);
    ~Console();

    void Render() override;

    void Clear();
    void Print(const char* fmt, ...) IM_FMTARGS(2);
    void ExecCommand(const char* command_line);

    static void EditorPrint(UIManager* ui_manager, const char* message);

    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    int TextEditCallback(ImGuiInputTextCallbackData* data);
};

#endif // CONSOLE_H