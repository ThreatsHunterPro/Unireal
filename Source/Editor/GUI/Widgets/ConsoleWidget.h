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
    ~ConsoleWidget() override;

public:
    void Draw() override;
    void Clear();
    void AddLog(Log_Severity severity, const char* fmt, ...);
    const char* SeverityToString(Log_Severity _severity) const;
    const char** Collapse();
    void Stop() override;
};