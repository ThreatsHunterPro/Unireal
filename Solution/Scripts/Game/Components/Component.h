#pragma once
#include <Scripts/Game/Actors/Actor.h>
#include <Scripts/Engine/Macros.h>

class Component
{

protected:
	///*friend*/ class Actor;
	Actor* owner;

public:
	FORCEINLINE Actor* GetOwner() const { return owner; }

public:
	Component(Actor* _owner);
	~Component();

protected:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void Stop();
};