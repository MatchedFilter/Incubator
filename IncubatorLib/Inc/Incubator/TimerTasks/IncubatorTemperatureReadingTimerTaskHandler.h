#ifndef _INCUBATORTEMPERATUREREADINGTIMERTASKHANDLER_H_
#define _INCUBATORTEMPERATUREREADINGTIMERTASKHANDLER_H_
#include "Incubator/TimeUtils/TimerTask/ITimerTaskHandler.h"
#include "NTC/NTC.h"
#include "Incubator/IncubatorData.h"

class IncubatorTemperatureReadingTimerTaskHandler : public ITimerTaskHandler
{
public:
    IncubatorTemperatureReadingTimerTaskHandler(IncubatorData *incubatorData);
    ~IncubatorTemperatureReadingTimerTaskHandler() = default;
    void Initialize();
    virtual void OnTimeout(TaskID taskId) override;

private:
    IncubatorData *m_IncubatorData;
    Sensors::NTC m_NtcSensor;
    static constexpr const int32_t MOVING_WINDOW_SIZE = 5;
    double m_TemperatureWindow[MOVING_WINDOW_SIZE];
    uint8_t m_CurrentWindowCounter;
    bool m_bIsInitialized;
    static constexpr const uint8_t MAX_ALLOWED_INVALID_READING = 3;
    uint8_t m_InvalidReadingCounter;

private:
    void MeasureTemperature();
    double GetAvarageTemperature();

};
#endif // _INCUBATORTEMPERATUREREADINGTIMERTASKHANDLER_H_