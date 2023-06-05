#pragma once
#include "../../../Core/Macros.h"

class Button;

struct Menu
{
    String Title;
    Array<Button*> Buttons;
    Array<int> Separators;

    Menu()
    {
        Title = "";
        Buttons = Array<Button*>();
    }
    Menu(String _title, Array<Button*> _buttons, Array<int> _separators = Array<int>())
    {
        Title = _title;
        Buttons = _buttons;
        Separators = _separators;
    }
};

class Button
{
    String title;
    String shortcut;
    Event<> event;
    Array<Button*> children;
    
public:
    FORCEINLINE String GetTitle() const { return title; }
    FORCEINLINE String GetShortcut() const { return shortcut; }
    FORCEINLINE Array<Button*> GetChildren() const { return children; }
    FORCEINLINE void Callback() { return event.Invoke(); }
    
public:
    Button();
    Button(String _title, Action _callback = Action(), String _shortcut = "", Array<Button*> _button = Array<Button*>());
    ~Button();

    bool operator==(const Button& _button) const
    {
        return _button.GetTitle() == title;
    }
    bool operator!=(const Button& _button) const
    {
        return _button.GetTitle() != title;
    }
    bool operator!() const
    {
        return !event.IsBound();
    }
};