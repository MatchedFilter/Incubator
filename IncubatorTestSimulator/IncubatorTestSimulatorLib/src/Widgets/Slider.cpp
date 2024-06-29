#include "Widgets/Slider.h"
#include "Utils/IncubatorTestSimulatorUtils.h"
#include <cstring>

using namespace ITS;

Slider::Slider() : 
    m_Renderer { nullptr },
    m_SliderValue { 0 },
    m_bHovered { false },
    m_bPressed { false },
    m_SliderFrameRect { 0, 0, 120, 7 },
    m_SliderRect { 0, 0, 60, 7 },
    m_SliderColor { 80, 200, 80, 255 },
    m_SliderBgFrameColor { 80, 200, 80, 255 }
{
}

void Slider::Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos, int32_t width, int32_t height, int32_t sliderWidth)
{
    m_SliderFrameRect.x = xPos;
    m_SliderFrameRect.y = yPos;
    m_SliderFrameRect.w = width;
    m_SliderFrameRect.h = height;
    m_SliderRect.x = m_SliderFrameRect.x + m_SliderFrameRect.w / 2;
    m_SliderRect.y = m_SliderFrameRect.y;
    m_SliderRect.w = sliderWidth;
    m_SliderRect.h = m_SliderFrameRect.h;
    m_SliderColor.r = m_SliderBgFrameColor.r = 80;
    m_SliderColor.g = m_SliderBgFrameColor.g = 200;
    m_SliderColor.b = m_SliderBgFrameColor.b = 80;
    m_SliderColor.a = m_SliderBgFrameColor.a = 255;
    m_Renderer = renderer;

    m_SliderValue = (uint32_t)(m_SliderRect.x - m_SliderFrameRect.x - 10);
    m_SliderRect.x = m_SliderRect.x - 10;
}

void Slider::SetSliderColor(SDL_Color color)
{
    memcpy(&m_SliderColor ,&color, sizeof(SDL_Color));
}

void Slider::SetSliderBgFrameColor(SDL_Color color)
{
    memcpy(&m_SliderBgFrameColor ,&color, sizeof(SDL_Color));
}


void Slider::HandleEvents(const SDL_Event &event)
{

    if (event.motion.x < m_SliderRect.x + m_SliderRect.w && event.motion.x > m_SliderRect.x && 
        event.motion.y < m_SliderRect.y + m_SliderRect.h && event.motion.y > m_SliderRect.y)
    {
        m_bHovered = true;
        IncubatorTestSimulatorUtils::SetCursor(SDL_SYSTEM_CURSOR_HAND);
    }
    else
    {
        m_bHovered = false;
        IncubatorTestSimulatorUtils::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
    }
    
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        if (m_bHovered)
        {
            m_bPressed = true;
        }
    }
        break;

    case SDL_MOUSEBUTTONUP:
        m_bPressed = false;
        break;
    
    default:
        break;
    }

    if (m_bPressed)
    {
        int xPos = event.motion.x;
        if (xPos > m_SliderFrameRect.x + 110)
        {
            xPos = m_SliderFrameRect.x + 110;
        }
        if (xPos < m_SliderFrameRect.x + 10)
        {
            xPos = m_SliderFrameRect.x + 10;
        }
        m_SliderValue = (uint32_t)(xPos - m_SliderFrameRect.x - 10);
        m_SliderRect.x = xPos - 10;
    }
}

void Slider::Run()
{
    SDL_SetRenderDrawColor(m_Renderer, m_SliderBgFrameColor.r, m_SliderBgFrameColor.g, m_SliderBgFrameColor.b, m_SliderBgFrameColor.a);
    SDL_RenderDrawRect(m_Renderer, &m_SliderFrameRect);
    SDL_SetRenderDrawColor(m_Renderer, m_SliderColor.r, m_SliderColor.g, m_SliderColor.b, m_SliderColor.a);
    SDL_RenderFillRect(m_Renderer, &m_SliderRect);
}
