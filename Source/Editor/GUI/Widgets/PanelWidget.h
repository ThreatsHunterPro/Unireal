#pragma once
#include "ActiveWidget.h"

class PanelWidget : public ActiveWidget
{
public:
    PanelWidget(const String& _name, Window* _window);
    ~PanelWidget() override;
};
