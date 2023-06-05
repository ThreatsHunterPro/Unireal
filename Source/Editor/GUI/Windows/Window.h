#pragma once
#include "../Widgets/ContentWidget.h"
#include "../Widgets/EditorBarWidget.h"
#include "../Widgets/ToolBarWidget.h"
#include "../../../Core/Macros.h"

class Window
{
	// Main window
	const char* windowTitle;
	vec2 windowSize;
	vec4 windowBGColor;
	GLFWwindow* mainWindow;

	// Widgets
	Array<Widget*> widgets;
	
public:
	FORCEINLINE GLFWwindow* GetWindow() const { return mainWindow; }
	FORCEINLINE vec2 GetWindowSize() const
	{
		int width, height;
		glfwGetWindowSize(mainWindow, &width, &height);
		return vec2(width, height);
	}
	FORCEINLINE void AddWidget(Widget* _widget)
	{
		int _occurrences = 0;
		for (int _widgetIndex = 0; _widgetIndex < widgets.Lenght(); _widgetIndex++)
		{
			string _name = _widget->GetName();
			if (_name != widgets[_widgetIndex]->GetName()) continue;
			_occurrences++;
			_widget->SetName(_name += std::to_string(_occurrences));
		}
		
		widgets.Add(_widget);
	}

public:
	Window();
	~Window();

#pragma region Start
	
	void Start();
	void InitGLFW();
	void InitImGUI() const;

#pragma endregion

#pragma region Update
	
	void Update() const;
	void UpdateWidgets() const;
	void UpdateWindow() const;

#pragma endregion

#pragma region Stop
	
	void Stop() const;
	void StopImGUI() const;
	void StopWindow() const;

#pragma endregion 
};