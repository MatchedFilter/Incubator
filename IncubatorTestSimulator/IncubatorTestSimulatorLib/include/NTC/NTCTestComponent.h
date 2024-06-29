#ifndef _ITS_NTCTESTCOMPONENT_H_
#define _ITS_NTCTESTCOMPONENT_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Widgets/Slider.h"

namespace ITS
{
    class NTCTestComponent
    {
    public:
        NTCTestComponent();
        ~NTCTestComponent();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        inline double GetTemperature() { return m_TemperatureInDegree; }
        void HandleEvents(const SDL_Event &event);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        SDL_Texture *m_ImageTexture;
        SDL_Texture *m_TextTexture;
        SDL_Rect m_ImageRect;
        SDL_Rect m_TextRect;
        Slider m_Slider;
        TTF_Font *m_NTCFont;

    private:
        double m_TemperatureInDegree;
        static const uint8_t TEMPERATURE_STRING_SIZE = 16;
        char m_TemperatureStringValue[TEMPERATURE_STRING_SIZE];

    };
} // namespace ITS

#endif // _ITS_NTCTESTCOMPONENT_H_