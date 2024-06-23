#ifndef _ITS_TC1602SCREEN_H_
#define _ITS_TC1602SCREEN_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

namespace ITS
{
    class TC1602Screen
    {
    public:
        TC1602Screen();
        ~TC1602Screen();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        void SendCommand(uint8_t command);
        void SendData(uint8_t data);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        TTF_Font *m_TC1602ScreenFont;
        SDL_Surface *m_TC1602ScreenSurface;
        SDL_Texture *m_TC1602ScreenTexture;
        SDL_Rect m_ImagePositionRect;
        SDL_Rect m_TextInitialPositionRect;
        static constexpr const int32_t LINE_COUNT = 2;
        static constexpr const int32_t LINE_SIZE = 16;
        static constexpr const int32_t CURSOR_WIDTH = 35;
        static constexpr const int32_t ROW_WIDTH = 56;
        static constexpr const int32_t LINE_STRING_SIZE = LINE_SIZE * LINE_COUNT + sizeof('\0');
        char16_t m_Lines[LINE_STRING_SIZE];

    private:
        bool m_bIsDisplayOn;
        bool m_bAutoCursorUsed;
        bool m_bTwoLinesUsed;
        uint8_t m_CursorCount;
        uint8_t m_MaxCursorSize;

    };
} // namespace ITS

#endif // _ITS_TC1602SCREEN_H_