#include "ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(const String& _name, Window* _window) : PanelWidget(_name, _window)
{
    logs = Array<Log*>();
    buttons = 
    {
        new Button("Clear", [this]
        {
            ClearLogs();
        }),
        new Button("Clear on Play", [this]
        {
            AddLog(Message, "Clear on Play");
        }),
        new Button("Collapse", [this]
        {
            collapse = !collapse;
        }),
        new Button("Error Pause", [this]
        {
            AddLog(Error, "Error Pause");
        }),
        new Button("Filters", [this]
        {
            ImGui::OpenPopup("SeverityFilter");
        })
    };

    collapse = false;
    showMessages = true;
    showWarnings = true;
    showErrors = true;
    autoScroll = true;
}

ConsoleWidget::~ConsoleWidget() = default;


void ConsoleWidget::Draw()
{
    /*
    if (ImGui::TreeNode("Advanced & Close Button"))
        {
            constexpr ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_FittingPolicyResizeDown;

            const Array<String>& _names = { "Artichoke", "Beetroot", "Celery", "Daikon" };
            Array<bool> _opened = { true, true, true, true };

            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                for (int n = 0; n < _opened.Lenght(); n++)
                    if (_opened[n] && ImGui::BeginTabItem(_names[n], &_opened[n], ImGuiTabItemFlags_None))
                    {
                        ImGui::Text("This is the %s tab!", _names[n]);
                        ImGui::EndTabItem();
                    }
                ImGui::EndTabBar();
            }
        
            ImGui::Separator();
            ImGui::TreePop();
        }
    */

    ImGui::Begin(name, &widgetStatus);
    
    const int _buttonsCount = buttons.Lenght();
    for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
    {
        Button* _button = buttons[_buttonIndex];
        if (!_button) continue;

        if (ImGui::Button(_button->GetTitle()))
        {
            _button->Callback();
        }
        ImGui::SameLine();
    }
    
    if (ImGui::BeginPopup("SeverityFilter", ImGuiPopupFlags_None))
    {
        ImGui::Checkbox("Messages", &showMessages);
        ImGui::Checkbox("Warnings", &showWarnings);
        ImGui::Checkbox("Errors", &showErrors);
        ImGui::EndPopup();
    }
    
    ImGui::SameLine();
    filter.Draw("Filter", 200.0f);
    
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


void ConsoleWidget::AddLog(Log_Severity _severity, const String& _string, ...)
{
    Log* _log = new Log(ImGui::GetTime(), _severity, _string);
    logs.Add(_log);
}

void ConsoleWidget::ShowLogs()
{
    if (ImGui::BeginChild("Console", ImVec2(0.0f, 0.0f), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        Array<LogGroup*> _logGroups = GetLogs();
        const int _groupsCount = _logGroups.Lenght();
        
        for (int _groupIndex = 0; _groupIndex < _groupsCount; _groupIndex++)
        {
            const LogGroup* _group = _logGroups[_groupIndex];
            ImGui::TextColored(_group->Color, _group->FullText);

            if (collapse)
            {
                ImGui::SameLine(350.0f);
                ImGui::Text(String::FromInt(_group->Count));
            }
        }
        
        if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }
    }

    ImGui::EndChild();
}

Array<LogGroup*> ConsoleWidget::GetLogs()
{
    Array<LogGroup*> _logGroups = Array<LogGroup*>();
    
    const int _logsCount = logs.Lenght();
    for (int _logIndex = 0; _logIndex < _logsCount; _logIndex++)
    {
        const Log* _log = logs[_logIndex];
        const String& _text = _log->GetText();
        const String& _fullText = _log->GetFullText();
        const Log_Severity& _severity = _log->GetSeverity();
        const ImVec4& _color = _log->GetColor();
        
        if (IsFiltered(_severity, _text)) continue;

        if (_logGroups.Lenght() <= 0 || !collapse)
        {
            _logGroups.Add(new LogGroup(_text, _fullText, _color));
            continue;
        }

        bool _isEquals = false;
        for (int _groupIndex = 0; _groupIndex < _logGroups.Lenght(); _groupIndex++)
        {
            LogGroup* _group = _logGroups[_groupIndex];
                    
            if (_group->IsEquals(_text))
            {
                _group->Count += 1;
                _isEquals = true;
                break;
            }
        }

        if (!_isEquals)
        {
            _logGroups.Add(new LogGroup(_text, _fullText, _color));
        }
    }

    return _logGroups;
}

void ConsoleWidget::ClearLogs()
{
    logs.Empty();
}


bool ConsoleWidget::IsFiltered(const Log_Severity& _severity, const String& _text)
{
    return IsSeverityFiltered(_severity) || filter.IsActive() && !filter.PassFilter(_text);
}

bool ConsoleWidget::IsSeverityFiltered(Log_Severity _severity)
{
    switch (_severity)
    {
        case Message:
            return !showMessages;

        case Warning:
            return !showWarnings;

        case Error:
            return !showErrors;
    }

    return false;
}