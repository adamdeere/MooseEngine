#include "Engine/Engine.h"

int main()
{
    Engine engine;

    if (!engine.Initialise())
        return -1;

    engine.Run();
    engine.Shutdown();

    return 0;
}
