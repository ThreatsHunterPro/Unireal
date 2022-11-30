#include "Engine.h"

Engine::Engine()
{
	window = nullptr;
	world = nullptr;
}

Engine::~Engine()
{
	delete window;
	delete world;
}

void Engine::Run()
{
	Start();
	Update();
	Stop();
}

void Engine::Start()
{
	window = new Window();
	window->Start();

	world = new World();
	world->Start();
}

void Engine::Update()
{
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->Update();
		window->Update();
	}
}

void Engine::Stop()
{
	world->Stop();
	window->Stop();
}