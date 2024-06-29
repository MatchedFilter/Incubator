#ifndef _ITS_DHT11TESTCOMPONENT_H_
#define _ITS_DHT11TESTCOMPONENT_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Widgets/Slider.h"

namespace ITS
{
    class DHT11TestComponent
    {
    public:
        DHT11TestComponent();
        ~DHT11TestComponent();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        void GetHumidityPercentageAndTemperature(uint8_t &humidityPercentage, uint8_t &temperature);
        void HandleEvents(const SDL_Event &event);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        SDL_Texture *m_ImageTexture;
        SDL_Texture *m_TextTexture;
        SDL_Rect m_ImageRect;
        SDL_Rect m_TextRect;
        Slider m_Slider;
        TTF_Font *m_DHT11Font;

    private:
        int32_t m_HumidityPercentage;
        static const uint8_t HUMIDITY_STRING_SIZE = 16;
        char m_HumidityStringValue[HUMIDITY_STRING_SIZE];
        bool m_bHovered;
        bool m_bPressed;
        bool m_bReleased;

    };
} // namespace ITS

#endif // _ITS_DHT11TESTCOMPONENT_H_