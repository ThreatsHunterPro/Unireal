#pragma once
#include "Widget.h"

class ToolBarWidget : public Widget
{
    
public:
    ToolBarWidget(String _name, Window* _window);

public:
    void Draw() override;
};
