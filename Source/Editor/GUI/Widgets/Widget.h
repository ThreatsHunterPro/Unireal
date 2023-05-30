#pragma once
#include "../../../Core/Macros.h"

class Window;

class Widget
{
protected:
    string name;
    Window* window;

public:
    FORCEINLINE void SetName(const string& _name) { name = _name; }
    FORCEINLINE string GetName() const { return name; }
    
public:
    Widget(string _name, Window* _window);
    virtual ~Widget();

public:
    virtual void Draw() = 0;
    virtual void Stop() = 0;
};