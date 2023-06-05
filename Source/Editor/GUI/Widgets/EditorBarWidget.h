#pragma once
#include "Widget.h"
#include "../Controls/Button.h"
#include "../../../Core/Macros.h"

class EditorBarWidget : public Widget
{
    Array<Menu> menus;
    
public:
    EditorBarWidget(string _name, Window* _window);
    ~EditorBarWidget() override;

public:
    void Draw() override;
    void ExecuteCallback(string _methodName) const;
    void Stop() override;
};