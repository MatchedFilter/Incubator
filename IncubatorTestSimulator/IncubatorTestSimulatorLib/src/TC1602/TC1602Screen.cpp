#include "TC1602/TC1602Screen.h"

using namespace ITS;

static constexpr const char *TC1602Screen_FONT_PATH = "resources/fonts/Open_Sans/static/OpenSans-Light.ttf";
static constexpr const int32_t TC1602Screen_FONT_SIZE = 32;
static constexpr const char *TC1602Screen_IMAGE_PATH = "resources/images/TC1602.png";

static constexpr const uint8_t _2LINES_4_BIT_MODE_CMD = 0x28;
static constexpr const uint8_t AUTO_CURSOR_SHIFT_TO_RIGHT_CMD = 0x06;
static constexpr const uint8_t DISPLAY_ON_CMD = 0x0C;
static constexpr const uint8_t DISPLAY_OFF_CMD = 0x08;
static constexpr const uint8_t CLEAR_SCREEN_CMD = 0x01;
static constexpr const uint8_t GOTO_LINE_1_CMD = 0x80;
static constexpr const uint8_t GOTO_LINE_2_CMD = 0xC0;

static constexpr const uint8_t TC1602_CHAR_LOWER_I = 0x00;
static constexpr const uint8_t TC1602_CHAR_LOWER_U = 0x01;
static constexpr const uint8_t TC1602_CHAR_LOWER_O = 0x02;
static constexpr const uint8_t TC1602_CHAR_DEGREE_SYMBOL = 0xDF;

TC1602Screen::TC1602Screen() :
    m_Renderer { nullptr },
    m_TC1602ScreenFont { nullptr },
    m_TC1602ScreenSurface { nullptr },
    m_TC1602ScreenTexture { nullptr },
    m_Lines { 0 },
    m_bIsDisplayOn { false },
    m_bAutoCursorUsed { false },
    m_bTwoLinesUsed { false },
    m_CursorCount { 0 },
    m_MaxCursorSize { LINE_SIZE }
{
}

TC1602Screen::~TC1602Screen()
{
    if (m_TC1602ScreenSurface != nullptr)
    {
        SDL_FreeSurface(m_TC1602ScreenSurface);
    }
    if (m_TC1602ScreenTexture != nullptr)
    {
        SDL_DestroyTexture(m_TC1602ScreenTexture);
    }
    if (m_TC1602ScreenFont != nullptr)
    {
        TTF_CloseFont(m_TC1602ScreenFont);
    }
}

bool TC1602Screen::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos)
{
    bool bResult = true;
    m_Renderer = renderer;

    m_ImagePositionRect.x = xPos;
    m_ImagePositionRect.y = yPos;
    m_ImagePositionRect.w = 678;
    m_ImagePositionRect.h = 286;

    m_TextInitialPositionRect.x = m_ImagePositionRect.x + 60;
    m_TextInitialPositionRect.y = m_ImagePositionRect.y + 92;

    m_TC1602ScreenFont = TTF_OpenFont(TC1602Screen_FONT_PATH, TC1602Screen_FONT_SIZE);
    if (m_TC1602ScreenFont == nullptr)
    {
        bResult = false;
    }

    if (bResult)
    {
        m_TC1602ScreenSurface = IMG_Load(TC1602Screen_IMAGE_PATH);
        if (m_TC1602ScreenSurface == nullptr)
        {
            bResult = false;
        }
    }
    
    m_TC1602ScreenTexture = SDL_CreateTextureFromSurface(m_Renderer, m_TC1602ScreenSurface);
    return bResult;
}

