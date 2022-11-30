#include "SceneComponent.h"
#include <Scripts/Game/Actors/Actor.h>

SceneComponent::SceneComponent(Actor* _owner) : Component(_owner)
{
	transform = Transform();
}
SceneComponent::~SceneComponent()
{

}

void SceneComponent::Start()
{
	SUPER::Start();
}
void SceneComponent::Update(float _deltaTime)
{
	SUPER::Update(_deltaTime);
}
void SceneComponent::Stop()
{
	SUPER::Stop();
}

#pragma region Local

#pragma region AddMethods

void SceneComponent::AddLocalTransform(const Transform& _transform)
{
	transform += _transform;
}
void SceneComponent::AddLocalLocation(const Vector3& _location)
{
	transform.location += _location;
}
void SceneComponent::AddLocalRotation(const Rotator& _rotation)
{
	transform.rotation += _rotation;
}
void SceneComponent::AddLocalScale(const Vector3& _scale)
{
	transform.scale += _scale;
}

#pragma endregion

#pragma region SetMethods

void SceneComponent::SetLocalTransform(const Transform& _transform)
{
	transform = _transform;
}
void SceneComponent::SetLocalLocation(const Vector3& _location)
{
	transform.location = _location;
}
void SceneComponent::SetLocalLocationAndRotation(const Vector3& _location, const Rotator& _rotation)
{
	transform.location = _location;
	transform.rotation = _rotation;
}
void SceneComponent::SetLocalRotation(const Rotator& _rotation)
{
	transform.rotation = _rotation;
}
void SceneComponent::SetLocalScale(const Vector3& _scale)
{
	transform.scale = _scale;
}

#pragma endregion

#pragma endregion

#pragma region Relative

#pragma region AddMethods

void SceneComponent::AddRelativeTransform(const Transform& _transform)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalTransform(_transform);
		return;
	}
	transform += _transform - GetRelativeTransform(_parent);
}
void SceneComponent::AddRelativeLocation(const Vector3& _location)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalLocation(_location);
		return;
	}
	transform.location += _location - GetRelativeLocation(_parent);
}
void SceneComponent::AddRelativeRotation(const Rotator& _rotation)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalRotation(_rotation);
		return;
	}
	transform.rotation += _rotation - GetRelativeRotation(_parent);
}
void SceneComponent::AddRelativeScale(const Vector3& _scale)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalScale(_scale);
		return;
	}
	transform.scale += _scale - GetRelativeScale(_parent);
}

#pragma endregion

#pragma region GetMethods

const Transform& SceneComponent::GetRelativeTransform(Actor* _parent) const
{
	return _parent ? _parent->GetActorTransform() : GetLocalTransform();
}
const Vector3& SceneComponent::GetRelativeLocation(Actor* _parent) const
{
	return _parent ? _parent->GetActorLocation() : GetLocalLocation();
}
const Rotator& SceneComponent::GetRelativeRotation(Actor* _parent) const
{
	return _parent ? _parent->GetActorRotation() : GetLocalRotation();
}
const Vector3& SceneComponent::GetRelativeScale(Actor* _parent) const
{
	return _parent ? _parent->GetActorScale() : GetLocalScale();
}

#pragma endregion

#pragma region SetMethods

void SceneComponent::SetRelativeTransform(const Transform& _transform)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalTransform(_transform);
		return;
	}
	transform = _transform - GetRelativeTransform(_parent);
}
void SceneComponent::SetRelativeLocation(const Vector3& _location)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalLocation(_location);
		return;
	}
	transform.location = _location - GetRelativeLocation(_parent);
}
void SceneComponent::SetRelativeLocationAndRotation(const Vector3& _location, const Rotator& _rotation)
{
	SetRelativeLocation(_location);
	SetRelativeRotation(_rotation);
}
void SceneComponent::SetRelativeRotation(const Rotator& _rotation)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalRotation(_rotation);
		return;
	}
	transform.rotation = _rotation - GetRelativeRotation(_parent);
}
void SceneComponent::SetRelativeScale(const Vector3& _scale)
{
	Actor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalScale(_scale);
		return;
	}
	transform.scale = _scale - GetRelativeScale(_parent);
}

#pragma endregion

#pragma endregion