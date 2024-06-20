#include "Incubator/TimerTasks/IncubatorSecondPeriodicTimerTaskHandler.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/Storage/Storage.h"

IncubatorSecondPeriodicTimerTaskHandler::IncubatorSecondPeriodicTimerTaskHandler(IncubatorData *incubatorData) : m_IncubatorData { incubatorData },
    m_InvalidHumidityCounter { 0 }
{
}

void IncubatorSecondPeriodicTimerTaskHandler::MeasureHumidity()
{
	Sensors::DHT11Data dht11Data;
    if (m_Dht11.RetreiveData(dht11Data))
    {
        m_IncubatorData->m_HumiditySensorStatus = SENSOR_STATUS_NO_ERROR;
        m_InvalidHumidityCounter = 0;
        m_IncubatorData->m_HumidityInPercentage = dht11Data.m_HumidityInPercentage;
    }
    else
    {
        m_InvalidHumidityCounter++;
        if (m_InvalidHumidityCounter > ALLOWED_INVALID_HUMIDITY_COUNT)
        {
            m_InvalidHumidityCounter = ALLOWED_INVALID_HUMIDITY_COUNT;
            m_IncubatorData->m_HumiditySensorStatus = SENSOR_STATUS_ERROR;
        }
    }
}

void IncubatorSecondPeriodicTimerTaskHandler::OnTimeout(TaskID taskId)
{
    TimeInfoData timeInfoData;
    if (Storage::Query(timeInfoData))
    {
        uint32_t currentTimestampInSeconds = static_cast<uint32_t>(TimeUtils::GetTimestampInMilliseconds() / 1000);
        timeInfoData.m_IncubatorCurrentTimestampInSeconds = currentTimestampInSeconds;
        m_IncubatorData->m_CurrentTimestampInSeconds = currentTimestampInSeconds;
    }
    MeasureHumidity();
}
