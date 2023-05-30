#pragma once
#include "ActiveWidget.h"

class PanelWidget : public ActiveWidget
{
public:
    PanelWidget(string _name, Window* _window);
    ~PanelWidget() override;
};
