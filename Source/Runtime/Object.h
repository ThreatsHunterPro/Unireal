#pragma once
#include "../../../Core/Macros.h"

class World;

class Object
{
protected:
    World* world;

public:
    FORCEINLINE World* GetWorld() const { return world; }
    
public:
    Object(World* _world);
};
