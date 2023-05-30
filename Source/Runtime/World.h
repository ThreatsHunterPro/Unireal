#pragma once
#include "../Core/Macros.h"
#include "Actors/Actor.h"
#include "Managers/Manager.h"

class World : public Manager<World>
{
	GLFWwindow* window;

public:
	Array<Actor*> actors;
	
public:
	World();
	World(GLFWwindow* _window);
	~World();

public:
	void Start();
	void Update() const;
	void Stop();
	
	void SpawnActor(string _name, string _mesh, string _texture, bool _custom, Transform _transform);
	void DestroyActor(Actor* _actor);
};