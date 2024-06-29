#ifndef _ITS_INCUBATORTESTSIMULATOR_H_
#define _ITS_INCUBATORTESTSIMULATOR_H_
#include <SDL2/SDL.h>
#include "TC1602/TC1602Screen.h"
#include "JoystickButton/JoystickButton.h"
#include "DHT11/DHT11TestComponent.h"
#include "NTC/NTCTestComponent.h"
#include "Output/OutputSensorTestComponent.h"

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
        inline void TurnOnHumidityGenerator() { m_HumidityGeneratorTestComponent.TurnOn(); }
        inline void TurnOffHumidityGenerator() { m_HumidityGeneratorTestComponent.TurnOff();}
        inline void TurnOnHeater() { m_CarbonFiberHeaterTestComponent.TurnOn(); }
        inline void TurnOffHeater() { m_CarbonFiberHeaterTestComponent.TurnOff();}
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
        DHT11TestComponent m_DHT11TestComponent;
        NTCTestComponent m_NTCTestComponent;
        OutputSensorTestComponent m_HumidityGeneratorTestComponent;
        OutputSensorTestComponent m_CarbonFiberHeaterTestComponent;

    private:
        void InitializeTime();
        void InitializeEeprom24C32();
        void CreateEeprom24C32();
    };
} // namespace ITS

#endif // _ITS_INCUBATORTESTSIMULATOR_H_