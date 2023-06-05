#include "Button.h"

Button::Button()
{
    title = "ButtonTitle";
    shortcut = "";
    event = Event();
    children = Array<Button>();
}
Button::Button(const char* _title, Action _callback, const char* _shortcut, Array<Button> _button)
{
    title = _title;
    shortcut = _shortcut;
    event = Event(_callback);
    children = _button;
}
Button::~Button()
{
    children.Empty();
}