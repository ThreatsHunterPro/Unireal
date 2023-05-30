#include "InputManager.h"
#include "CameraManager.h"

InputManager::InputManager()
{
	window = nullptr;
}
InputManager::~InputManager()
{
}

void InputManager::Start(GLFWwindow* _window)
{
	window = _window;
	InitControls();
}
void InputManager::Update()
{
	// Take care of all GLFW events
	glfwPollEvents();
	
	ProcessMouse();
	ProcessInputs();
}
void InputManager::Stop() const
{
}

void InputManager::InitControls() const
{
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();

	int _windowWidth, _windowHeight;
	glfwGetWindowSize(window, &_windowWidth, &_windowHeight);
	
	const double _halfWidth = _windowWidth / 2.0;
	const double _halfHeight = _windowHeight / 2.0;
	glfwSetCursorPos(window, _halfWidth, _halfHeight);
}
void InputManager::ProcessMouse()
{
	double _xPos, yPos = 0.0;
	glfwGetCursorPos(window, &_xPos, &yPos);

	const float _xCursorPos = static_cast<float>(_xPos);
	const float _yCursorPos = static_cast<float>(yPos);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		const float yawValue = previousCursorPos.x - _xCursorPos;
		const float pitchValue = previousCursorPos.y - _yCursorPos;
		
		CameraManager::Instance()->MoveYaw(yawValue);
		CameraManager::Instance()->MovePitch(pitchValue);
	}
	
	previousCursorPos = Vector2(_xCursorPos, _yCursorPos);
}
void InputManager::ProcessInputs() const
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		CameraManager::Instance()->Debug();
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraManager::Instance()->MoveForward(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraManager::Instance()->MoveForward(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraManager::Instance()->MoveRight(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraManager::Instance()->MoveRight(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		CameraManager::Instance()->MoveUp(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		CameraManager::Instance()->MoveUp(1.0f);
	}
}