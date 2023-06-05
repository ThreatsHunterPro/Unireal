#include "ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(const string& _name, Window* _window) : PanelWidget(_name, _window)
{
    buttons =
    {
        Button("Clear", [this]
        {
            ClearLogs();
        }),
        Button("Clear on Play", [this]
        {
            ImGui::LogToClipboard();
        }),
        Button("Collapse", [this]
        {
            AddLog(Error, "Collapse");
        }),
        Button("Error Pause", [this]
        {
            cout << "Pause" << endl;
        }),
        Button("Filters", [this]
        {
           if (ImGui::BeginPopup("Options"))
           {
               ImGui::Checkbox("Messages", &showMessages);
               ImGui::Checkbox("Warnings", &showWarnings);
               ImGui::Checkbox("Errors", &showErrors);
               ImGui::EndPopup();
           }

            ImGui::OpenPopup("Options");
        })
    };

    showMessages = true;
    showWarnings = true;
    showErrors = true;
    autoScroll = true;
    
    ClearLogs();
}


void ConsoleWidget::Draw()
{
    constexpr ImGuiTabBarFlags _tabFlags = ImGuiTabBarFlags_FittingPolicyDefault_ | ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("Tabs", _tabFlags))
    {
        // for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
        {
            // MyDocument* doc = &app.Documents[doc_n];
            // if (!doc->Open)
            //     continue;
            //
            // ImGuiTabItemFlags tab_flags = (doc->Dirty ? ImGuiTabItemFlags_UnsavedDocument : 0);
            // bool visible = ImGui::BeginTabItem(doc->Name, &doc->Open, tab_flags);
            //
            // // Cancel attempt to close when unsaved add to save queue so we can display a popup.
            // if (!doc->Open && doc->Dirty)
            // {
            //     doc->Open = true;
            //     doc->DoQueueClose();
            // }
            //
            // MyDocument::DisplayContextMenu(doc);
            // if (visible)
            // {
            //     MyDocument::DisplayContents(doc);
            //     ImGui::EndTabItem();
            // }
        }

        ImGui::EndTabBar();
    }
    
    ImGui::Begin(name.c_str(), nullptr);
    const int _buttonsCount = buttons.Lenght();
    for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
    {
        Button _button = buttons[_buttonIndex];
        if (!_button) continue;

        if (ImGui::Button(_button.GetTitle()))
        {
            _button.Callback();
        }
        ImGui::SameLine();
    }
    
    ImGui::SameLine();
    filter.Draw("Filter", 250.0f);
    
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &autoScroll);
    
    ImGui::Separator();
    ShowLogs();
    
    ImGui::Separator();
    ImGui::End();
}

void ConsoleWidget::Stop()
{
    ClearLogs();
}


void ConsoleWidget::AddLog(Log_Severity _severity, const char* _toAdd, ...)
{
    va_list _args;
    va_start(_args, _toAdd);
    
    char _logWithSeverity[1024];
    snprintf(_logWithSeverity, sizeof(_logWithSeverity), "[%f] %s: %s\n", ImGui::GetTime(), SeverityToString(_severity), _toAdd);
    buffer.appendfv(_logWithSeverity, _args);

    va_end(_args);
    
    int _oldSize = buffer.size();
    for (const int newSize = buffer.size(); _oldSize < newSize; _oldSize++)
    {
        if (buffer[_oldSize] == '\n')
        {
            offsets.push_back(_oldSize + 1);
        }
    }
}

void ConsoleWidget::ShowLogs()
{
    if (ImGui::BeginChild("Console", ImVec2(0.0f, 0.0f), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        const char* _buffer = buffer.begin();
        const char* _bufferEnd = buffer.end();
        
        if (filter.IsActive())
        {
            for (int _line = 0; _line < offsets.Size; _line++)
            {
                const char* _lineStart = _buffer + offsets[_line];
                const char* _lineEnd = (_line + 1 < offsets.Size) ? (_buffer + offsets[_line + 1] - 1) : _bufferEnd;
                
                if (filter.PassFilter(_lineStart, _lineEnd))
                {
                    PrintOnCollapse();
                    
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.8f, 0.4f, 1.0f));
                    ImGui::TextUnformatted(_lineStart, _lineEnd);
                    ImGui::PopStyleColor();
                }
            }
        }
        else
        {
            ImGuiListClipper clipper;
            clipper.Begin(offsets.Size);
            while (clipper.Step())
            {
                for (int _line = clipper.DisplayStart; _line < clipper.DisplayEnd; _line++)
                {
                    const char* line_start = _buffer + offsets[_line];
                    const char* line_end = (_line + 1 < offsets.Size) ? (_buffer + offsets[_line + 1] - 1) : _bufferEnd;
                    
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                    ImGui::TextUnformatted(line_start, line_end);
                    ImGui::PopStyleColor();
                }
            }
            clipper.End();
        }

        if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }
    }
    ImGui::EndChild();
}

void ConsoleWidget::ClearLogs()
{
    buffer.clear();
    offsets.clear();
    offsets.push_back(0);
}

const char* ConsoleWidget::SeverityToString(Log_Severity _severity) const
{
    switch (_severity)
    {
    case Message:
        return "Message";
                
    case Warning:
        return "Warning";
                
    case Error:
        return "Error";
    }
        
    return "";
}


void ConsoleWidget::PrintOnCollapse()
{
    
}

const char** ConsoleWidget::Collapse()
{
    

    return nullptr;
}

bool ConsoleWidget::CheckToCollapse(int& _index)
{
    // int resultat = strcmp(chaine1, chaine2);
    //
    // if (resultat == 0)
    // {
    //     printf("Les deux chaînes sont identiques.\n");
    // }
    
    // index to double
    // double ou non*

    return true;
}