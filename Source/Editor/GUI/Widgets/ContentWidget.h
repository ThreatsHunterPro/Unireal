#pragma once
#include "PanelWidget.h"
#include "../../../Core/Macros.h"

class ContentWidget : public PanelWidget
{
    class Folder 
    {
    public:
        string Name;
        string Path;
        Array<Folder> Files = Array<Folder>();

        FORCEINLINE bool IsFolder() const { return Files.Lenght() > 0; }
        
        Folder() = default;
        Folder(const string& _name, const string& _path)
        {
            Name = _name;
            Path = _path;
        }
        Folder(const Folder& other)
        {
            Name = other.Name;
            Path = other.Path;
            Files = other.Files;
        }
        
        Folder& operator=(const Folder& other)
        {
            Name = other.Name;
            Path = other.Path;
            Files = other.Files;
            return *this;
        }
    };

    GLuint folderTexture;
    GLuint fileTexture;
    Array<Folder> folders;
    
public:
    ContentWidget(string _name, Window* _window);
    ~ContentWidget() override;

private:
    void Update();
    void RetrieveFiles(Folder& _currentFolder);
    //TODO move
    GLuint LoadTexture(const char* filename) const;

public:
    // void Awake() override;
    void Draw() override;
    void Stop() override;
    void DrawBreadcrumbTrail(const Folder& folder) const;
    void DrawFiles(const Folder& _folder) const;
};
