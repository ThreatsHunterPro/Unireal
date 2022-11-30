#pragma once


class Actor
{
	//friend class World;

	string name;
	SceneComponent* rootComponent;
	StaticMeshComponent* staticMesh;
	List<Component*> components;
	Actor* parent;

public:
	Actor();
	~Actor();

protected:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void Stop();

private:
	/*friend void Component::Start();
	friend void Component::Update(float _deltaTime);
	friend void Component::Stop();*/

public:
	void SetMesh(const char* _objPath, char* _texturePath, bool _useCustomMethod);

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
	FORCEINLINE const Vector3& GetActorLocation()
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
	void SetActorTransform(const Vector3& _location, const Rotator& _rotation, const Vector3& _scale);
	void SetActorTransform(const Transform& _transform);

	// ** Location **
	void SetActorLocation(const float _loc);
	void SetActorLocation(const float _locX, const float _locY, const float _locZ);
	void SetActorLocation(const Vector3& _location);
	void SetActorLocationAndRotation(const Vector3& _location, const Rotator& _rotation);

	// ** Rotation **
	void SetActorRotation(const float _rot);
	void SetActorRotation(const float _rotX, const float _rotY, const float _rotZ);
	void SetActorRotation(const Rotator& _rotation);

	// ** Scale **
	void SetActorScale(const float _scale);
	void SetActorScale(const float _scaleX, const float _scaleY, const float _scaleZ);
	void SetActorScale(const Vector3& _scale);

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
		return staticMesh ? staticMesh->GetMeshScale() : Vector3(0.0f);
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