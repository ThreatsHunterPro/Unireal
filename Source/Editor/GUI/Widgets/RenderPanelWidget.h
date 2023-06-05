#pragma once
#include "PanelWidget.h"
#include "../Windows/Window.h"

class RenderPanelWidget : public PanelWidget
{
    GLuint sceneTexture;
    GLuint sceneFramebuffer;
    GLuint sceneDepthTexture;
    // GLfloat* border_color;
    
public:
    RenderPanelWidget(String _name, Window* _window);
    ~RenderPanelWidget() override;

public:
    void Draw() override;
    void Stop() override;
};