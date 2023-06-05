#pragma once
#include "../../../Core/Macros.h"

class Window;

class Widget
{
protected:
    String name;
    Window* window;

public:
    FORCEINLINE void SetName(const String& _name) { name = _name; }
    FORCEINLINE String GetName() const { return name; }
    
public:
    Widget(String _name, Window* _window);
    virtual ~Widget();

public:
    virtual void Draw() = 0;
    virtual void Stop() = 0;
};