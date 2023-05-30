#pragma once
#include "../../Core/Macros.h"

class Actor;

class Component
{

protected:
	Actor* owner;

public:
	FORCEINLINE Actor* GetOwner() const { return owner; }

public:
	explicit Component(Actor* _owner);
	virtual ~Component();

public:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void Stop();
};