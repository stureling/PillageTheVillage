#include "state.h"

int main()
{
    Engine engine{};
    while (engine.window.isOpen()) 
    {
        engine.run();
    }
}
