#include "EditorBarWidget.h"
#include "RenderPanelWidget.h"
#include "../../../Runtime/World.h"

EditorBarWidget::EditorBarWidget(string _name, Window* _window) : Widget(_name, _window)
{
    menus = 
    {
        Menu("File",
            {
                Button("New scene", [this] { ExecuteCallback("New scene"); }),
                Button("Open scene", [this] { ExecuteCallback("Open scene"); }),
                Button("Save scene", [this] { ExecuteCallback("Save scene"); }),
                Button("New project", [this] { ExecuteCallback("New project"); }),
                Button("Open project", [this] { ExecuteCallback("Open project"); }),
                Button("Save project", [this] { ExecuteCallback("Save project"); }),
                Button("Build settings", [this] { ExecuteCallback("Build settings"); }),
                Button("Build & Run", [this] { ExecuteCallback("Build & Run"); }),
                Button("Exit", [this] { ExecuteCallback("Exit"); })
            }),
        
        Menu("Edit", { Button("Preferences") }),
        Menu("Window",
            {
                Button("Scene", [_window]
                {
                    _window->AddWidget(new RenderPanelWidget("Scene", _window));
                }),
                Button("Game", [_window]
                {
                    _window->AddWidget(new RenderPanelWidget("Game", _window));
                }),
                Button("Content", [_window] { _window->AddWidget(new ContentWidget("Content", _window)); }),
                Button("Hierarchy", [this] { ExecuteCallback("Hierarchy"); }),
                Button("Inspector", [this] { ExecuteCallback("Inspector"); }),
                Button("Console", [this] { ExecuteCallback("Console"); })
            }),
        Menu("Actors",
            {
                Button("Cube", [this]
                {
                   cout << "Spawn Cube" << endl;
                   World::Instance()->SpawnActor("Boule", "Boule.obj", "uvmap", false, Transform(Vector3(-5.0f, 0.0f, 0.0f), Rotator(0.0f), Vector3(1.0f)));
                }),
                Button("Sphere", [this]
                {
                    cout << "Spawn sphere" << endl;
                    World::Instance()->SpawnActor("Boule", "Boule.obj", "uvmap", false, Transform(Vector3(0.0f), Rotator(0.0f), Vector3(1.0f)));
                }),
                Button("Cylinder", [this]
                {
                    cout << "Spawn cylinder" << endl;
                    World::Instance()->SpawnActor("Singe1", "suzanne.obj", "uvmap", false, Transform(Vector3(5.0f, 0.0f, 0.0f), Rotator(0.0f), Vector3(3.0f)));
                })
            })
    };
}
EditorBarWidget::~EditorBarWidget()
{
    menus.Empty();
}

void EditorBarWidget::Draw()
{
    ImGuiStyle& _style = ImGui::GetStyle();
    ImVec4* _colors = _style.Colors;
    _colors[ImGuiCol_Button] = ImVec4(0.26f, 0.26f, 0.26f, 1.0f);
    _colors[ImGuiCol_ButtonHovered] = ImVec4(0.36f, 0.36f, 0.36f, 1.0f);
    
    ImGui::SetNextWindowSize(ImVec2(1800, 40));
    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);
	
    if (ImGui::BeginMenuBar())
    {
        const int _menusCount = menus.Lenght();
        for (int _menuIndex = 0; _menuIndex < _menusCount; _menuIndex++)
        {
            Menu _menu = menus[_menuIndex];
            
            if (ImGui::BeginMenu(_menu.Title.c_str()))
            {
                Array<Button> _buttons = _menu.Buttons;
                const int _buttonsCount = _buttons.Lenght();
                
                for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
                {
                    Button _button = _buttons[_buttonIndex];
                    if (ImGui::MenuItem(_button.GetTitle()))
                    {
                        _button.Callback();
                    }
                }
                
                ImGui::EndMenu();
            }
            
            ImGui::SameLine();
        }
        
        ImGui::EndMenuBar();
    }
    
    ImGui::End();
}
void EditorBarWidget::ExecuteCallback(string _methodName) const
{
    cout << _methodName << endl;
}

void EditorBarWidget::Stop()
{
    
}
