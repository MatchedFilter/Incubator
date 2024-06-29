#ifndef _ITS_SLIDER_H_
#define _ITS_SLIDER_H_
#include "SDL2/SDL.h"
#include <cinttypes>
namespace ITS
{
    class Slider
    {
    public:
        Slider();
        ~Slider() = default;
        void Initialize(SDL_Renderer *renderer, int32_t xPos = 0, int32_t yPos = 0, int32_t width = 120, int32_t height = 7, int32_t sliderWidth = 20);
        void SetSliderColor(SDL_Color color);
        void SetSliderBgFrameColor(SDL_Color color);
        inline uint32_t GetSliderValue() const { return m_SliderValue; }
        void HandleEvents(const SDL_Event &event);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        uint32_t m_SliderValue;
        bool m_bHovered;
        bool m_bPressed;
        SDL_Rect m_SliderFrameRect;
        SDL_Rect m_SliderRect;
        SDL_Color m_SliderColor;
        SDL_Color m_SliderBgFrameColor;
    };
} // namespace ITS

#endif // _ITS_SLIDER_H_