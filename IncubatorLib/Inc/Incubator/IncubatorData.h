#ifndef _INCUBATORDATA_H_
#define _INCUBATORDATA_H_
#include <cinttypes>

enum EnumErrorState : uint8_t
{
    ERROR_STATE_NO_ERROR = 0,
    ERROR_STATE_ERROR
};

enum EnumSensorStatus : uint8_t
{
    SENSOR_STATUS_NO_ERROR = 0,
    SENSOR_STATUS_INITIALIZATION = 1,
    SENSOR_STATUS_ERROR = 2
};

struct IncubatorData
{
public:
    uint8_t m_HumidityInPercentage;
    uint8_t m_HumidityStart;
    uint8_t m_HumidityEnd;
    uint8_t m_HumidityDesired;
    uint8_t m_MotorsOffHumidityStart;
    uint8_t m_MotorsOffHumidityEnd;
    uint8_t m_MotorsOffHumidityDesired;
    int32_t m_TemperatureInDeciDegree;
    int32_t m_TemperatureStart;
    int32_t m_TemperatureEnd;
    int32_t m_TemperatureDesired;
    int32_t m_MotorsOffTemperatureStart;
    int32_t m_MotorsOffTemperatureEnd;
    int32_t m_MotorsOffTemperatureDesired;
    uint32_t m_CurrentTimestampInSeconds;
    uint8_t m_TotalIncubationDayCount;
    uint8_t m_MotorOffDayCount;
    bool m_bIsButtonUp;
    bool m_bIsButtonDown;
    bool m_bIsButtonRight;
    bool m_bIsButtonLeft;
    bool m_bIsButtonClicked;
    EnumErrorState m_MemoryDeviceErrorState;
    EnumSensorStatus m_HumiditySensorStatus;
    EnumSensorStatus m_TemperatureSensorStatus;

    IncubatorData() { Reset(); }

    ~IncubatorData() = default;

    void Reset()
    {
        m_HumidityInPercentage = 0;
        m_HumidityStart = 0;
        m_HumidityEnd = 0;
        m_HumidityDesired = 0;
        m_MotorsOffHumidityStart = 0;
        m_MotorsOffHumidityEnd = 0;
        m_MotorsOffHumidityDesired = 0;
        m_TemperatureInDeciDegree = 0;
        m_TemperatureStart = 0;
        m_TemperatureEnd = 0;
        m_TemperatureDesired = 0;
        m_MotorsOffTemperatureStart = 0;
        m_MotorsOffTemperatureEnd = 0;
        m_MotorsOffTemperatureDesired = 0;
        m_CurrentTimestampInSeconds = 0;
        m_TotalIncubationDayCount = 0;
        m_MotorOffDayCount = 0;
        m_bIsButtonUp = false;
        m_bIsButtonDown = false;
        m_bIsButtonRight = false;
        m_bIsButtonLeft = false;
        m_bIsButtonClicked = false;
        m_MemoryDeviceErrorState = ERROR_STATE_NO_ERROR;
        m_HumiditySensorStatus = SENSOR_STATUS_INITIALIZATION;
        m_TemperatureSensorStatus = SENSOR_STATUS_INITIALIZATION;
    }
};

#endif // _INCUBATORDATA_H_