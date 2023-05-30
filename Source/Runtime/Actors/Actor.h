#pragma once
#include "../Object.h"
#include "../../Core/Macros.h"
#include "../Components/SceneComponent.h"
#include "../Components/StaticMeshComponent.h"

class World;

class Actor : public Object
{
	SceneComponent* rootComponent;
	StaticMeshComponent* staticMesh;
	
	string name;
	Array<Component*> components;
	Actor* parent;

public:
	Actor(World* _world, string _name);
	virtual ~Actor();

public:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void Stop();

public:
	void SetMesh(const char* _objPath, const char* _texturePath, bool _useCustomMethod) const;

	#pragma region ParentMethods

	void SetParent(Actor* _parent);
	FORCEINLINE Actor* GetParent() const { return parent; }

	#pragma endregion

	#pragma region TransformMethods

	#pragma region LocalMethods

	#pragma region AddMethods

	void AddActorLocation(const Vector3& _location);
	void AddActorRotation(const float _angle, const Vector3& _axis);
	void AddActorScale(const Vector3& _scale);

	#pragma endregion

	#pragma region GetMethods

	FORCEINLINE const Transform& GetActorTransform() const
	{
		return rootComponent->GetLocalTransform();
	}
	FORCEINLINE const Vector3& GetActorLocation() const
	{
		return rootComponent->GetLocalLocation();
	}
	FORCEINLINE const Rotator& GetActorRotation() const
	{
		return rootComponent->GetLocalRotation();
	}
	FORCEINLINE const Vector3& GetActorScale() const
	{
		return rootComponent->GetLocalScale();
	}

	#pragma endregion

	#pragma region SetMethods

	// ** Transform **
	void SetActorTransform(const Vector3& _location, const Rotator& _rotation, const Vector3& _scale) const;
	void SetActorTransform(const Transform& _transform) const;

	// ** Location **
	void SetActorLocation(const float _loc) const;
	void SetActorLocation(const float _locX, const float _locY, const float _locZ) const;
	void SetActorLocation(const Vector3& _location) const;
	void SetActorLocationAndRotation(const Vector3& _location, const Rotator& _rotation) const;

	// ** Rotation **
	void SetActorRotation(const float _rot) const;
	void SetActorRotation(const float _rotX, const float _rotY, const float _rotZ) const;
	void SetActorRotation(const Rotator& _rotation) const;

	// ** Scale **
	void SetActorScale(const float _scale) const;
	void SetActorScale(const float _scaleX, const float _scaleY, const float _scaleZ) const;
	void SetActorScale(const Vector3& _scale) const;

	#pragma endregion

	#pragma endregion

	#pragma region RelativeMethods

	#pragma region AddMethods

	void AddActorRelativeLocation(const Vector3& _location);
	void AddActorRelativeRotation(const float _angle, const Vector3& _axis);
	void AddActorRelativeScale(const Vector3& _scale);

	#pragma endregion

	#pragma region GetMethods

	FORCEINLINE const Transform& GetActorRelativeTransform() const
	{
		return rootComponent->GetRelativeTransform(parent);
	}
	FORCEINLINE const Vector3& GetActorRelativeLocation() const
	{
		return rootComponent->GetRelativeLocation(parent);
	}
	FORCEINLINE const Rotator& GetActorRelativeRotation() const
	{
		return rootComponent->GetRelativeRotation(parent);
	}
	FORCEINLINE const Vector3& GetActorRelativeScale() const
	{
		return rootComponent->GetRelativeScale(parent);
	}

	#pragma endregion

	#pragma region SetMethods

	// ** Transform **
	void SetActorRelativeTransform(const Vector3& _location, const Rotator& _rotation, const Vector3& _scale);
	void SetActorRelativeTransform(const Transform& _transform);

	// ** Location **
	void SetActorRelativeLocation(const float _loc);
	void SetActorRelativeLocation(const float _locX, const float _locY, const float _locZ);
	void SetActorRelativeLocation(const Vector3& _location);

	// ** Rotation **
	void SetActorRelativeRotation(const float _rot);
	void SetActorRelativeRotation(const float _rotX, const float _rotY, const float _rotZ);
	void SetActorRelativeRotation(const Rotator& _rotation);

	// ** Scale **
	void SetActorRelativeScale(const float _scale);
	void SetActorRelativeScale(const float _scaleX, const float _scaleY, const float _scaleZ);
	void SetActorRelativeScale(const Vector3& _scale);

	#pragma endregion

	#pragma endregion

	#pragma region MeshMethods

	FORCEINLINE const mat4& GetMeshMatrix() const
	{
		return staticMesh ? staticMesh->GetModelMatrix() : mat4(0.0f);
	}
	FORCEINLINE Vector3 GetActorMeshLocation() const
	{
		return staticMesh ? staticMesh->GetMeshPosition() : Vector3(0.0f);
	}
	FORCEINLINE Rotator GetActorMeshRotation() const
	{
		return staticMesh ? staticMesh->GetMeshRotation() : Rotator(0.0f);
	}
	FORCEINLINE Vector3 GetActorMeshScale() const
	{
		return Vector3();
		// return staticMesh ? staticMesh->GetMeshScale() : Vector3(0.0f);
	}

	FORCEINLINE Vector3 GetActorForwardVector() const
	{
		return staticMesh ? staticMesh->GetForward() : Vector3(0.0f);
	}
	FORCEINLINE Vector3 GetActorRightVector() const
	{
		return staticMesh ? staticMesh->GetRight() : Vector3(0.0f);
	}
	FORCEINLINE Vector3 GetActorUpVector() const
	{
		return staticMesh ? staticMesh->GetUp() : Vector3(0.0f);
	}

	#pragma endregion

	#pragma endregion
};
