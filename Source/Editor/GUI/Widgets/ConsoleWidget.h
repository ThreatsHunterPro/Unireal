#pragma once
#include "PanelWidget.h"
#include "../Controls/Button.h"

enum Log_Severity { Message, Warning, Error };

class Log
{
    double time;
    Log_Severity Severity;
    String text;

public:
    Log(double _time, Log_Severity _severity, String _text)
    {
        time = _time;
        Severity = _severity;
        text = _text;
    }

public:
    String GetFullLog() const
    {
        return String("[") + String::FromDouble(time) + "] " + to_string(Severity) + ": " + text;
    }
    ImVec4 GetColor() const
    {
        switch (Severity)
        {
        case Message:
            return ImVec4(0.4f, 0.8f, 0.4f, 1.0f);
                
        case Warning:
            return ImVec4();
                
        case Error:
            return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        return ImVec4();
    }
};

class ConsoleWidget : public PanelWidget
{
    Array<Log*> logs;
    Array<Button*> buttons;
    bool showMessages;
    bool showWarnings;
    bool showErrors;
    bool autoScroll;
    ImGuiTextBuffer buffer;
    ImGuiTextFilter filter;
    ImVector<int> offsets;
    
public:
    ConsoleWidget(const String& _name, Window* _window);
    ~ConsoleWidget() override = default;

public:
    void Draw() override;
    void Stop() override;

private:
    void AddLog(Log_Severity severity, String _string, ...);
    void ShowLogs();
    void ClearLogs();

    void PrintOnCollapse();
    const char** Collapse();
    bool CheckToCollapse(int& _index);
    
};