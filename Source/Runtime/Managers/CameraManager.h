#pragma once
#include "Manager.h"
#include "../../Core/Macros.h"

class TShader;

struct Plan
{
	vec3 normal;
	float distance;

	Plan()
	{
		normal = { 0.0f, 1.0f, 0.0f };
		distance = 0.0f;
	}
	Plan(const vec3& _plan1, const vec3& _plan2)
	{
		normal = normalize(_plan2);
		distance = dot(normal, _plan1);
	}

	FORCEINLINE float GetSignedDistanceToPlan(const vec3& _point) const
	{
		return dot(normal, _point) - distance;
	}
};

struct Frustum
{
	Plan topFace;
	Plan bottomFace;

	Plan rightFace;
	Plan leftFace;

	Plan farFace;
	Plan nearFace;
};

class CameraManager : public Manager<CameraManager>
{
	// Values
	Vector3 position;
	float pitch;
	float yaw;
	float roll;
	float angle;
	float speed;
	float sensivity;
	Vector3 targetLocation;

	// FoV
	float fov;
	float minFov;
	float maxFov;

	// Ranges
	float nearRange;
	float farRange;
	Frustum frustum;

	// Vectors
	vec3 forward;
	vec3 right;
	vec3 up;

	int windowWidth;
	int windowHeight;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	
	TShader* DebugShader;
	
public:
	FORCEINLINE const mat4& GetProjectionMatrix(bool _inPerspective = true)
	{
		if (_inPerspective)
		{
			return projectionMatrix = perspective(radians(fov), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), nearRange, 100.0f);
		}

		return projectionMatrix = ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearRange, farRange);
	}
	FORCEINLINE const mat4& GetViewMatrix()
	{
		return viewMatrix = lookAt(position.ToVec3(), position.ToVec3() + forward, up);
	}
	FORCEINLINE const Frustum& GetFrustum() const { return frustum; }
	FORCEINLINE const Vector3& GetForward() const { return forward; }
	FORCEINLINE void DrawLine(const Vector3& _start, const Vector3& _end, const vec4& _color, const TShader& _shader) const
	{
		unsigned int _vao, _vbo;
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		const Vector3 _vertices[] = {_start, _end};
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		_shader.Use();
		_shader.SetVec4("uColor", _color);
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
		
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
	}
	FORCEINLINE void DrawGrid(float _height, int _size, vec4 _color, const TShader& _shader) const
	{
		constexpr float _step = 10;
		const float _gap = std::roundf(std::abs(_height) / _step) + 1;
		for (int _index = -_size; _index <= _size; _index++)
		{
			DrawLine(vec3(_index, 0, -_size) * _gap, vec3(_index, 0, _size) * _gap, _color, _shader);
			DrawLine(vec3(-_size, 0, _index) * _gap, vec3(_size, 0, _index) * _gap, _color, _shader);
		}
	}
	
public:
	CameraManager();
	~CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	void Start();
	void Update();
	void Stop() const;
	void Debug() const;

	void MoveForward(float _forwardValue);
	void MoveRight(float _rightValue);
	void MoveUp(float _upValue);

	void MovePitch(float _pitchValue);
	void MoveYaw(float _yawValue);
	void MoveRoll(float _rollValue);

	void RotateAround(float _direction);
	void Zoom(float _zoomOffset);

	void SetTargetLocation(const Vector3& _targetLocation);

	//void SetTarget(Actor* _target);

private:
	void InitDepth();
	void UpdateFrustum();
	
public:
	void UpdateCameraVectors();
};