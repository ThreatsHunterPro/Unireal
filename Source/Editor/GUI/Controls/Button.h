#pragma once
#include "../../../Core/Macros.h"

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
    Button(const String& _title, Action _callback = nullptr, const String& _shortcut = "", const Array<Button*>& _button = Array<Button*>());
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