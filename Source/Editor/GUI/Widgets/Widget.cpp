#include "Widget.h"
#include "../Windows/Window.h"

Widget::Widget(string _name, Window* _window)
{
    name = _name;
    window = _window;
}
Widget::~Widget()
{
    delete window;
}