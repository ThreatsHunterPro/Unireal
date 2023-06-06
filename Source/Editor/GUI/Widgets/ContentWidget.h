#pragma once
#include "PanelWidget.h"
#include "../Controls/Button.h"
#include "../../../Core/Macros.h"

class ContentWidget : public PanelWidget
{
    class File 
    {
        String name;
        const char* path;
        Array<File*> files;

    public:
        FORCEINLINE bool IsFolder() const { return files.Lenght() > 0; }
        FORCEINLINE String GetName() const { return name; }
        FORCEINLINE const char* GetPath() const { return path; }
        FORCEINLINE Array<File*> GetFiles() { return files; }
        FORCEINLINE void AddFile(File* _file) { files.Add(_file); }
        
    public:
        File(const String& _name, const char* _path)
        {
            name = _name;
            path = _path;
            files = Array<File*>();
        }
        File(const File* _other)
        {
            name = _other->name;
            path = _other->path;
            files = _other->files;
        }
        
    public:
        File& operator=(const File* _other)
        {
            name = _other->name;
            path = _other->path;
            files = _other->files;
            return *this;
        }
    };

    Array<Button*> buttons;
    GLuint folderTexture;
    GLuint fileTexture;
    Array<File*> folders;
    
public:
    ContentWidget(const String& _name, Window* _window);
    ~ContentWidget() override;

public:
    void Draw() override;
    void Stop() override;
    
private:
    void Update();
    void RetrieveFiles(File*& _currentFolder);
    void DrawBreadcrumbTrail(File* folder) const;
    void DrawTreeFolders(File* _folder) const;
    void DrawFiles(File* _folder) const;
    GLuint LoadTexture(const String& _filename) const;
};
