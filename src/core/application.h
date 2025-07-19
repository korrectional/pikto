#include "core/engine.h"

class Application
{
private:
    Engine engine;
public:
    bool appRunning = false;
    void run();
};

void Application::run()
{
    appRunning = engine.init();
    
    while (appRunning)
    {
        if(!engine.update()) break;
    }
    
    engine.shutdown();
}