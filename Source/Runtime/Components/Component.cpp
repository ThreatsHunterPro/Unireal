#include "Component.h"
#include "../Actors/Actor.h"

Component::Component(Actor* _owner)
{
	owner = _owner;
}
Component::~Component() = default;

void Component::Start()
{

}
void Component::Update(float _deltaTime)
{

}
void Component::Stop()
{

}