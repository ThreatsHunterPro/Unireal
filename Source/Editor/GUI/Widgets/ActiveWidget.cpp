#include "ActiveWidget.h"

ActiveWidget::ActiveWidget(const String& _name, Window* _window) : Widget(_name, _window)
{
    widgetStatus = true;
}
ActiveWidget::~ActiveWidget()
{
    
}
