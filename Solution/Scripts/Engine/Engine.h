#pragma once
#include "../GUI/Window.h"
#include "World.h"
#include "Macros.h"

using namespace GUI;

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
	void Update();
	void Stop();
};