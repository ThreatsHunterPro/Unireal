#include "ContentWidget.h"
#include "../../../Core/Macros.h"
#include <../../../Core/Common/stb_image.h>

namespace fs = std::filesystem;

ContentWidget::ContentWidget(string _name, Window* _window) : PanelWidget(_name, _window)
{
    folderTexture = LoadTexture("Folder.png");
    fileTexture = LoadTexture("File.png");
}
ContentWidget::~ContentWidget()
{
    folders.Empty();
}

void ContentWidget::Draw()
{
    Update();
    
    ImGui::SetNextWindowSize(ImVec2(800, 500));
    ImGui::Begin(name.c_str(), nullptr);

    if (folders.Lenght() > 0)
    {
        DrawBreadcrumbTrail(folders[0]);
        DrawFiles(folders[0]);
    }

    ImGui::End();
}

void ContentWidget::Stop()
{
}

void ContentWidget::DrawBreadcrumbTrail(const Folder& _folder) const
{
    /*Array<string> folders;
    const Folder* currentFolder = &_folder;

    // Traverse up the folder hierarchy and add each folder name to the list
    while (currentFolder != nullptr)
    {
        folders.push_back(currentFolder->Name);
        currentFolder = currentFolder->Parent;
    }

    // Reverse the list so that the root folder is first
    std::reverse(folders.begin(), folders.end());

    // Draw the breadcrumb trail using clickable buttons for each folder
    for (int i = 0; i < folders.size(); i++)
    {
        const std::string& folderName = folders[i];

        if (i != 0)
        {
            ImGui::SameLine();
            ImGui::Text("/");
            ImGui::SameLine();
        }

        if (ImGui::Button(folderName.c_str()))
        {
            // Navigate to the clicked folder
            Folder* clickedFolder = folder.FindSubfolderByName(folderName);
            if (clickedFolder != nullptr)
            {
                folders.Empty();
                RetrieveFiles(*clickedFolder);
            }
        }
    }*/
}
void ContentWidget::DrawFiles(const Folder& _folder) const
{
    const int _filesCount = _folder.Files.Lenght();
    for (int _fileIndex = 0; _fileIndex < _filesCount; _fileIndex++)
    {
        Folder _file = _folder.Files[_fileIndex];
        
        if (!_file.IsFolder())
        {
            glBindTexture(GL_TEXTURE_2D, fileTexture);
            ImGui::Image((ImTextureID)fileTexture, ImVec2(25, 25));
            ImGui::SameLine();
            ImGui::Text(_file.Name.c_str());
            continue;
        }

        glBindTexture(GL_TEXTURE_2D, folderTexture);
        ImGui::Image((ImTextureID)folderTexture, ImVec2(25, 25));
        ImGui::SameLine();
        if (ImGui::TreeNode(_file.Name.c_str()))
        {
            DrawFiles(_file);
            ImGui::TreePop();
        }
    }
}

void ContentWidget::Update()
{
    folders.Empty();
    Folder _folder("Content", PATH_CONTENT);
    RetrieveFiles(_folder);
    folders.Add(_folder);
}
void ContentWidget::RetrieveFiles(Folder& _currentFolder)
{
    for (const auto& _file : fs::directory_iterator(_currentFolder.Path))
    {
        const string& _fileName = _file.path().stem().string();
        const string& _filePath = _file.path().string();
        Folder _folder = Folder(_fileName, _filePath);
        
        if (_file.is_regular_file())
        {
            _currentFolder.Files.Add(_folder);
            continue;
        }
        
        RetrieveFiles(_folder);
        _currentFolder.Files.Add(_folder);
    }
}

//TODO move into Texture class
GLuint ContentWidget::LoadTexture(const char* filename) const
{
    int width, height, channels;
    //stbi_set_flip_vertically_on_load(true); // invert image on load
    unsigned char* data = stbi_load((PATH_TEXTURES + filename).c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    const GLenum format = channels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return textureID;
}
