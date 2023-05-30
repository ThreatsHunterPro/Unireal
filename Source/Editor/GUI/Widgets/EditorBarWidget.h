#pragma once
#include "Widget.h"
#include "../Controls/Button.h"
#include "../../../Core/Macros.h"

class EditorBarWidget : public Widget
{
    struct Menu
    {
        string Title;
        Array<Button> Buttons;

        Menu()
        {
            Title = "";
            Buttons = Array<Button>();
        }
        Menu(string _title, Array<Button> _buttons)
        {
            Title = _title;
            Buttons = _buttons;
        }
    };
    
    Array<Menu> menus;
    
public:
    EditorBarWidget(string _name, Window* _window);
    ~EditorBarWidget() override;

public:
    void Draw() override;
    void ExecuteCallback(string _methodName) const;
    void Stop() override;
};