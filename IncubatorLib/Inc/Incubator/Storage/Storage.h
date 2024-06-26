#ifndef _STORAGE_H_
#define _STORAGE_H_
#include <cinttypes>
#include "EEPROM24C/EEPROM24C.h"

struct HumidityData
{
    uint8_t m_HumidityStartPercentage;
    uint8_t m_HumidityEndPercentage;
    uint8_t m_MotorsOffHumidityStartPercentage;
    uint8_t m_MotorsOffHumidityEndPercentage;
    HumidityData() : m_HumidityStartPercentage { 50 }, m_HumidityEndPercentage { 55 },
    m_MotorsOffHumidityStartPercentage { 65 }, m_MotorsOffHumidityEndPercentage { 70 } { }
    bool Serialize(uint8_t *buffer, uint16_t size) const;
    bool Deserialize(const uint8_t *buffer, uint16_t size);
    static constexpr const uint8_t BUFFER_SIZE = sizeof(m_HumidityStartPercentage) + sizeof(m_HumidityEndPercentage)
        + sizeof(m_MotorsOffHumidityStartPercentage) + sizeof(m_MotorsOffHumidityEndPercentage);
    ~HumidityData() = default;
};

struct TemperatureData
{
    int16_t m_TemperatureStartInDeciDegrees;
    int16_t m_TemperatureEndInDeciDegrees;
    int16_t m_MotorsOffTemperatureStartInDeciDegrees;
    int16_t m_MotorsOffTemperatureEndInDeciDegrees;
    TemperatureData() : m_TemperatureStartInDeciDegrees { 375 }, m_TemperatureEndInDeciDegrees { 380 },
        m_MotorsOffTemperatureStartInDeciDegrees { 368 }, m_MotorsOffTemperatureEndInDeciDegrees { 372 } { }
    bool Serialize(uint8_t *buffer, uint16_t size) const;
    bool Deserialize(const uint8_t *buffer, uint16_t size);
    static constexpr const uint8_t BUFFER_SIZE = sizeof(m_TemperatureStartInDeciDegrees) + sizeof(m_TemperatureEndInDeciDegrees)
        + sizeof(m_MotorsOffTemperatureStartInDeciDegrees) + sizeof(m_MotorsOffTemperatureEndInDeciDegrees);
    ~TemperatureData() = default;
};

struct TimeInfoData
{
    uint32_t m_IncubatorCurrentTimestampInSeconds;
    uint8_t m_TotalDayCount;
    uint8_t m_MotorOffDayCount;
    TimeInfoData() : m_IncubatorCurrentTimestampInSeconds { 0 }, m_TotalDayCount { 21 }, m_MotorOffDayCount { 3 } { }
    bool Serialize(uint8_t *buffer, uint16_t size) const;
    bool Deserialize(const uint8_t *buffer, uint16_t size);
    static constexpr const uint8_t BUFFER_SIZE = sizeof(m_IncubatorCurrentTimestampInSeconds)
        + sizeof(m_TotalDayCount) + sizeof(m_MotorOffDayCount);
    ~TimeInfoData() = default;
};

class Storage
{
public:
    Storage() = default;
    ~Storage() = default;
    static void Initialize();
    static void Reset();
    static bool Query(HumidityData &humidityData);
    static bool Write(const HumidityData &humidityData);
    static bool Query(TemperatureData &temperatureData);
    static bool Write(const TemperatureData &temperatureData);
    static bool Query(TimeInfoData &timeInfoData);
    static bool Write(const TimeInfoData &timeInfoData);
    static constexpr uint8_t STORAGE_READ_TIME_IN_MILLISECOND = 20; 
    static constexpr uint8_t STORAGE_WRITE_TIME_IN_MILLISECOND = 50; 

private:
    static MemoryDevices::EEPROM24C s_Eeprom24C;
};

#endif // _STORAGE_H_