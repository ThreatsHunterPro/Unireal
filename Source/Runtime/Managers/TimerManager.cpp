#include "TimerManager.h"

TimerManager::TimerManager()
{
    deltaTime = 0.0;
    lastTime = 0.0f;
}

TimerManager::~TimerManager()
{
    
}

void TimerManager::Start()
{
    
}
void TimerManager::Update()
{
    const float _currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = _currentFrame - lastTime;
    lastTime = _currentFrame;
}
void TimerManager::Stop()
{
    
}