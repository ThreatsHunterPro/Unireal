#pragma once
#include "../Engine/Macros.h"

namespace GUI
{
	class Window
	{
	private:
		char* windowTitle;
		vec2 windowSize;
		vec4 windowBGColor;
		GLFWwindow* window;

	public:
		FORCEINLINE GLFWwindow* GetWindow() const { return window; }

	public:
		Window();
		~Window();

	public:
		void Start();
		void Update();
		void Stop();
	};
}