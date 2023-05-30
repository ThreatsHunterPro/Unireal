#include "Engine.h"
#include "../../Core/Macros.h"

Engine::Engine()
{
	window = new Window();
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
	window->Start();
	world = new World(window->GetWindow());
	world->Start();
}
void Engine::Update() const
{
	GLFWwindow* _mainWindow = window->GetWindow();
	
	while (glfwGetKey(_mainWindow, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(_mainWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->Update();
		window->Update();
	}
}
void Engine::Stop() const
{
	world->Stop();
	window->Stop();
}