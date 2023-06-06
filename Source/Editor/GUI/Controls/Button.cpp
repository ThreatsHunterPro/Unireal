#include "Button.h"

Button::Button()
{
    title = "ButtonTitle";
    shortcut = "";
    event = Event();
    children = Array<Button*>();
}
Button::Button(const String& _title, Action _callback, const String& _shortcut, const Array<Button*>& _button)
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