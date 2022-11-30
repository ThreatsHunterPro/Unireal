#include "World.h"

World::World()
{
	actors = List<Actor*>();
	deltaTime = 0.0f;
}
World::~World()
{

}

void World::Start()
{
	int _actorsCount = actors.Lenght();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		Actor* _actor = actors[_index];
		if (!_actor) return;
		//_actor->Start();
	}
}
void World::Update()
{
	int _actorsCount = actors.Lenght();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		Actor* _actor = actors[_index];
		if (!_actor) return;
		//_actor->Update(deltaTime += 0.1f);
	}
}
void World::Stop()
{
	int _actorsCount = actors.Lenght();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		Actor* _actor = actors[_index];
		if (!_actor) return;
		//_actor->Stop();
	}
}