#include "console.h"

Console::Console(UIManager* ui_manager) : UIWindow(ui_manager, "Console")
{
    Clear();
    memset(m_input_buffer, 0, sizeof(m_input_buffer));
    m_history_pos = -1;

    m_commands.push_back("HELP");
    m_commands.push_back("HISTORY");
    m_commands.push_back("CLEAR");
    m_auto_scroll = true;
    m_scroll_to_bottom = false;

    Print("Welcome to the Clique Engine console!");
}

Console::~Console()
{
    Clear();
    for (int i = 0; i < m_history.Size; i++)
    {
        free(m_history[i]);
    }
}

void Console::EditorPrint(UIManager* ui_manager, const char* message)
{
    Console* console_ptr;
    bool found = ui_manager->TryGetUIWindow<Console>(K_CONSOLE_KEY, console_ptr);
    if (found)
    {
        console_ptr->Print(message);
    }
}

// Portable helpers
int   Console::Stricmp(const char* s1, const char* s2)         { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
int   Console::Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
char* Console::Strdup(const char* s)                           { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
void  Console::Strtrim(char* s)                                { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

void Console::Clear()
{
    for (int i = 0; i < m_items.Size; i++)
    {
        free(m_items[i]);
    }
    m_items.clear();
}

void Console::Print(const char* fmt, ...) //IM_FMTARGS(2)
{

    std::cout << "Console: " << fmt << std::endl;
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf)-1] = 0;
    va_end(args);
    m_items.push_back(Console::Strdup(buf));
}

void Console::Render()
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin(m_window_name, &m_is_open))
    {
        ImGui::End();
        return;
    }

    // if (ImGui::BeginPopupContextItem())
    // {
    //     if (ImGui::MenuItem("Close Console"))
    //     {
    //         m_is_open = false;
    //     }
    //     ImGui::EndPopup();
    // }

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &m_auto_scroll);
        ImGui::EndPopup();
    }

    // Options, Filter
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    m_filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
    ImGui::Separator();

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) Clear();
            ImGui::EndPopup();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

        for (const char* item : m_items)
        {
            if (!m_filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            bool has_color = false;
            if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (has_color)
                ImGui::PopStyleColor();
        }

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (m_scroll_to_bottom || (m_auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        m_scroll_to_bottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();
    ImGui::Separator();

        if (ImGui::Button("Clear"))
    {
        Clear();
    }
    ImGui::SameLine();

    if (ImGui::Button("Copy"))
    {
        ImGui::LogToClipboard();
        for (const char* item : m_items)
        {
            if (!m_filter.PassFilter(item))
                continue;

            ImVec4 color;
            bool has_color = false;
            if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (has_color)
                ImGui::PopStyleColor();
        }
        ImGui::LogFinish();
    }

    ImGui::SameLine();

    // Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    
    if (ImGui::InputText("Input", m_input_buffer, IM_ARRAYSIZE(m_input_buffer), input_text_flags, &TextEditCallbackStub, (void*)this))
    {
        char* s = m_input_buffer;
        Console::Strtrim(s);
        if (s[0])
            ExecCommand(s);
        strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::End();
}

void Console::ExecCommand(const char* command_line)
{
    Print("# %s\n", command_line);

    // Insert into history. First find match and delete it so it can be pushed to the back.
    // This isn't trying to be smart or optimal.
    m_history_pos = -1;
    for (int i = m_history.Size - 1; i >= 0; i--)
        if (Console::Stricmp(m_history[i], command_line) == 0)
        {
            free(m_history[i]);
            m_history.erase(m_history.begin() + i);
            break;
        }
    m_history.push_back(Console::Strdup(command_line));

    // Process command
    if (Console::Stricmp(command_line, "CLEAR") == 0)
    {
        Clear();
    }
    else if (Console::Stricmp(command_line, "HELP") == 0)
    {
        Print("Commands:");
        for (int i = 0; i < m_commands.Size; i++)
            Print("- %s", m_commands[i]);
    }
    else if (Console::Stricmp(command_line, "HISTORY") == 0)
    {
        int first = m_history.Size - 10;
        for (int i = first > 0 ? first : 0; i < m_history.Size; i++)
            Print("%3d: %s\n", i, m_history[i]);
    }
    else
    {
        Print("Unknown command: '%s'\n", command_line);
    }

    // On command input, we scroll to bottom even if AutoScroll==false
    m_scroll_to_bottom = true;
}

// In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
int Console::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
{
    Console* console = (Console*)data->UserData;
    return console->TextEditCallback(data);
}

int Console::TextEditCallback(ImGuiInputTextCallbackData* data)
{
    //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
    switch (data->EventFlag)
    {
    case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < m_commands.Size; i++)
                if (Console::Strnicmp(m_commands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(m_commands[i]);

            if (candidates.Size == 0)
            {
                // No match
                Print("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                Print("Possible matches:\n");
                for (int i = 0; i < candidates.Size; i++)
                    Print("- %s\n", candidates[i]);
            }

            break;
        }
    case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = m_history_pos;
            if (data->EventKey == ImGuiKey_UpArrow)
            {
                if (m_history_pos == -1)
                    m_history_pos = m_history.Size - 1;
                else if (m_history_pos > 0)
                    m_history_pos--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow)
            {
                if (m_history_pos != -1)
                    if (++m_history_pos >= m_history.Size)
                        m_history_pos = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != m_history_pos)
            {
                const char* history_str = (m_history_pos >= 0) ? m_history[m_history_pos] : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
    }
    return 0;
}