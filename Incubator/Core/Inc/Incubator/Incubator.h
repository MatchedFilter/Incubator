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

class Incubator
{
public:
    Incubator();
    ~Incubator() = default;
    void Initialize();
    void Run();

private:
    Sensors::DHT11 m_Dht11;
    Sensors::NTC m_NtcSensor;
    Sensors::Joystick m_Joystick;
    GUI::UIComponent m_UIComponent;
    IncubatorData m_IncubatorData;

    IncubatorSecondPeriodicTimerTaskHandler m_IncubatorSecondPeriodicTimerTaskHandler;
    IncubatorTemperatureReadingTimerTaskHandler m_IncubatorTemperatureReadingTimerTaskHandler;
    IncubatorStorageUpdatingTimerTaskHandler m_IncubatorStorageUpdatingTimerTaskHandler;

private:
    void GetJoystickInfo();
};



#endif // _INCUBATOR_H_
