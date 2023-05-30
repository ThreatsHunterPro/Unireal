#pragma once
#include "Manager.h"
#include "../../Editor/GUI/Windows/Window.h"

class InputManager : public Manager<InputManager>
{
    GLFWwindow* window;
    Vector2 previousCursorPos;
    
public:
    InputManager();
    ~InputManager();

    void Start(GLFWwindow* _window);
    void Update();
    void Stop() const;

private:
    void InitControls() const;
    void ProcessMouse();
    void ProcessInputs() const;
};
