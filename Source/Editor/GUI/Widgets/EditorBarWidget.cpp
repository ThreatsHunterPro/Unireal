#include "EditorBarWidget.h"

#include "ConsoleWidget.h"
#include "RenderPanelWidget.h"
#include "../../../Runtime/World.h"

EditorBarWidget::EditorBarWidget(const String& _name, Window* _window) : Widget(_name, _window)
{
    menus = 
    {
        Menu("File",
            {
                new Button("New scene", [this] { ExecuteCallback("New scene"); }),
                new Button("Open scene", [this] { ExecuteCallback("Open scene"); }),
                new Button("Save scene", [this] { ExecuteCallback("Save scene"); }),
                new Button("New project", [this] { ExecuteCallback("New project"); }),
                new Button("Open project", [this] { ExecuteCallback("Open project"); }),
                new Button("Save project", [this] { ExecuteCallback("Save project"); }),
                new Button("Build settings", [this] { ExecuteCallback("Build settings"); }),
                new Button("Build & Run", [this] { ExecuteCallback("Build & Run"); }),
                new Button("Exit", [this] { ExecuteCallback("Exit"); }, "Alf + F4")
            },
            { 3, 6}
            ),
        
        Menu("Edit", { new Button("Preferences") }),
        Menu("Window",
            {
                new Button("Scene", [_window]
                {
                    _window->AddWidget(new RenderPanelWidget("Scene", _window));
                }),
                new Button("Game", [_window]
                {
                    _window->AddWidget(new RenderPanelWidget("Game", _window));
                }),
                new Button("Content", [_window] { _window->AddWidget(new ContentWidget("Content", _window)); }),
                new Button("Hierarchy", [this] { ExecuteCallback("Hierarchy"); }),
                new Button("Inspector", [this] { ExecuteCallback("Inspector"); }),
                new Button("Console", [_window]
                {
                    _window->AddWidget(new ConsoleWidget("Console", _window));
                })
            }),
        Menu("Actors",
            {
                new Button("Cube", [this]
                {
                   cout << "Spawn Cube" << endl;
                   World::Instance()->SpawnActor("Boule", "Boule.obj", "uvmap", false, Transform(Vector3(-5.0f, 0.0f, 0.0f), Rotator(0.0f), Vector3(1.0f)));
                }),
                new Button("Sphere", [this]
                {
                    cout << "Spawn sphere" << endl;
                    World::Instance()->SpawnActor("Boule", "Boule.obj", "uvmap", false, Transform(Vector3(0.0f), Rotator(0.0f), Vector3(1.0f)));
                }),
                new Button("Cylinder", [this]
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
    if (ImGui::BeginMainMenuBar())
    {
        const int _menusCount = menus.Lenght();
        for (int _menuIndex = 0; _menuIndex < _menusCount; _menuIndex++)
        {
            Menu _menu = menus[_menuIndex];
            
            if (ImGui::BeginMenu(_menu.Title))
            {
                Array<Button*> _buttons = _menu.Buttons;
                const int _buttonsCount = _buttons.Lenght();
                
                for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
                {
                    if (_menu.Separators.Contains(_buttonIndex))
                    {
                        ImGui::Separator();
                    }
                    
                    Button* _button = _buttons[_buttonIndex];
                    if (ImGui::MenuItem(_button->GetTitle(), _button->GetShortcut()))
                    {
                        _button->Callback();
                    }
                }
                
                ImGui::EndMenu();
            }
            
            ImGui::SameLine();
        }
        
        ImGui::EndMainMenuBar();
    }
}
void EditorBarWidget::Stop()
{
    
}

void EditorBarWidget::ExecuteCallback(const String& _methodName) const
{
    cout << _methodName << endl;
}