void TC1602Screen::SendCommand(uint8_t command)
{
    switch (command)
    {
    case _2LINES_4_BIT_MODE_CMD:
        m_bTwoLinesUsed = true;
        m_MaxCursorSize = LINE_COUNT * LINE_SIZE;
        break;
    case AUTO_CURSOR_SHIFT_TO_RIGHT_CMD:
        m_bAutoCursorUsed = true;
        break;
    case DISPLAY_ON_CMD:
        m_bIsDisplayOn = true;
        break;
    case DISPLAY_OFF_CMD:
        m_bIsDisplayOn = false;
        break;
    case CLEAR_SCREEN_CMD:
        {
            memset(m_Lines, 0, sizeof(m_Lines));
            m_CursorCount = 0;
        }
        break;
    case GOTO_LINE_1_CMD:
        m_CursorCount = 0;
        break;
    case GOTO_LINE_2_CMD:
        m_CursorCount = LINE_SIZE % m_MaxCursorSize;
        break;
    default:
        break;
    }
}

void TC1602Screen::SendData(uint8_t data)
{
    switch (data)
    {
    case TC1602_CHAR_LOWER_I:
        m_Lines[m_CursorCount] = (char16_t)0x0131;
        break;

    case TC1602_CHAR_LOWER_U:
        m_Lines[m_CursorCount] = (char16_t)0x00FC;
        break;

    case TC1602_CHAR_LOWER_O:
        m_Lines[m_CursorCount] = (char16_t)0x00F6;
        break;

    case TC1602_CHAR_DEGREE_SYMBOL:
        m_Lines[m_CursorCount] = (char16_t)0x00B0;
        break;
    
    default:
        m_Lines[m_CursorCount] = data;
        break;
    }
    if (m_bAutoCursorUsed)
    {
        m_CursorCount = (m_CursorCount + 1) % m_MaxCursorSize;
    }
}

void TC1602Screen::Run()
{
    SDL_RenderCopy(m_Renderer, m_TC1602ScreenTexture, NULL, &m_ImagePositionRect);
    for (uint8_t i = 0; i < m_MaxCursorSize; i++)
    {
        SDL_Rect charRect;
        if (m_bTwoLinesUsed)
        {
            uint8_t columnNo = i % LINE_SIZE;
            uint8_t rowNo = i / LINE_SIZE; 
            charRect.x = m_TextInitialPositionRect.x + columnNo * CURSOR_WIDTH;
            charRect.y = m_TextInitialPositionRect.y + rowNo * ROW_WIDTH;
            charRect.w = CURSOR_WIDTH;
            charRect.h = ROW_WIDTH;
        }
        else
        {
            charRect.x = m_TextInitialPositionRect.x + i * CURSOR_WIDTH;
            charRect.y = m_TextInitialPositionRect.y + ROW_WIDTH / 2;
            charRect.w = CURSOR_WIDTH;
            charRect.h = ROW_WIDTH;
        }
        if (m_bIsDisplayOn)
        {
            if (m_Lines[i] == 0 )
            {
                constexpr const Uint16 EMPTY_STRING[] = {(Uint16)' ', (Uint16)'\0' }; 
                SDL_Surface *surfaceText = TTF_RenderUNICODE_LCD(m_TC1602ScreenFont ,EMPTY_STRING, {0, 0, 0}, {0, 0, 255});
                SDL_Texture *textureText = SDL_CreateTextureFromSurface(m_Renderer, surfaceText);
                SDL_FreeSurface(surfaceText);
                SDL_RenderCopy(m_Renderer, textureText, NULL, &charRect);
                SDL_DestroyTexture(textureText);
            }
            else
            {
                Uint16 charToPrint[] = {m_Lines[i], '\0'};
                SDL_Surface *surfaceText = TTF_RenderUNICODE_LCD(m_TC1602ScreenFont ,charToPrint, {0, 0, 0}, {0, 0, 255});
                SDL_Texture *textureText = SDL_CreateTextureFromSurface(m_Renderer, surfaceText);
                SDL_FreeSurface(surfaceText);
                SDL_RenderCopy(m_Renderer, textureText, NULL, &charRect);
                SDL_DestroyTexture(textureText);
            }
        }
    }
}
