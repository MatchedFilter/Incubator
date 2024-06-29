#ifndef _ITS_INCUBATORTESTSIMULATORUTILS_H_
#define _ITS_INCUBATORTESTSIMULATORUTILS_H_
#include "SDL2/SDL.h"
namespace ITS
{
    class IncubatorTestSimulatorUtils
    {
    public:
        static void Initialize();
        static void SetCursor(SDL_SystemCursor cursorType);

    private:
        static SDL_Cursor *s_SdlCursors[SDL_NUM_SYSTEM_CURSORS];
    };
} // namespace ITS

#endif // _ITS_INCUBATORTESTSIMULATORUTILS_H_