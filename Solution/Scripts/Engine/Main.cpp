#include "Engine.h"

int main(int _argc, char** _argv)
{
    Engine* _engine = new Engine();
    _engine->Run();

    delete _engine;

    return 0;
}