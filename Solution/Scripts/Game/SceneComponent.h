#pragma once
#include "Component.h"
#include "Scripts/Engine/Macros.h"

class SceneComponent : public Component
{
	Transform transform;

public:
	SceneComponent(Actor* _owner);
	~SceneComponent();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void Stop() override;

	#pragma region LocalMethods

	#pragma region AddMethods

	void AddLocalTransform(const Transform& _transform);
	void AddLocalLocation(const Vector3& _location);
	void AddLocalRotation(const Rotator& _rotation);
	void AddLocalScale(const Vector3& _scale);

	#pragma endregion

	#pragma region GetMethods

	FORCEINLINE const Transform& GetLocalTransform() const
	{
		return transform;
	}
	FORCEINLINE const Vector3& GetLocalLocation() const
	{
		return transform.location;
	}
	FORCEINLINE const Rotator& GetLocalRotation() const
	{
		return transform.rotation;
	}
	FORCEINLINE const Vector3& GetLocalScale() const
	{
		return transform.scale;
	}

	#pragma endregion

	#pragma region SetMethods

	void SetLocalTransform(const Transform& _transform);
	void SetLocalLocation(const Vector3& _location);
	void SetLocalLocationAndRotation(const Vector3& _location, const Rotator& _rotation);
	void SetLocalRotation(const Rotator& _rotation);
	void SetLocalScale(const Vector3& _scale);

	#pragma endregion

	#pragma endregion

	#pragma region RelativeMethods

	#pragma region AddMethods

	void AddRelativeTransform(const Transform& _location);
	void AddRelativeLocation(const Vector3& _location);
	void AddRelativeRotation(const Rotator& _rotation);
	void AddRelativeScale(const Vector3& _scale);

	#pragma endregion

	#pragma region GetMethods

	const Transform& GetRelativeTransform(Actor* _parent) const;
	const Vector3& GetRelativeLocation(Actor* _parent) const;
	const Rotator& GetRelativeRotation(Actor* _parent) const;
	const Vector3& GetRelativeScale(Actor* _parent) const;

	#pragma endregion

	#pragma region SetMethods

	void SetRelativeTransform(const Transform& _transform);
	void SetRelativeLocation(const Vector3& _location);
	void SetRelativeLocationAndRotation(const Vector3& _location, const Rotator& _rotation);
	void SetRelativeRotation(const Rotator& _rotation);
	void SetRelativeScale(const Vector3& _scale);

	#pragma endregion

	#pragma endregion
};