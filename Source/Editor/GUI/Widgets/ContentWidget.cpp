#include "ContentWidget.h"
#include "../../../Core/Macros.h"

namespace fs = std::filesystem;

ContentWidget::ContentWidget(const String& _name, Window* _window) : PanelWidget(_name, _window)
{
    folderTexture = LoadTexture("Folder.png");
    fileTexture = LoadTexture("File.png");

    buttons = 
    {
        new Button("Add", [this]
        {
            cout << "Add" << endl;
        }),
        new Button("Import", [this]
        {
            cout << "Import" << endl;
        }),
        new Button("Save all", [this]
        {
            cout << "Save" << endl;
        })
    };
}

ContentWidget::~ContentWidget()
{
    folders.Empty();
}


void ContentWidget::Draw()
{
    Update();
    
    ImGui::SetNextWindowSize(ImVec2(800, 500));
    ImGui::Begin(name, &widgetStatus);

    const int _buttonsCount = buttons.Lenght();
    for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
    {
        Button* _button = buttons[_buttonIndex];
        if (!_button) continue;

        if (ImGui::Button(_button->GetTitle()))
        {
            _button->Callback();
        }
        ImGui::SameLine();
    }
        
    if (folders.Lenght() > 0)
    {
        DrawBreadcrumbTrail(folders[0]);

        DrawTreeFolders(folders[0]);
        // ImGui::SameLine();
        // DrawFiles(folders[0]);
    }

    ImGui::End();
}

void ContentWidget::Stop()
{
}


void ContentWidget::Update()
{
    folders.Empty();
    File* _file = new File("Content", PATH_CONTENT);
    RetrieveFiles(_file);
    folders.Add(_file);
}

void ContentWidget::RetrieveFiles(File*& _currentFile)
{
    for (const auto& _directoryEntry : fs::directory_iterator(_currentFile->GetPath()))
    {
        const String& _fileName = _directoryEntry.path().stem().string();
        const String& _filePath = _directoryEntry.path().string();
        File* _file = new File(_fileName, _filePath);
        
        if (_directoryEntry.is_regular_file())
        {
            _currentFile->AddFile(_file);
            continue;
        }
        
        RetrieveFiles(_file);
        _currentFile->AddFile(_file);
    }
}

void ContentWidget::DrawBreadcrumbTrail(File* _file) const
{
    ImGui::Text("DrawBreadcrumbTrail");
    
    /*Array<string> folders;
    const Folder* currentFolder = &_file;

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

        if (ImGui::Button(folderName)))
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

void ContentWidget::DrawTreeFolders(File* _file) const
{
    if (ImGui::TreeNode(_file->GetName()))
    {
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

        static int selection_mask = (1 << 2);
        int node_clicked = -1;

        Array<File*> _files = _file->GetFiles();
        const int _filesCount = _files.Lenght();
    
        for (int _fileIndex = 0; _fileIndex < _filesCount; _fileIndex++)
        {
            File* _currentFile = _files[_fileIndex];
            const String& _fileName = _currentFile->GetName();
            
            ImGuiTreeNodeFlags node_flags = base_flags;
            const bool is_selected = (selection_mask & (1 << _fileIndex)) != 0;
            
            if (is_selected)
                node_flags |= ImGuiTreeNodeFlags_Selected;
            
            bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)_fileIndex, node_flags, _fileName);
            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
            {
                node_clicked = _fileIndex;
            }
            if (node_open)
            {
                DrawTreeFolders(_currentFile);
                ImGui::TreePop();
            }
        }
        
        if (node_clicked != -1)
        {
            if (ImGui::GetIO().KeyCtrl)
                selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
            else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                selection_mask = (1 << node_clicked);           // Click to single-select
        }
        
        ImGui::TreePop();
    }

    // ImGui::TreePop();
    
    /*Array<Folder*> _files = _file->GetFiles();
    const int _filesCount = _files.Lenght();
    
    for (int _fileIndex = 0; _fileIndex < _filesCount; _fileIndex++)
    {
        const Folder* _file = _files[_fileIndex];
        if (!_file->IsFolder()) return;

        glBindTexture(GL_TEXTURE_2D, folderTexture);
        ImGui::Image(ImTextureID(folderTexture), ImVec2(25, 25));
        ImGui::SameLine();
        if (ImGui::TreeNode(_file->GetName()))
        {
            DrawFiles(_file);
            ImGui::TreePop();
        }
    }*/
}

void ContentWidget::DrawFiles(File* _file) const
{
    Array<File*> _files = _file->GetFiles();
    const int _filesCount = _files.Lenght();
    
    for (int _fileIndex = 0; _fileIndex < _filesCount; _fileIndex++)
    {
        File* _currentFile = _files[_fileIndex];
        const String& _fileName = _currentFile->GetName();
        
        if (!_currentFile->IsFolder())
        {
            glBindTexture(GL_TEXTURE_2D, fileTexture);
            ImGui::Image(ImTextureID(fileTexture), ImVec2(25, 25));
            ImGui::SameLine();
            ImGui::Text(_fileName);
            continue;
        }

        glBindTexture(GL_TEXTURE_2D, folderTexture);
        ImGui::Image(ImTextureID(folderTexture), ImVec2(25, 25));
        ImGui::SameLine();
        if (ImGui::TreeNode(_fileName))
        {
            DrawFiles(_currentFile);
            ImGui::TreePop();
        }
    }
}

//TODO move into Texture class
GLuint ContentWidget::LoadTexture(const String& _filename) const
{
    int width, height, channels;
    //stbi_set_flip_vertically_on_load(true); // invert image on load
    unsigned char* data = stbi_load(PATH_TEXTURES.ToString() + _filename, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << _filename << std::endl;
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
