#pragma once
#include "Widget.h"

class ToolBarWidget : public Widget
{
    
public:
    ToolBarWidget(const String& _name, Window* _window);

public:
    void Draw() override;
};
