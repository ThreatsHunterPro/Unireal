#include "Actor.h"
#include "../World.h"

Actor::Actor(World* _world, String _name) : Object(_world)
{
	name = _name;
	components = Array<Component*>();
	
	rootComponent = new SceneComponent(this);
	components.Add(rootComponent);
	
	staticMesh = new StaticMeshComponent(this);
	components.Add(staticMesh);

	world = _world;
}

Actor::~Actor()
{
	components.Empty();
}

void Actor::Start()
{
	const int _componentsCount = components.Lenght();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		Component* _component = components[_index];
		if (!_component) return;
		_component->Start();
	}
}
void Actor::Update(float _deltaTimeSeconds)
{
	const int _componentsCount = components.Lenght();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		Component* _component = components[_index];
		if (!_component) return;
		_component->Update(_deltaTimeSeconds);
	}
}
void Actor::Stop()
{
	const int _componentsCount = components.Lenght();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		Component* _component = components[_index];
		if (!_component) return;
		_component->Stop();
	}
}

void Actor::SetMesh(const String& _objPath, const String& _texturePath, bool _useCustomMethod) const
{
	staticMesh->Init(_objPath, _texturePath, _useCustomMethod);
}

#pragma region ParentMethods

void Actor::SetParent(Actor* _parent)
{
	if (parent)
	{
		delete parent;
	}
	parent = _parent;
}

#pragma endregion

#pragma region TransformMethods

#pragma region Local

#pragma region AddMethods

void Actor::AddActorLocation(const Vector3& _location)
{
	rootComponent->AddLocalLocation(_location);

	if (staticMesh)
	{
		staticMesh->AddMeshLocation(_location);
	}
}
void Actor::AddActorRotation(const float _angle, const Vector3& _axis)
{
	rootComponent->AddLocalRotation(GetActorMeshRotation());

	if (staticMesh)
	{
		staticMesh->AddMeshRotation(_angle, _axis);
	}
}
void Actor::AddActorScale(const Vector3& _scale)
{
	rootComponent->AddLocalScale(_scale);

	if (staticMesh)
	{
		staticMesh->AddMeshScale(_scale);
	}
}

#pragma endregion

#pragma region SetMethods

void Actor::SetActorTransform(const Vector3& _location, const Rotator& _rotation, const Vector3& _scale) const
{
	SetActorTransform(Transform(_location, _rotation, _scale));
}
void Actor::SetActorTransform(const Transform& _transform) const
{
	SetActorLocation(_transform.location);
	SetActorRotation(_transform.rotation);
	SetActorScale(_transform.scale);
}

void Actor::SetActorLocation(const float _loc) const
{
	SetActorLocation(Vector3(_loc));
}
void Actor::SetActorLocation(const float _locX, const float _locY, const float _locZ) const
{
	SetActorLocation(Vector3(_locX, _locY, _locZ));
}
void Actor::SetActorLocation(const Vector3& _location) const
{
	rootComponent->SetLocalLocation(_location);
	staticMesh->SetMeshLocation(_location);
}
void Actor::SetActorLocationAndRotation(const Vector3& _location, const Rotator& _rotation) const
{
	SetActorLocation(_location);
	SetActorRotation(_rotation);
}

void Actor::SetActorRotation(const float _rot) const
{
	SetActorRotation(Rotator(_rot));
}
void Actor::SetActorRotation(const float _rotX, const float _rotY, const float _rotZ) const
{
	SetActorRotation(Rotator(_rotX, _rotY, _rotZ));
}
void Actor::SetActorRotation(const Rotator& _rotation) const
{
	rootComponent->SetLocalRotation(_rotation);
	staticMesh->SetMeshRotation(_rotation);
}

void Actor::SetActorScale(const float _scale) const
{
	SetActorScale(Vector3(_scale));
}
void Actor::SetActorScale(const float _scaleX, const float _scaleY, const float _scaleZ) const
{
	SetActorScale(Vector3(_scaleX, _scaleY, _scaleZ));
}
void Actor::SetActorScale(const Vector3& _scale) const
{
	rootComponent->SetLocalScale(_scale);
	staticMesh->SetMeshScale(_scale);
}

#pragma endregion

#pragma endregion

#pragma region Relative

//TODO implement
#pragma region AddMethods

void Actor::AddActorRelativeLocation(const Vector3& _location)
{

}
void Actor::AddActorRelativeRotation(const float _angle, const Vector3& _axis)
{

}
void Actor::AddActorRelativeScale(const Vector3& _scale)
{

}

#pragma endregion

#pragma region SetMethods

void Actor::SetActorRelativeTransform(const Vector3& _location, const Rotator& _rotation, const Vector3& _scale)
{
	SetActorRelativeTransform(Transform(_location, _rotation, _scale));
}
void Actor::SetActorRelativeTransform(const Transform& _transform)
{
	rootComponent->SetRelativeTransform(_transform);
}

void Actor::SetActorRelativeLocation(const float _loc)
{
	SetActorRelativeLocation(Vector3(_loc));

}
void Actor::SetActorRelativeLocation(const float _locX, const float _locY, const float _locZ)
{
	SetActorRelativeLocation(Vector3(_locX, _locY, _locZ));
}
void Actor::SetActorRelativeLocation(const Vector3& _location)
{
	rootComponent->SetRelativeLocation(_location);
}

void Actor::SetActorRelativeRotation(const float _rot)
{
	SetActorRelativeRotation(Rotator(_rot));
}
void Actor::SetActorRelativeRotation(const float _rotX, const float _rotY, const float _rotZ)
{
	SetActorRelativeRotation(Rotator(_rotX, _rotY, _rotZ));
}
void Actor::SetActorRelativeRotation(const Rotator& _rotation)
{
	rootComponent->SetRelativeRotation(_rotation);
}

void Actor::SetActorRelativeScale(const float _scale)
{
	SetActorRelativeScale(Vector3(_scale));
}
void Actor::SetActorRelativeScale(const float _scaleX, const float _scaleY, const float _scaleZ)
{
	SetActorRelativeScale(Vector3(_scaleX, _scaleY, _scaleZ));
}
void Actor::SetActorRelativeScale(const Vector3& _scale)
{
	rootComponent->SetRelativeScale(_scale);
}

#pragma endregion

#pragma endregion

#pragma endregion