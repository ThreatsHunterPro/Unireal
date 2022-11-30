#pragma once

#include "Macros.h"

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

class CameraManager
{
	// Values
	static vec3 position;
	float pitch;
	float yaw;
	float roll;
	float angle;
	float speed;
	float sensivity;
	Vector3 targetLocation;

	// FoV
	static float fov;
	float minFov;
	float maxFov;

	// Ranges
	static float nearRange;
	static float farRange;
	static Frustum frustum;

	// Vectors
	static vec3 forward;
	static vec3 right;
	static vec3 up;

	static int windowWidth;
	static int windowHeight;

	//TODO make a static getter for a TimerManager
	float deltaTime;

public:
	FORCEINLINE static const mat4& GetProjectionMatrix(bool _inPerspective = true)
	{
		return _inPerspective ? perspective(radians(fov), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), nearRange, 150.0f)
							  : ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearRange, farRange);
	}
	FORCEINLINE static const mat4& GetViewMatrix() { return lookAt(position, position + forward /*targetLocation*/, up); }
	FORCEINLINE static const Frustum& GetFrustum() { return frustum; }
	FORCEINLINE static const vec3& GetForward() { return forward; }
	
public:
	CameraManager(Vector2 _windowSize);
	~CameraManager();

	void Start();
	void Update(float _deltaTime);
	void Stop();

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
	void UpdateCameraVectors();
	void UpdateFrustum();
};