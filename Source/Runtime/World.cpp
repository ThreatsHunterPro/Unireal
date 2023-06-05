#include "World.h"
#include "Managers/TimerManager.h"
#include "Managers/InputManager.h"
#include "Managers/CameraManager.h"

World::World()
{
	window = nullptr;
	actors = Array<Actor*>();
}
World::World(GLFWwindow* _window)
{
	window = _window;
	actors = Array<Actor*>();
}
World::~World() = default;

void World::Start()
{
	TimerManager::Instance()->Start();
	InputManager::Instance()->Start(window);
	CameraManager::Instance()->Start();

	const int _actorsCount = actors.Lenght();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		Actor* _actor = actors[_index];
		if (!_actor) return;
		_actor->Start();
	}
}
void World::Update() const
{
	TimerManager::Instance()->Update();
	InputManager::Instance()->Update();
	CameraManager::Instance()->Update();

	// const int _actorsCount = Instance()->actors.Lenght();
	// for (int _index(0); _index < _actorsCount; _index++)
	// {
	// 	Actor* _actor = Instance()->actors[_index];
	// 	if (!_actor) continue;
	// 	_actor->Update(1.0f);
	// }
}
void World::Stop()
{
	TimerManager::Instance()->Stop();
	InputManager::Instance()->Stop();
	CameraManager::Instance()->Stop();

	const int _actorsCount = actors.Lenght();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		Actor* _actor = actors[_index];
		if (!_actor) return;
		_actor->Stop();
	}
}

void World::SpawnActor(String _name, String _mesh, String _texture, bool _custom, Transform _transform)
{
	Actor* _actor = new Actor(this, _name);
	if (!_actor) return;
	
	_actor->SetMesh(_mesh, _texture, _custom);
	_actor->SetActorTransform(_transform);
	actors.Add(_actor);
}
void World::DestroyActor(Actor* _actor)
{
	if (!_actor) return;
	actors.RemoveSingle(_actor);
}