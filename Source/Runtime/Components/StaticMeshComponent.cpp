#include "StaticMeshComponent.h"
#include "../Managers/CameraManager.h"
#include "../../Core/Common/Shader.h"
#include "../Managers/InputManager.h"

StaticMeshComponent::StaticMeshComponent(Actor* _owner) : Component(_owner)
{
	vertexArrayID = GLuint();

	// Shader
	programID = GLuint();
	vertexShaderPath = "StandardShading.vertexshader";
	fragmentShaderPath = "StandardShading.fragmentshader";

	// Matrix
	matrixID = GLuint();
	modelMatrix = mat4(1.0);
	modelMatrixID = GLuint();
	viewMatrix = mat4();
	viewMatrixID = GLuint();
	projectionMatrix = mat4();

	// Textures
	texture = GLuint();
	textureID = GLuint();

	// Model
	vertices = vector<vec3>();

	// VBO
	indices = vector<unsigned short>();
	indexed_vertices = vector<vec3>();
	indexed_uvs = vector<vec2>();
	indexed_normals = vector<vec3>();

	// Buffers
	vertexBuffer = GLuint();
	uvBuffer = GLuint();
	normalBuffer = GLuint();
	elementBuffer = GLuint();

	// Lights
	lightID = GLuint();
}
StaticMeshComponent::~StaticMeshComponent() = default;

void StaticMeshComponent::Start()
{
	SUPER::Start();
}
void StaticMeshComponent::Update(float _deltaTime)
{
	SUPER::Update(_deltaTime);

	/*
	// Display the mesh only if owner is into camera's frustum
	UShapeComponent* _shapeComponent = owner->GetComponent<UShapeComponent>();
	if (_shapeComponent && _shapeComponent->IsOnFrustum(Game::GameCamera()->GetFrustum(), owner) || !_shapeComponent)
	{
		ComputeMVPMatrix();
		ComputeShader();
		BindTextures();
		ComputeMatrix();
		ComputeVertices();
		DrawArrays();
	}*/

	ComputeMVPMatrix();
	ComputeShader();
	BindTextures();
	ComputeMatrix();
	ComputeVertices();
	DrawArrays();
	StopRender();
}
void StaticMeshComponent::Stop()
{
	SUPER::Stop();
	
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &vertexArrayID);
}

#pragma region TransformMethods

#pragma region AddMethods

void StaticMeshComponent::AddMeshLocation(const Vector3& _location)
{
	modelMatrix = translate(modelMatrix, vec3(_location.x, _location.y, _location.z));
}
void StaticMeshComponent::AddMeshRotation(const float _angle, const Vector3& _axis)
{
	modelMatrix = rotate(modelMatrix, radians(_angle), vec3(_axis.x, _axis.y, _axis.z));
}
void StaticMeshComponent::AddMeshScale(const Vector3& _scale)
{
	modelMatrix = scale(modelMatrix, vec3(_scale.x, _scale.y, _scale.z));
}

#pragma endregion

#pragma region SetMethods

void StaticMeshComponent::SetMeshLocation(const Vector3& _location)
{
	modelMatrix[3][0] = _location.x;
	modelMatrix[3][1] = _location.y;
	modelMatrix[3][2] = _location.z;
}
void StaticMeshComponent::SetMeshLocationAndRotation(const Vector3& _location, const Rotator& _rotation)
{
	SetMeshLocation(_location);
	SetMeshRotation(_rotation);
}
void StaticMeshComponent::SetMeshRotation(const Rotator& _rotation)
{
	modelMatrix[0][3] = _rotation.pitch;
	modelMatrix[1][3] = _rotation.roll;
	modelMatrix[2][3] = _rotation.yaw;
}
void StaticMeshComponent::SetMeshScale(const Vector3& _scale)
{
	modelMatrix[0][0] = _scale.x;
	modelMatrix[1][1] = _scale.y;
	modelMatrix[2][2] = _scale.z;
}

#pragma endregion

#pragma endregion

#pragma region InitMethods

void StaticMeshComponent::Init(const String& _objPath, const String& _texturePath, bool _useCustomMethod)
{
	if (!_texturePath || !_objPath) return;

	InitVertex();
	InitShaders();
	InitMatrix();
	InitTextures(_texturePath, _useCustomMethod);
	LoadModel(_objPath);
	InitBuffers();
	InitLights();
}
void StaticMeshComponent::InitVertex()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}
void StaticMeshComponent::InitShaders()
{
	const String _path = PATH_SHADERS;
	programID = TShader::LoadShaders(_path + vertexShaderPath, _path + fragmentShaderPath);
}
void StaticMeshComponent::InitMatrix()
{
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "M");
	modelMatrixID = glGetUniformLocation(programID, "V");
}
void StaticMeshComponent::InitTextures(const String& _texturePath, bool _useCustomMethod)
{
	char _fullTexturePath[100 * sizeof(char)];
	const String _path = PATH_TEXTURES;
	strcpy_s(_fullTexturePath, _path + _texturePath);

	if (!_useCustomMethod)
	{
		strcat_s(_fullTexturePath, sizeof(_fullTexturePath), ".DDS");
		texture = loadDDS(_fullTexturePath);
	}
	
	else
	{
		strcat_s(_fullTexturePath, sizeof(_fullTexturePath), ".bmp");
		texture = loadBMP_custom(_fullTexturePath);
	}

	textureID = glGetUniformLocation(programID, "myTextureSampler");
}
void StaticMeshComponent::LoadModel(const String& _objPath)
{
	vector<vec2> _uvs;
	vector<vec3> _normals;
	const String _path = PATH_MODELS;
	bool _res = loadOBJ(_path + _objPath, vertices, _uvs, _normals);
	indexVBO(vertices, _uvs, _normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
}
void StaticMeshComponent::InitBuffers()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(vec3), &indexed_normals[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}
void StaticMeshComponent::InitLights()
{
	glUseProgram(programID);
	lightID = glGetUniformLocation(programID, "LightPosition_worldspace");
}

#pragma endregion

#pragma region UpdateMethods

void StaticMeshComponent::ComputeMVPMatrix()
{
	projectionMatrix = CameraManager::Instance()->GetProjectionMatrix();
	viewMatrix = CameraManager::Instance()->GetViewMatrix();
}
void StaticMeshComponent::ComputeShader() const
{
	glUseProgram(programID);
	const vec3 _lightPos = vec3(4, 4, 4);
	glUniform3f(lightID, _lightPos.x, _lightPos.y, _lightPos.z);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
}
void StaticMeshComponent::BindTextures() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);
}
void StaticMeshComponent::ComputeMatrix()
{
	mat4 _mvp = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &_mvp[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
}
void StaticMeshComponent::ComputeVertices() const
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
}
void StaticMeshComponent::DrawArrays() const
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_SHORT, nullptr);
}
void StaticMeshComponent::StopRender() const
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

#pragma endregion