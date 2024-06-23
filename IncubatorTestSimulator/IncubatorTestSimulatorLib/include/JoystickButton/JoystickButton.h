#ifndef _ITS_JOYSTICKBUTTON_H_
#define _ITS_JOYSTICKBUTTON_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Joystick/Joystick.h"

namespace ITS
{
    class JoystickButton
    {
    public:
        JoystickButton();
        ~JoystickButton();
        bool Initialize(SDL_Renderer *renderer, int32_t xPos, int32_t yPos);
        void GetJoystickData(bool &upKeyPressed, bool &downKeyPressed, bool &rightKeyPressed, bool &leftKeyPressed);
        uint8_t GetJoystickButtonState();
        void HandleEvents(const SDL_Event &event);
        void Run();

    private:
        SDL_Renderer *m_Renderer;
        SDL_Texture *m_IdleTexture;
        SDL_Texture *m_UpTexture;
        SDL_Texture *m_DownTexture;
        SDL_Texture *m_RightTexture;
        SDL_Texture *m_LeftTexture;
        SDL_Rect m_JoystickRect;
        SDL_Rect m_JoystickPressedRect;

        bool m_UpKeyPressed;
        bool m_DownKeyPressed;
        bool m_RightKeyPressed;
        bool m_LeftKeyPressed;
        Sensors::EnumJoystickPressState m_JoystickPressState;


    };
} // namespace ITS

#endif // _ITS_JOYSTICKBUTTON_H_