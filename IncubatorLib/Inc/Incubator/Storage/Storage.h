#ifndef _STORAGE_H_
#define _STORAGE_H_
#include <cinttypes>
#include "EEPROM24C/EEPROM24C.h"

struct HumidityData
{
    uint8_t m_HumidityStartPercentage;
    uint8_t m_HumidityEndPercentage;
    HumidityData() : m_HumidityStartPercentage { 50 }, m_HumidityEndPercentage { 55 } { }
    bool Serialize(uint8_t *buffer, uint16_t size) const;
    bool Deserialize(const uint8_t *buffer, uint16_t size);
    static constexpr const uint8_t BUFFER_SIZE = sizeof(uint8_t) + sizeof(uint8_t);
    ~HumidityData() = default;
};

struct TemperatureData
{
    int32_t m_TemperatureStartInDeciDegrees;
    int32_t m_TemperatureEndInDeciDegrees;
    TemperatureData() : m_TemperatureStartInDeciDegrees { 365 }, m_TemperatureEndInDeciDegrees { 385 } { }
    bool Serialize(uint8_t *buffer, uint16_t size) const;
    bool Deserialize(const uint8_t *buffer, uint16_t size);
    static constexpr const uint8_t BUFFER_SIZE = sizeof(int32_t) + sizeof(int32_t);
    ~TemperatureData() = default;
};

struct TimeInfoData
{
    uint32_t m_IncbutorStartTimestampInSeconds;
    uint32_t m_IncubatorCurrentTimestampInSeconds;
    uint8_t m_TotalDayCount;
    uint8_t m_MotorOffDayCount;
    TimeInfoData() : m_IncbutorStartTimestampInSeconds { 0 }, m_IncubatorCurrentTimestampInSeconds { 0 }, m_TotalDayCount { 21 }, m_MotorOffDayCount { 3 } { }
    bool Serialize(uint8_t *buffer, uint16_t size) const;
    bool Deserialize(const uint8_t *buffer, uint16_t size);
    static constexpr const uint8_t BUFFER_SIZE = sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint8_t);
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

private:
    static MemoryDevices::EEPROM24C s_Eeprom24C;
};

#endif // _STORAGE_H_