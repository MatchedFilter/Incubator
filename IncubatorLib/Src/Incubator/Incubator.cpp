#include "Incubator/Incubator.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/TimeUtils/TimerTask/TimerTaskController.h"
#include "Incubator/Utils/IncubatorUtils.h"
#include "Incubator/Logger/Logger.h"

Incubator::Incubator(const char* incubatorVersion) :
    m_UIComponent { incubatorVersion },
    m_IncubatorSecondPeriodicTimerTaskHandler { &m_IncubatorData },
    m_IncubatorTemperatureReadingTimerTaskHandler { &m_IncubatorData },
    m_IncubatorStorageUpdatingTimerTaskHandler { &m_IncubatorData }
{
}

void Incubator::Initialize()
{
    TimeUtils::SleepInMilliseconds(2000);
    m_IncubatorTemperatureReadingTimerTaskHandler.Initialize();
    m_UIComponent.Initialize();
    Storage::Initialize();
    IncubatorUtils::ReadStorageData(m_IncubatorData);
    if (m_IncubatorData.m_MemoryDeviceErrorState == ERROR_STATE_NO_ERROR)
    {
        LOG_DEBUG("____________________PARAMETERS_________________");
        LOG_DEBUG("Humidity:");
        LOG_DEBUG("    Desired: %d", m_IncubatorData.m_HumidityDesired);
        LOG_DEBUG("    Start: %d", m_IncubatorData.m_HumidityStart);
        LOG_DEBUG("    End: %d", m_IncubatorData.m_HumidityEnd);
        LOG_DEBUG("Temperature:");
        LOG_DEBUG("    Desired: %d", m_IncubatorData.m_TemperatureDesired);
        LOG_DEBUG("    Start: %d", m_IncubatorData.m_TemperatureStart);
        LOG_DEBUG("    End: %d", m_IncubatorData.m_TemperatureEnd);
        LOG_DEBUG("TimeInfo:");
        LOG_DEBUG("    Current timestamp in seconds: %d", m_IncubatorData.m_CurrentTimestampInSeconds);
        LOG_DEBUG("    Total day count: %d", m_IncubatorData.m_TotalIncubationDayCount);
        LOG_DEBUG("    Motor off day count: %d", m_IncubatorData.m_MotorOffDayCount);
        LOG_DEBUG("_______________________________________________");

        TimeUtils::SetTimestampInMilliseconds(static_cast<int64_t>(m_IncubatorData.m_CurrentTimestampInSeconds) * 1000);
    }
    TaskID secondPeriodicTimerTaskId = TimerTaskController::RegisterTask(&m_IncubatorSecondPeriodicTimerTaskHandler, 1000, true);
    TaskID temperatureReadingTimerTaskId = TimerTaskController::RegisterTask(&m_IncubatorTemperatureReadingTimerTaskHandler, 150, true);
    TaskID storageUpdatingTimerTaskId = TimerTaskController::RegisterTask(&m_IncubatorStorageUpdatingTimerTaskHandler, 500, true);

    TimerTaskController::StartTask(secondPeriodicTimerTaskId);
    TimerTaskController::StartTask(temperatureReadingTimerTaskId);
    TimerTaskController::StartTask(storageUpdatingTimerTaskId);
}

void Incubator::GetJoystickInfo()
{
    constexpr int32_t JOYSTICK_UPPER_THRESHOLD = 2900;
    constexpr int32_t JOYSTICK_LOWER_THRESHOLD = 1100;
    Sensors::JoystickData joystickData = m_Joystick.GetJoystickValues();
    m_IncubatorData.m_bIsButtonClicked = false;
    if (joystickData.m_PressState == Sensors::JOYSTICK_PRESS_STATE_CLICKED)
    {
        m_IncubatorData.m_bIsButtonClicked = true;
    }

    m_IncubatorData.m_bIsButtonUp = false;
    m_IncubatorData.m_bIsButtonDown = false;
    m_IncubatorData.m_bIsButtonRight = false;
    m_IncubatorData.m_bIsButtonLeft = false;

    if (joystickData.m_RightPosition > JOYSTICK_UPPER_THRESHOLD)
    {
        if (!(m_LastJoystickData.m_RightPosition > JOYSTICK_UPPER_THRESHOLD))
        {
            m_IncubatorData.m_bIsButtonRight = true;
        }
    }
    else if (joystickData.m_RightPosition < JOYSTICK_LOWER_THRESHOLD)
    {
        if (!(m_LastJoystickData.m_RightPosition < JOYSTICK_LOWER_THRESHOLD))
        {
            m_IncubatorData.m_bIsButtonLeft = true;
        }
    }
    else
    {
    }

    if (joystickData.m_UpPosition > JOYSTICK_UPPER_THRESHOLD)
    {
        if (!(m_LastJoystickData.m_UpPosition > JOYSTICK_UPPER_THRESHOLD))
        {
            m_IncubatorData.m_bIsButtonUp = true;
        }
    }
    else if (joystickData.m_UpPosition < JOYSTICK_LOWER_THRESHOLD)
    {
        if (!(m_LastJoystickData.m_UpPosition < JOYSTICK_LOWER_THRESHOLD))
        {
            m_IncubatorData.m_bIsButtonDown = true;
        }
    }
    else
    {
    }
    m_LastJoystickData.m_PressState = joystickData.m_PressState;
    m_LastJoystickData.m_RightPosition = joystickData.m_RightPosition;
    m_LastJoystickData.m_UpPosition = joystickData.m_UpPosition;
    
}

void Incubator::AdjustTemperature()
{
    int32_t temperatureHighThreshold = m_IncubatorData.m_TemperatureEnd;
    int32_t temperatureLowThreshold = m_IncubatorData.m_TemperatureStart;
    if (IncubatorUtils::IsInMotorsOffTime(m_IncubatorData))
    {
        temperatureHighThreshold = m_IncubatorData.m_MotorsOffTemperatureEnd;
        temperatureLowThreshold = m_IncubatorData.m_MotorsOffTemperatureStart;
    }
    if (m_IncubatorData.m_TemperatureInDeciDegree > temperatureHighThreshold)
    {
        m_IncubatorController.TurnOffHeater();
    }
    else if (m_IncubatorData.m_TemperatureInDeciDegree < temperatureLowThreshold)
    {
        m_IncubatorController.TurnOnHeater();
    }
    else
    {
    }
}

void Incubator::AdjustHumidity()
{

    int32_t humidityHighThreshold = m_IncubatorData.m_HumidityEnd;
    int32_t humidityLowThreshold = m_IncubatorData.m_HumidityStart;
    if (IncubatorUtils::IsInMotorsOffTime(m_IncubatorData))
    {
        humidityHighThreshold = m_IncubatorData.m_MotorsOffHumidityEnd;
        humidityLowThreshold = m_IncubatorData.m_MotorsOffHumidityStart;
    }

    if (m_IncubatorData.m_HumidityInPercentage > humidityHighThreshold)
    {
        m_IncubatorController.TurnOffHumidityGenerator();
    }
    else if (m_IncubatorData.m_HumidityInPercentage < humidityLowThreshold)
    {
        m_IncubatorController.TurnOnHumidityGenerator();
    }
    else
    {
    }
}


void Incubator::Run()
{
    GetJoystickInfo();
    m_UIComponent.Update(m_IncubatorData);
    AdjustTemperature();
    AdjustHumidity();
    TimerTaskController::Run();
}
