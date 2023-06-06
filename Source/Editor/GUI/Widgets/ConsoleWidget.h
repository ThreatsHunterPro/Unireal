#pragma once
#include "PanelWidget.h"
#include "../Controls/Button.h"

enum Log_Severity { Message, Warning, Error };

class Log
{
    double time;
    Log_Severity severity;
    String text;

public:
    Log(double _time, Log_Severity _severity, const String& _text)
    {
        time = _time;
        severity = _severity;
        text = _text;
    }

public:
    Log_Severity GetSeverity() const { return severity; }
    String GetText() const { return text; }
    String GetFullText() const
    {
        return String("[") + String::FromDouble(time) + "] " + GetSeverityString(severity) + ": " + text;
    }
    ImVec4 GetColor() const
    {
        switch (severity)
        {
        case Message:
            return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                
        case Warning:
            return ImVec4(1.0f, 0.35f, 0.0f, 1.0f);
                
        case Error:
            return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        return ImVec4();
    }

private:
    String GetSeverityString(const Log_Severity& _severity) const
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
};

class LogGroup
{
public:
    int Count;
    String Text;
    String FullText;
    ImVec4 Color;

public:
    LogGroup(const String& _text, const String& _fullText, ImVec4 _color)
    {
        Text = _text;
        FullText = _fullText;
        Color = _color;
        Count = 1;
    }

    bool IsEquals(const String& _text) const
    {
        return Text == _text;
    }
};

class ConsoleWidget final : public PanelWidget
{
    Array<Log*> logs;
    Array<Button*> buttons;
    bool collapse;
    bool showMessages;
    bool showWarnings;
    bool showErrors;
    bool autoScroll;
    ImGuiTextFilter filter;
    
public:
    ConsoleWidget(const String& _name, Window* _window);
    ~ConsoleWidget() override;

public:
    void Draw() override;
    void Stop() override;

private:
    void AddLog(Log_Severity severity, const String& _string, ...);
    void ShowLogs();
    Array<LogGroup*> GetLogs();
    void ClearLogs();

    bool IsFiltered(const Log_Severity& _severity, const String& _text);
    bool IsSeverityFiltered(Log_Severity severity);
};