#pragma once
#include "../../../Core/Macros.h"

class Button
{
    string title;
    Event<> event;
    Array<Button> children;
    
public:
    FORCEINLINE const char* GetTitle() const { return title.c_str(); }
    FORCEINLINE Array<Button> GetChildren() const { return children; }
    FORCEINLINE void Callback() { return event.Invoke(); }
    
public:
    Button();
    Button(const char* _title, Action _callback = Action(), Array<Button> _button = Array<Button>());
    ~Button();
};