#include "RenderPanelWidget.h"
#include "../../../Core/Macros.h"
#include "../../../Runtime/World.h"

RenderPanelWidget::RenderPanelWidget(String _name, Window* _window) : PanelWidget(_name, _window)
{
    sceneTexture = 0;
    sceneFramebuffer = 0;
    sceneDepthTexture = 0;
}

RenderPanelWidget::~RenderPanelWidget()
{
    
}

void RenderPanelWidget::Draw()
{
    // const ImVec2& panelSize = ImGui::GetContentRegionAvail();
    const ImVec2& panelSize = ImVec2(300.0f, 300.0f);
    
    // Generate an OpenGL framebuffer and texture for rendering the scene
    glGenFramebuffers(1, &sceneFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFramebuffer);
   
    // Generate a texture for the color buffer
    glGenTextures(1, &sceneTexture);
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, panelSize.x, panelSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate a texture for the depth buffer
    glGenTextures(1, &sceneDepthTexture);
    glBindTexture(GL_TEXTURE_2D, sceneDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, panelSize.x, panelSize.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
   
    // Attach the color and depth textures to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, sceneDepthTexture, 0);

    // Check that the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Error: Framebuffer is not complete!" << std::endl;
        return;
    }

    glClearTexImage(sceneTexture, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glClearTexImage(sceneDepthTexture, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);

    // Draw static meshes to the framebuffer
    const int numActors = World::Instance()->actors.Lenght();
    for (int i = 0; i < numActors; ++i)
    {
        Actor* actor = World::Instance()->actors[i];
        if (!actor) continue;
        actor->Update(1.0f);
    }

    // Render the framebuffer texture with ImGui
    ImGui::Begin(name);
    ImGui::Text("coucou");
    ImGui::Image((void*)(intptr_t)sceneTexture, panelSize, ImVec2(panelSize.x, panelSize.y));
    ImGui::End();

    glDeleteTextures(1, &sceneTexture);
    glDeleteTextures(1, &sceneDepthTexture);
    glDeleteFramebuffers(1, &sceneFramebuffer);
}

void RenderPanelWidget::Stop()
{
    // Clean up the OpenGL resources
    glDeleteTextures(1, &sceneTexture);
    glDeleteTextures(1, &sceneDepthTexture);
    glDeleteFramebuffers(1, &sceneFramebuffer);
}
