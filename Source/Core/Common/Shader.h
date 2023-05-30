#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Macros.h"
#include <string>

class TShader
{
protected:
    unsigned int id;

public:
    TShader() = default;
    TShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
    virtual ~TShader();

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const std::string& name, const glm::mat3& mat) const;
    
private:
    void CheckCompileErrors(GLuint shader, std::string type) const;
public:
    void Use() const;
    unsigned int ID() const;
    static GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
};

class TComputeShader : public TShader
{
public:
    TComputeShader() = default;
    TComputeShader(const std::string& computePath);
    void Dispatch(unsigned int _x, unsigned int _y = 1, unsigned int _z = 1) const;
};