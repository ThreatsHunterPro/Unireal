#pragma once
#include "ActiveWidget.h"

class PanelWidget : public ActiveWidget
{
public:
    PanelWidget(String _name, Window* _window);
    ~PanelWidget() override;
};
