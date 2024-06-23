#include "IncubatorTestSimulator.h"
#include "Incubator/Incubator.h"
#include <SDL2/SDL.h>
#include <thread>


ITS::IncubatorTestSimulator g_IncubatorTestSimulator;
static Incubator s_Incubator;
static bool s_bApplicationRunning = true;

void RunIncubatorApp()
{
    while (s_bApplicationRunning)
    {
        s_Incubator.Run();
    }
}

int main(int argc, char *argv[])
{
    g_IncubatorTestSimulator.Initialize();
    s_Incubator.Initialize();
    std::thread incubatorThread = std::thread(RunIncubatorApp);
    while (s_bApplicationRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                s_bApplicationRunning = false;
            }
            g_IncubatorTestSimulator.Run(event);
        }
        // s_Incubator.Run();
    }
    incubatorThread.join();
    return 0;
}