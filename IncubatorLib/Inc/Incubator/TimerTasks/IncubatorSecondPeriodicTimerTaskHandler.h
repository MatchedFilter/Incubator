#ifndef _INCUBATORSECONDPERIODICTIMERTASKHANDLER_H_
#define _INCUBATORSECONDPERIODICTIMERTASKHANDLER_H_
#include "Incubator/TimeUtils/TimerTask/ITimerTaskHandler.h"
#include "DHT11/DHT11.h"
#include "Incubator/IncubatorData.h"
class IncubatorSecondPeriodicTimerTaskHandler : public ITimerTaskHandler
{
public:
    IncubatorSecondPeriodicTimerTaskHandler(IncubatorData *incubatorData);
    ~IncubatorSecondPeriodicTimerTaskHandler() = default;
    virtual void OnTimeout(TaskID taskId) override;

private:
    IncubatorData *m_IncubatorData;
    Sensors::DHT11 m_Dht11;
    uint8_t m_InvalidHumidityCounter;
    static constexpr const int32_t ALLOWED_INVALID_HUMIDITY_COUNT = 3;

private:
    void MeasureHumidity();

};
#endif // _INCUBATORSECONDPERIODICTIMERTASKHANDLER_H_