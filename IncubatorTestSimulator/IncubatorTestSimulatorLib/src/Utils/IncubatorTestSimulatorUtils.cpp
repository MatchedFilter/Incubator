#include "Utils/IncubatorTestSimulatorUtils.h"

using namespace ITS;

SDL_Cursor *IncubatorTestSimulatorUtils::s_SdlCursors[SDL_NUM_SYSTEM_CURSORS] = { 0 };

void IncubatorTestSimulatorUtils::Initialize()
{
    s_SdlCursors[SDL_SYSTEM_CURSOR_ARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    s_SdlCursors[SDL_SYSTEM_CURSOR_IBEAM] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    s_SdlCursors[SDL_SYSTEM_CURSOR_WAIT] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
    s_SdlCursors[SDL_SYSTEM_CURSOR_CROSSHAIR] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    s_SdlCursors[SDL_SYSTEM_CURSOR_WAITARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZENWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZENESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZEWE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZENS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    s_SdlCursors[SDL_SYSTEM_CURSOR_SIZEALL] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    s_SdlCursors[SDL_SYSTEM_CURSOR_NO] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    s_SdlCursors[SDL_SYSTEM_CURSOR_HAND] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}

void IncubatorTestSimulatorUtils::SetCursor(SDL_SystemCursor cursorType)
{
    SDL_SetCursor(s_SdlCursors[cursorType]);
}
