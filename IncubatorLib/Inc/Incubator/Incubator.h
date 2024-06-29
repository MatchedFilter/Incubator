#ifndef _INCUBATOR_H_
#define _INCUBATOR_H_
#include "DHT11/DHT11.h"
#include "NTC/NTC.h"
#include "Joystick/Joystick.h"
#include "Storage/Storage.h"
#include "GUI/UIComponent.h"
#include "TimerTasks/IncubatorSecondPeriodicTimerTaskHandler.h"
#include "TimerTasks/IncubatorTemperatureReadingTimerTaskHandler.h"
#include "TimerTasks/IncubatorStorageUpdatingTimerTaskHandler.h"
#include "IncubatorController/IncubatorController.h"

class Incubator
{
public:
    Incubator(const char* incubatorVersion);
    ~Incubator() = default;
    void Initialize();
    void Run();

private:
    Sensors::Joystick m_Joystick;
    GUI::UIComponent m_UIComponent;
    IncubatorData m_IncubatorData;

    IncubatorSecondPeriodicTimerTaskHandler m_IncubatorSecondPeriodicTimerTaskHandler;
    IncubatorTemperatureReadingTimerTaskHandler m_IncubatorTemperatureReadingTimerTaskHandler;
    IncubatorStorageUpdatingTimerTaskHandler m_IncubatorStorageUpdatingTimerTaskHandler;
    IC::IncubatorController m_IncubatorController;

private:
    Sensors::JoystickData m_LastJoystickData;

private:
    void GetJoystickInfo();
    void AdjustTemperature();
    void AdjustHumidity();
};



#endif // _INCUBATOR_H_
