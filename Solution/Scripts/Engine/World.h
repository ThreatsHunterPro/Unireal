#pragma once
#include <Scripts/Game/Actor.h>

class World
{
	List<Actor*> actors;
	float deltaTime;

public:
	World();
	~World();

public:
	void Start();
	void Update();
	void Stop();

private:
	/*friend void Actor::Start();
	friend void Actor::Update(float _deltaTime);
	friend void Actor::Stop();*/
};