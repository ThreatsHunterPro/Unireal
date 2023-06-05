#pragma once
#include "PanelWidget.h"
#include "../Controls/Button.h"

enum Log_Severity { Message, Warning, Error };

struct LogE
{
    
};

class ConsoleWidget : public PanelWidget
{
    Array<Button> buttons;
    bool showMessages;
    bool showWarnings;
    bool showErrors;
    bool autoScroll;
    ImGuiTextBuffer buffer;
    ImGuiTextFilter filter;
    ImVector<int> offsets;
    
public:
    ConsoleWidget(const string& _name, Window* _window);
    ~ConsoleWidget() override = default;

public:
    void Draw() override;
    void Stop() override;

private:
    void AddLog(Log_Severity severity, const char* fmt, ...);
    void ShowLogs();
    void ClearLogs();
    
    const char* SeverityToString(Log_Severity _severity) const;


    void PrintOnCollapse();
    const char** Collapse();
    bool CheckToCollapse(int& _index);
    
};