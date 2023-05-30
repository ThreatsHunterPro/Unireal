#include "Button.h"

Button::Button()
{
    title = "Button";
    event = Event();
    children = Array<Button>();
}
Button::Button(const char* _title, Action _callback, Array<Button> _button)
{
    title = _title;
    event = Event(_callback);
    children = _button;
}
Button::~Button()
{
    children.Empty();
}