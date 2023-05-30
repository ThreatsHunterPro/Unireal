#include "ActiveWidget.h"

ActiveWidget::ActiveWidget(string _name, Window* _window) : Widget(_name, _window)
{
    widgetStatus = true;
}
ActiveWidget::~ActiveWidget()
{
    
}
