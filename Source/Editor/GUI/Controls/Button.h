#pragma once
#include "../../../Core/Macros.h"

class Button;

struct Menu
{
    string Title;
    Array<Button> Buttons;
    Array<int> Separators;

    Menu()
    {
        Title = "";
        Buttons = Array<Button>();
    }
    Menu(string _title, Array<Button> _buttons, Array<int> _separators = Array<int>())
    {
        Title = _title;
        Buttons = _buttons;
        Separators = _separators;
    }
};

class Button
{
    string title;
    string shortcut;
    Event<> event;
    Array<Button> children;
    
public:
    FORCEINLINE const char* GetTitle() const { return title.c_str(); }
    FORCEINLINE const char* GetShortcut() const { return shortcut.c_str(); }
    FORCEINLINE Array<Button> GetChildren() const { return children; }
    FORCEINLINE void Callback() { return event.Invoke(); }
    
public:
    Button();
    Button(const char* _title, Action _callback = Action(), const char* _shortcut = "", Array<Button> _button = Array<Button>());
    ~Button();

    bool operator==(const Button& _button) const
    {
        return _button == nullptr;
    }
    bool operator!=(const Button& _button) const
    {
        return _button != nullptr;
    }
    bool operator!() const
    {
        return !event.IsBound();
    }
};

class ParentButton : public Button
{
    Array<Button> children;

public:
    FORCEINLINE Array<Button> GetChildren() const { return children; } 

public:
    ParentButton();
    ParentButton(const char* _title, Action _callback = Action(), Array<Button> _button = Array<Button>());
    ~ParentButton();
};