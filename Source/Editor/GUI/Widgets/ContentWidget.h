#pragma once
#include "PanelWidget.h"
#include "../../../Core/Macros.h"

class ContentWidget : public PanelWidget
{
    class Folder 
    {
    public:
        String Name;
        const char* Path;
        Array<Folder> Files = Array<Folder>();

        FORCEINLINE bool IsFolder() const { return Files.Lenght() > 0; }
        
        Folder() = default;
        Folder(const String& _name, const String& _path)
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
    ContentWidget(String _name, Window* _window);
    ~ContentWidget() override;

private:
    void Update();
    void RetrieveFiles(Folder& _currentFolder);
    //TODO move
    GLuint LoadTexture(String _filename) const;

public:
    // void Awake() override;
    void Draw() override;
    void Stop() override;
    void DrawBreadcrumbTrail(const Folder& folder) const;
    void DrawFiles(const Folder& _folder) const;
};
