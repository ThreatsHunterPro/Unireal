#pragma once
#include "Component.h"
#include "Actor.h"

class StaticMeshComponent : Component
{
private:
	// Vertex
	GLuint vertexArrayID;

	// Shader
	GLuint programID;
	const char* vertexShaderPath;
	const char* fragmentShaderPath;

	// Matrix
	GLuint matrixID;
	mat4 modelMatrix;
	GLuint modelMatrixID;
	mat4 viewMatrix;
	GLuint viewMatrixID;
	mat4 projectionMatrix;

	// Textures
	GLuint texture;
	GLuint textureID;

	// Model
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

	// VBO
	vector<unsigned short> indices;
	vector<vec3> indexed_vertices;
	vector<vec2> indexed_uvs;
	vector<vec3> indexed_normals;

	// Buffers
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

	// Lights
	GLuint lightID;

public:
	StaticMeshComponent(Actor* _owner);
	~StaticMeshComponent();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void Stop() override;

	void Init(const char* _objPath, char* _texturePath, bool _useCustomMethod = true);

	#pragma region TransformMethods

	#pragma region AddMethods

	void AddMeshLocation(const Vector3& _location);
	void AddMeshRotation(const float _angle, const Vector3& _rotation);
	void AddMeshScale(const Vector3& _scale);

	#pragma endregion

	#pragma region SetMethods

	void SetMeshLocation(const Vector3& _location);
	void SetMeshLocationAndRotation(const Vector3& _location, const Rotator& _rotation);
	void SetMeshRotation(const Rotator& _rotation);
	void SetMeshScale(const Vector3& _scale);

	#pragma endregion

	#pragma region GetMethods

	FORCEINLINE const mat4& GetModelMatrix() const { return modelMatrix; }
	FORCEINLINE Vector3 GetForward() const { return Vector3(-modelMatrix[2][0], -modelMatrix[2][1], -modelMatrix[2][2]); }
	FORCEINLINE Vector3 GetRight() const { return Vector3(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]); }
	FORCEINLINE Vector3 GetUp() const { return Vector3(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]); }
	FORCEINLINE Vector3 GetMeshPosition() const { return Vector3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]); }
	FORCEINLINE Rotator GetMeshRotation() const { return Rotator(modelMatrix[0][3], modelMatrix[1][3], modelMatrix[2][3]); }
	FORCEINLINE Vector3 GetMeshScale() const { return vec3(length(GetRight()), length(GetUp()), length(GetForward() * -1)); }

	#pragma endregion

	#pragma endregion

private:

	#pragma region InitMethods

	void InitVertex();
	void InitShaders();
	void InitMatrix();
	void InitTextures(char* _texturePath, bool _useCustomMethod = true);
	void LoadModel(const char* _objPath);
	void InitBuffers();
	void InitLights();

	#pragma endregion

	#pragma region UpdateMethods

	void ComputeMVPMatrix();
	void ComputeShader() const;
	void BindTextures() const;
	void ComputeMatrix();
	void ComputeVertices() const;
	void DrawArrays() const;

	#pragma endregion
};