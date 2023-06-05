#include "Window.h"

Window::Window()
{
	// Window values
	windowTitle = "Unireal";
	windowSize = vec2(1920, 1080);
	windowBGColor = vec4(150.0f, 0.0f, 0.0, 0.5f);

	// Widgets values
	widgets.Add(new EditorBarWidget("Editor", this));
	// widgets.Add(new ToolBarWidget("Tool", this));
}
Window::~Window()
{
	widgets.Empty();
}

#pragma region Start

void Window::Start()
{
	// Init GLFW
	InitGLFW();

	// Init ImGUI
	InitImGUI();
}
void Window::InitGLFW()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a mainWindow and create its OpenGL context
	mainWindow = glfwCreateWindow(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y), windowTitle, nullptr, nullptr);
	if( mainWindow == nullptr ){
		fprintf( stderr, "Failed to open GLFW mainWindow. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return;
	}
		
	glfwMakeContextCurrent(mainWindow);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Specify the color of the background
	glClearColor(windowBGColor.x, windowBGColor.y, windowBGColor.z, windowBGColor.w);
}
void Window::InitImGUI() const
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& _io = ImGui::GetIO();
	_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	_io.MouseDrawCursor = true;

	ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

#pragma endregion 

#pragma region Update

void Window::Update() const
{
	// Update widgets
	UpdateWidgets();

	// Update window
	UpdateWindow();
}
void Window::UpdateWidgets() const
{
	// Start a new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();
	
	// Draw widgets
	const int _widgetsCount = widgets.Lenght();
	for (int _widgetIndex = 0; _widgetIndex < _widgetsCount; _widgetIndex++)
	{
		Widget* _widget = widgets[_widgetIndex];
		if (!_widget) continue;
		_widget->Draw();
	}

	// End current frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	// glClearColor(windowBGColor.x, windowBGColor.y, windowBGColor.z, windowBGColor.w);
}
void Window::UpdateWindow() const
{
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(mainWindow);
}

#pragma endregion

#pragma region Stop

void Window::Stop() const
{
	// Stop ImGUI
	StopImGUI();
	
	// Stop sindow
	StopWindow();
}
void Window::StopImGUI() const
{
	// Stop widgets
	const int _widgetsCount = widgets.Lenght();
	for (int _widgetIndex = 0; _widgetIndex < _widgetsCount; _widgetIndex++)
	{
		Widget* _widget = widgets[_widgetIndex];
		if (!_widget) continue;
		_widget->Stop();
	}
	
	// Clean ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void Window::StopWindow() const
{
	// Destroy the current window
	glfwDestroyWindow(mainWindow);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

#pragma endregion 