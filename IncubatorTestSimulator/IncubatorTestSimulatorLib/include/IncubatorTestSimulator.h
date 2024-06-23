#ifndef _ITS_INCUBATORTESTSIMULATOR_H_
#define _ITS_INCUBATORTESTSIMULATOR_H_
#include <SDL2/SDL.h>
#include "TC1602/TC1602Screen.h"
#include "JoystickButton/JoystickButton.h"

/**
 * @brief Incubator Test Simulator
*/
namespace ITS
{
    class IncubatorTestSimulator
    {
    public:
        IncubatorTestSimulator();
        ~IncubatorTestSimulator();
        void SendDataToTC1602(uint8_t data);
        void SendCommandToTC1602(uint8_t command);
        inline int64_t GetSimulatorStartTimestampInMillisecond() const { return m_SimulatorStartTimestampInMillisecond; }
        void SetSimulatorStartTimestampInMillisecond(int64_t timestampInMillisecond) { m_SimulatorStartTimestampInMillisecond = timestampInMillisecond; }
        bool GetHumidityPercentageAndTemperatureInCelcius(uint8_t &humidityPercentage, uint8_t &temperatureInCelcius);
        bool GetTemperatureInCelcius(double &temperatureInCelcius);
        void GetJoystickData(bool &upKeyPressed, bool &downKeyPressed, bool &rightKeyPressed, bool &leftKeyPressed);
        uint8_t GetJoystickButtonState();

        void Initialize();
        void HandleEvents(SDL_Event &event);
        void Run();
    
    private:
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;
        TC1602Screen m_TC1602Screen;
        JoystickButton m_JoystickButton;
        int64_t m_SimulatorStartTimestampInMillisecond;
        bool m_UpKeyPressed;
        bool m_DownKeyPressed;
        bool m_RightKeyPressed;
        bool m_LeftKeyPressed;
        uint8_t m_OKeyState;

    private:
        void InitializeTime();
        void InitializeEeprom24C32();
        void CreateEeprom24C32();
    };
} // namespace ITS

#endif // _ITS_INCUBATORTESTSIMULATOR_H_