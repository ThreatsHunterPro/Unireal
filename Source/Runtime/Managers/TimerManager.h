#pragma once
#include "Manager.h"
#include "../../Core/Macros.h"

class TimerManager : public Manager<TimerManager>
{
    float deltaTime;
    float lastTime;

public:
    TimerManager();
    ~TimerManager();

public:
    FORCEINLINE float DeltaTimeSeconds() const { return deltaTime; }
    
public:
    void Start();
    void Update();
    void Stop();
};