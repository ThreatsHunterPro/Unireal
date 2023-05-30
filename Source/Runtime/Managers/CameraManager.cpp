#include "CameraManager.h"
#include "TimerManager.h"

CameraManager::CameraManager(): projectionMatrix(), viewMatrix()
{
	position = vec3(0.0f, 0.0f, -13.0f);
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	angle = 0.0f;
	speed = 3.0f;
	sensivity = 0.05f;
	targetLocation = Vector3();

	fov = 45.0f;
	minFov = 0.1f;
	maxFov = 100.0f;

	nearRange = 0.1f;
	farRange = 45.0f;

	frustum = Frustum();

	forward = vec3(-1.0f, 0.0f, 0.0f);
	right = vec3(0.0f, 1.0f, 0.0f);
	up = vec3(0.0f, 0.0f, 1.0f);

	windowWidth = 1920;
	windowHeight = 1080;

	DebugShader = new TShader("D:/Prog/OpenGL/Unireal/Content/Shaders/DebugShader.vertexshader",
	                          "D:/Prog/OpenGL/Unireal/Content/Shaders/DebugShader.fragmentshader");
}
CameraManager::~CameraManager() = default;

void CameraManager::Start()
{
	InitDepth();
}
void CameraManager::Update()
{
	UpdateCameraVectors();
	
	// DebugShader->Use();
	// const mat4& _mvp = GetProjectionMatrix() * GetViewMatrix() * mat4(1.0f);
	// DebugShader->SetMat4("uModelViewProjection", _mvp);
	// DrawGrid(0.5f, 20, vec4(1.0f, 0.0f, 0.0f, 1.0f), *DebugShader);
	
	// UpdateFrustum();
}
void CameraManager::Stop() const
{

}

void CameraManager::Debug() const
{
	cout << "X: " << position.x << " Y: " << position.y << " Z: " << position. z << endl;
	cout << "Yaw: " << pitch << " Pitch: " << pitch << " Roll: " << roll << endl;
}

// Standard
void CameraManager::MoveForward(float _verticalValue)
{
	const float _value = std::clamp(_verticalValue, -1.0f, 1.0f);
	position += forward * _value * speed * TimerManager::Instance()->DeltaTimeSeconds();
}
void CameraManager::MoveRight(float _horizontalValue)
{
	const float _value = std::clamp(_horizontalValue, -1.0f, 1.0f);
	position += right * _value * speed * TimerManager::Instance()->DeltaTimeSeconds();
}
void CameraManager::MoveUp(float _upValue)
{
	const float _value = std::clamp(_upValue, -1.0f, 1.0f);
	position += up * _value * speed * TimerManager::Instance()->DeltaTimeSeconds();
}

// Mouse
void CameraManager::MoveYaw(float _yawValue)
{
	yaw += radians(_yawValue * sensivity);

	yaw = mod(yaw, 360.0f);
	if (yaw > 180.0f)
	{
		yaw -= 360.0f;
	}
}
void CameraManager::MovePitch(float _pitchValue)
{
	pitch += radians(_pitchValue * sensivity);
	pitch = glm::clamp(pitch, -90.0f, 90.0f);
}
void CameraManager::MoveRoll(float _rollValue)
{
	roll += _rollValue * sensivity * TimerManager::Instance()->DeltaTimeSeconds();

	// if (roll >= 360.0f)
	// 	roll = 0.0f;
	//
	// else if (roll < 0.0f)
	// 	roll = 360.0f;
}

// Other
void CameraManager::RotateAround(float _direction)
{
	// const float _value = std::clamp(_direction, -1.0f, 1.0f);
	// angle += _value * speed / 10 * TimerManager::Instance()->DeltaTimeSeconds();
	//
	// if (angle >= 360.0f)
	// 	angle = 0.0f;
	// else if (angle < 0.0f)
	// 	angle = 360.0f;
	//
	// position.x = cos(radians(angle)) * cos(radians(pitch));
	// position.y = sin(radians(pitch));
	// position.z = sin(radians(angle)) * cos(radians(pitch));
}
void CameraManager::Zoom(float _zoomOffset)
{
	fov -= _zoomOffset;
	fov = std::clamp(fov, minFov, maxFov);
	// RotateAround(0.0f);
}
void CameraManager::SetTargetLocation(const Vector3& _targetLocation)
{
	targetLocation = _targetLocation;
}
/*void CameraManager::SetTarget(Actor* _target)
{
	if (!_target)
	{
		targetLocation = position + forward;
		return;
	}
	const Vector3& _targetLocation = _target->GetActorLocation();
	targetLocation = vec3(_targetLocation.x, _targetLocation.y, _targetLocation.z);
}*/

void CameraManager::InitDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}
void CameraManager::UpdateCameraVectors()
{
	forward = vec3(
		cos(pitch) * sin(yaw), 
		sin(pitch),
		cos(pitch) * cos(yaw)
	);
	
	right = vec3(
		sin(yaw - 90.0f), 
		0,
		cos(yaw - 90.0f)
	);
	
	up = cross(right, forward);
}
void CameraManager::UpdateFrustum()
{
	const float _aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	const float _halfVSize = farRange * tanf(radians(fov) * 0.5f);
	const float _halfHSize = _halfVSize * _aspect;
	const vec3& _frontMultFar = farRange * forward;
	const vec3& _pos = position.ToVec3();

	frustum.nearFace = Plan(_pos + nearRange * forward, forward);
	frustum.farFace = Plan(_pos + _frontMultFar, -forward);

	frustum.rightFace = Plan(_pos, cross(up, _frontMultFar + right * _halfHSize));
	frustum.leftFace = Plan(_pos, cross(_frontMultFar - right * _halfHSize, up));

	frustum.topFace = Plan(_pos, cross(right, _frontMultFar - up * _halfVSize));
	frustum.bottomFace = Plan(_pos, cross(_frontMultFar + up * _halfVSize, right));
}
