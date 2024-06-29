#include "IncubatorTestSimulator.h"
#include "Incubator/Incubator.h"
#include <SDL2/SDL.h>
#include <thread>

#ifndef INCUBATOR_SOFTWARE_VERSION
#define INCUBATOR_SOFTWARE_VERSION "Hata"
#endif // INCUBATOR_SOFTWARE_VERSION

const char *INCUBATOR_VERSION = INCUBATOR_SOFTWARE_VERSION;

ITS::IncubatorTestSimulator g_IncubatorTestSimulator;
static Incubator s_Incubator(INCUBATOR_VERSION);
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
            else
            {
                g_IncubatorTestSimulator.HandleEvents(event);
            }
        }
        g_IncubatorTestSimulator.Run();
    }
    incubatorThread.join();
    return 0;
}