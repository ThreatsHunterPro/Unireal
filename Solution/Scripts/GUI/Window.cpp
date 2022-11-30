#include "Window.h"

namespace GUI
{
	Window::Window()
	{
		windowTitle = "Unknown";
		windowSize = vec2(1920.0f, 1080.0f);
		windowBGColor = vec4(0.0f, 206.0f, 209.0f, 1.0f);
		window = nullptr;
	}

	Window::~Window()
	{

	}

	void Window::Start()
	{
		// Init GLFW
		if (!glfwInit())
		{
			cerr << "Failed to initialize GLFW !\n" << endl;
			return;
		}

		// 4x antialiasing
		glfwWindowHint(GLFW_SAMPLES, 4); 

		// Tell GLFW what version of OpenGL we are using (now : 3.3v)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Tell GLFW we are using the core profile
		// We only have modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create a window of GLFW
		window = glfwCreateWindow(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y), windowTitle, nullptr, nullptr);
		if (!window)
		{
			cerr << "Failed to initialize main window !\n" << endl;
			glfwTerminate();
			return;
		}

		// Introduce the window into the current context
		glfwMakeContextCurrent(window);

		// Needed in core profile
		glewExperimental = true; 

		// Initialize GLEW
		if (glewInit() != GLEW_OK)
		{
			cerr << "Failed to initialize GLEW !\n" << endl;
			glfwTerminate();
			return;
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		// Specify the color of the background
		glClearColor(windowBGColor.x, windowBGColor.y, windowBGColor.z, windowBGColor.w);
	}

	void Window::Update()
	{
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	void Window::Stop()
	{
		// Destroy the current window
		glfwDestroyWindow(window);

		// Close OpenGL window and terminate GLFW
		glfwTerminate();
	}
}