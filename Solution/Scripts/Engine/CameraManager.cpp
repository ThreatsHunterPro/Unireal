#include "CameraManager.h"

CameraManager::CameraManager(Vector2 _windowSize)
{
	position = vec3(-5.0f, 1.0f, 0.0f);
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	angle = 0.0f;
	speed = 10.0f;
	sensivity = 0.05f;
	targetLocation = Vector3();

	fov = 45.0f;
	minFov = 0.1f;
	maxFov = 100.0f;

	nearRange = 0.5f;
	farRange = 45.0f;

	frustum = Frustum();

	forward = vec3(0.0f, 0.0f, -1.0f);
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);


	windowWidth = static_cast<int>(_windowSize.x);
	windowHeight = static_cast<int>(_windowSize.y);
}
CameraManager::~CameraManager()
{

}

void CameraManager::Start()
{
	InitDepth();
}
void CameraManager::Update(float _deltaTime)
{
	deltaTime = _deltaTime;
	UpdateCameraVectors();
	UpdateFrustum();
}
void CameraManager::Stop()
{

}

// Standard
void CameraManager::MoveForward(float _verticalValue)
{
	const float _value = clamp(_verticalValue, -1.0f, 1.0f);
	position += forward * _value * deltaTime * speed;
}
void CameraManager::MoveRight(float _horizontalValue)
{
	const float _value = clamp(_horizontalValue, -1.0f, 1.0f);
	position += right * _value * deltaTime * speed;
}
void CameraManager::MoveUp(float _upValue)
{
	const float _value = clamp(_upValue, -1.0f, 1.0f);
	position += up * _value * deltaTime * speed;
}

// Mouse
void CameraManager::MoveYaw(float _yawValue)
{
	yaw -= sensivity * _yawValue;

	/*if (yaw >= 360.0f)
		yaw = 0.0f;

	else if (yaw < 0.0f)
		yaw = 360.0f;*/
}
void CameraManager::MovePitch(float _pitchValue)
{
	pitch += sensivity * _pitchValue;
	
	/*if (pitch >= 90.0f)
		pitch = 90.0f;

	else if (pitch < 0.0f)
		pitch = 0.0f;*/
}
void CameraManager::MoveRoll(float _rollValue)
{
	roll += sensivity * _rollValue;

	if (roll >= 360.0f)
		roll = 0.0f;

	else if (roll < 0.0f)
		roll = 360.0f;
}

// Other
void CameraManager::RotateAround(float _direction)
{
	const float _value = clamp(_direction, -1.0f, 1.0f);
	angle += deltaTime * _value * speed / 10;

	if (angle >= 360.0f)
		angle = 0.0f;
	else if (angle < 0.0f)
		angle = 360.0f;

	position.x = cos(radians(angle)) * cos(radians(pitch));
	position.y = sin(radians(pitch));
	position.z = sin(radians(angle)) * cos(radians(pitch));
}
void CameraManager::Zoom(float _zoomOffset)
{
	fov -= _zoomOffset;
	fov = clamp(fov, minFov, maxFov);
	RotateAround(0.0f);
}

void CameraManager::SetTargetLocation(const Vector3& _targetLocation)
{
	targetLocation = _targetLocation;
}
//void CameraManager::SetTarget(Actor* _target)
//{
//	if (!_target)
//	{
//		targetLocation = position + forward;
//		return;
//	}
//	const Vector3& _targetLocation = _target->GetActorLocation();
//	targetLocation = vec3(_targetLocation.x, _targetLocation.y, _targetLocation.z);
//}

void CameraManager::InitDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}
void CameraManager::UpdateCameraVectors()
{
	forward.x = cos(radians(yaw)) * cos(radians(pitch));
	forward.y = sin(radians(roll));
	forward.z = sin(radians(yaw)) * cos(radians(pitch));
	forward = normalize(forward);

	right = normalize(cross(forward, up));
	up = normalize(cross(right, forward));
}
void CameraManager::UpdateFrustum()
{
	const float _aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	const float _halfVSize = farRange * tanf(radians(fov) * 0.5f);
	const float _halfHSize = _halfVSize * _aspect;
	const vec3& _frontMultFar = farRange * forward;

	frustum.nearFace = Plan(position + nearRange * forward, forward);
	frustum.farFace = Plan(position + _frontMultFar, -forward);

	frustum.rightFace = Plan(position, cross(up, _frontMultFar + right * _halfHSize));
	frustum.leftFace = Plan(position, cross(_frontMultFar - right * _halfHSize, up));

	frustum.topFace = Plan(position, cross(right, _frontMultFar - up * _halfVSize));
	frustum.bottomFace = Plan(position, cross(_frontMultFar + up * _halfVSize, right));
}