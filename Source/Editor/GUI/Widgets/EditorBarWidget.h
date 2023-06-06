#pragma once
#include "Widget.h"
#include "../Controls/Menu.h"
#include "../../../Core/Macros.h"

class EditorBarWidget : public Widget
{
    Array<Menu> menus;
    
public:
    EditorBarWidget(const String& _name, Window* _window);
    ~EditorBarWidget() override;

public:
    void Draw() override;
    void ExecuteCallback(const String& _methodName) const;
    void Stop() override;
};