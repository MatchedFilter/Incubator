#include "Incubator/TimerTasks/IncubatorTemperatureReadingTimerTaskHandler.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/Storage/Storage.h"

IncubatorTemperatureReadingTimerTaskHandler::IncubatorTemperatureReadingTimerTaskHandler(IncubatorData *incubatorData) :
    m_IncubatorData { incubatorData },
    m_TemperatureWindow { 0 },
    m_CurrentWindowCounter { 0 },
    m_bIsInitialized { false },
    m_InvalidReadingCounter { 0 }
{
}

void IncubatorTemperatureReadingTimerTaskHandler::Initialize()
{
    m_NtcSensor.Initialize();
}

double IncubatorTemperatureReadingTimerTaskHandler::GetAvarageTemperature()
{
    double avarageTemperature = 0.0;
    for (uint8_t i = 0; i < MOVING_WINDOW_SIZE; i++)
    {
        avarageTemperature += m_TemperatureWindow[i];
    }
    avarageTemperature = avarageTemperature / MOVING_WINDOW_SIZE;
    return avarageTemperature;
}


void IncubatorTemperatureReadingTimerTaskHandler::OnTimeout(TaskID taskId)
{
    double temperature;
    if (m_NtcSensor.CalculateTemperatureInCelcius(temperature))
    {
        m_InvalidReadingCounter = 0;
        m_TemperatureWindow[m_CurrentWindowCounter] = temperature;
        if (!m_bIsInitialized)
        {
            m_CurrentWindowCounter++;
            m_IncubatorData->m_TemperatureSensorStatus = SENSOR_STATUS_INITIALIZATION;
            if (m_CurrentWindowCounter == MOVING_WINDOW_SIZE)
            {
                m_CurrentWindowCounter = 0;
                m_bIsInitialized = true;
                m_IncubatorData->m_TemperatureSensorStatus = SENSOR_STATUS_NO_ERROR;
                m_IncubatorData->m_TemperatureInDeciDegree = static_cast<int32_t>(GetAvarageTemperature() * 10);
            }
        }
        else
        {
            m_IncubatorData->m_TemperatureSensorStatus = SENSOR_STATUS_NO_ERROR;
            m_IncubatorData->m_TemperatureInDeciDegree = static_cast<int32_t>(GetAvarageTemperature() * 10);
            m_CurrentWindowCounter = (m_CurrentWindowCounter + 1) % MOVING_WINDOW_SIZE;
        }
    }
    else
    {
        m_InvalidReadingCounter++;
        if (m_InvalidReadingCounter > MAX_ALLOWED_INVALID_READING)
        {
            m_IncubatorData->m_TemperatureSensorStatus = SENSOR_STATUS_ERROR;
        }
    }
}
