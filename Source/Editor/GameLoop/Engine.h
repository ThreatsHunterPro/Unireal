#pragma once
#include "../GUI/Windows/Window.h"
#include "../../Runtime/World.h"

class Engine
{
	Window* window;
	World* world;
	
public:
	Engine();
	~Engine();
	
	void Run();
	
private:
	void Start();
	void Update() const;
	void Stop() const;
};