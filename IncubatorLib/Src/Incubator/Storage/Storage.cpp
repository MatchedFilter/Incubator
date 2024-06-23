#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/Logger/Logger.h"
#include <cstring>

constexpr uint16_t PAGE_OFFSET = 0;
constexpr uint16_t INITIAL_PAGE = 1;
constexpr uint16_t HUMIDITY_PAGE = 2;
constexpr uint16_t TEMPERATURE_PAGE = 3;
constexpr uint16_t TIME_INFO_PAGE = 4;

MemoryDevices::EEPROM24C Storage::s_Eeprom24C;

struct StorageStatusData
{
    bool m_bIsInitialized;
    StorageStatusData() : m_bIsInitialized { false } {}
    static constexpr int32_t BUFFER_SIZE = 4;
    static constexpr uint8_t BYTE_0 = 0xAC;
    static constexpr uint8_t BYTE_1 = 0xD3;
    static constexpr uint8_t BYTE_2 = 0x9C;
    static constexpr uint8_t BYTE_3 = 0x17;
    bool Serialize(uint8_t *buffer, uint16_t size)
    {
        bool bResult = size >= BUFFER_SIZE;
        if (bResult)
        {
            if (m_bIsInitialized)
            {
                buffer[0] = BYTE_0;
                buffer[1] = BYTE_1;
                buffer[2] = BYTE_2;
                buffer[3] = BYTE_3;
            }
            else
            {
                memset(buffer, 0xFF, BUFFER_SIZE);
            }
        }
        return bResult;
    }

    bool Deserialize(const uint8_t *buffer, uint16_t size)
    {
        bool bResult = size >= BUFFER_SIZE;
        if (bResult)
        {
            if (buffer[0] == BYTE_0 && buffer[1] == BYTE_1 &&
                buffer[2] == BYTE_2 && buffer[3] == BYTE_3)
            {
                m_bIsInitialized = true;
            }
            else
            {
                m_bIsInitialized = false;
            }
        }
        return bResult;
    }
};

bool HumidityData::Serialize(uint8_t *buffer, uint16_t size) const
{
    bool bResult = size >= BUFFER_SIZE;
    if (bResult)
    {
        buffer[0] = m_HumidityStartPercentage;
        buffer[1] = m_HumidityEndPercentage;
    }
    return bResult;
}

bool HumidityData::Deserialize(const uint8_t *buffer, uint16_t size)
{
    bool bResult = size >= BUFFER_SIZE;
    if (bResult)
    {
        m_HumidityStartPercentage = buffer[0];
        m_HumidityEndPercentage = buffer[1];
    }
    return bResult;
}

bool TemperatureData::Serialize(uint8_t *buffer, uint16_t size) const
{
    bool bResult = size >= BUFFER_SIZE;
    if (bResult)
    {
        uint8_t writtenSize = 0;
        memcpy(&buffer[writtenSize], &m_TemperatureStartInDeciDegrees, sizeof(m_TemperatureStartInDeciDegrees));
        writtenSize += sizeof(m_TemperatureStartInDeciDegrees);
        memcpy(&buffer[writtenSize], &m_TemperatureEndInDeciDegrees, sizeof(m_TemperatureEndInDeciDegrees));
    }
    return bResult;
}

bool TemperatureData::Deserialize(const uint8_t *buffer, uint16_t size)
{
    bool bResult = size >= BUFFER_SIZE;
    if (bResult)
    {
        uint8_t readSize = 0;
        memcpy(&m_TemperatureStartInDeciDegrees, &buffer[readSize], sizeof(m_TemperatureStartInDeciDegrees));
        readSize += sizeof(m_TemperatureStartInDeciDegrees);
        memcpy(&m_TemperatureEndInDeciDegrees, &buffer[readSize], sizeof(m_TemperatureEndInDeciDegrees));
    }
    return bResult;
}

bool TimeInfoData::Serialize(uint8_t *buffer, uint16_t size) const
{
    bool bResult = size >= BUFFER_SIZE;
    if (bResult)
    {
        uint8_t writtenSize = 0;
        memcpy(&buffer[writtenSize], &m_IncbutorStartTimestampInSeconds, sizeof(m_IncbutorStartTimestampInSeconds));
        writtenSize += sizeof(m_IncbutorStartTimestampInSeconds);
        memcpy(&buffer[writtenSize], &m_IncubatorCurrentTimestampInSeconds, sizeof(m_IncubatorCurrentTimestampInSeconds));
        writtenSize += sizeof(m_IncubatorCurrentTimestampInSeconds);
        memcpy(&buffer[writtenSize], &m_TotalDayCount, sizeof(m_TotalDayCount));
        writtenSize += sizeof(m_TotalDayCount);
        memcpy(&buffer[writtenSize], &m_MotorOffDayCount, sizeof(m_MotorOffDayCount));
    }
    return bResult;
}

bool TimeInfoData::Deserialize(const uint8_t *buffer, uint16_t size)
{
    bool bResult = size >= BUFFER_SIZE;
    if (bResult)
    {
        uint8_t readSize = 0;
        memcpy(&m_IncbutorStartTimestampInSeconds, &buffer[readSize], sizeof(m_IncbutorStartTimestampInSeconds));
        readSize += sizeof(m_IncbutorStartTimestampInSeconds);
        memcpy(&m_IncubatorCurrentTimestampInSeconds, &buffer[readSize], sizeof(m_IncubatorCurrentTimestampInSeconds));
        readSize += sizeof(m_IncubatorCurrentTimestampInSeconds);
        memcpy(&m_TotalDayCount, &buffer[readSize], sizeof(m_TotalDayCount));
        readSize += sizeof(m_TotalDayCount);
        memcpy(&m_MotorOffDayCount, &buffer[readSize], sizeof(m_MotorOffDayCount));
    }
    return bResult;
}

void Storage::Initialize()
{
    uint8_t buffer[StorageStatusData::BUFFER_SIZE] = { 0 };
    if (s_Eeprom24C.Read(INITIAL_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer)))
    {
        TimeUtils::SleepInMilliseconds(20);
        StorageStatusData storageStatusData;
        if (storageStatusData.Deserialize(buffer, (uint16_t) sizeof(buffer)))
        {
            if (storageStatusData.m_bIsInitialized == false)
            {
                LOG_DEBUG("Storage not initialized defaults values will be written");
                HumidityData humidityData;
                Write(humidityData);
                TimeUtils::SleepInMilliseconds(50);
                TemperatureData temperatureData;
                Write(temperatureData);
                TimeUtils::SleepInMilliseconds(50);
                TimeInfoData timeInfoData;
                timeInfoData.m_IncubatorCurrentTimestampInSeconds = static_cast<uint32_t>(TimeUtils::GetTimestampInMilliseconds() / 1000);
                Write(timeInfoData);
                TimeUtils::SleepInMilliseconds(50);
                
                storageStatusData.m_bIsInitialized = true;
                if (storageStatusData.Serialize(buffer, (uint16_t)sizeof(buffer)))
                {
                    if (s_Eeprom24C.Write(INITIAL_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer)))
                    {
                        LOG_DEBUG("Storage initialized with defaults values");
                    }
                    TimeUtils::SleepInMilliseconds(50);
                }
            }
            else
            {
                LOG_DEBUG("Storage status OK");
            }
        }
    }
}

void Storage::Reset()
{
    uint8_t buffer[StorageStatusData::BUFFER_SIZE] = { 0 };
    StorageStatusData storageStatusData;
    storageStatusData.m_bIsInitialized = false;
    storageStatusData.Serialize(buffer, (uint16_t)sizeof(buffer));
    s_Eeprom24C.Write(INITIAL_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    TimeUtils::SleepInMilliseconds(50);
}


bool Storage::Query(HumidityData &humidityData)
{
    bool bResult = false;
    uint8_t buffer[HumidityData::BUFFER_SIZE] = { 0 };
    bResult = s_Eeprom24C.Read(HUMIDITY_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    if (bResult)
    {
        bResult = humidityData.Deserialize(buffer, (uint16_t) sizeof(buffer));
    }
    return bResult;
}

bool Storage::Write(const HumidityData &humidityData)
{
    bool bResult = false;
    uint8_t buffer[HumidityData::BUFFER_SIZE] = { 0 };
    bResult = humidityData.Serialize(buffer, (uint16_t) sizeof(buffer));
    if (bResult)
    {
        bResult = s_Eeprom24C.Write(HUMIDITY_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    }
    return bResult;
}

bool Storage::Query(TemperatureData &temperatureData)
{
    bool bResult = false;
    uint8_t buffer[TemperatureData::BUFFER_SIZE] = { 0 };
    bResult = s_Eeprom24C.Read(TEMPERATURE_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    if (bResult)
    {
        bResult = temperatureData.Deserialize(buffer, (uint16_t) sizeof(buffer));
    }
    return bResult;
}

bool Storage::Write(const TemperatureData &temperatureData)
{
    bool bResult = false;
    uint8_t buffer[TemperatureData::BUFFER_SIZE] = { 0 };
    bResult = temperatureData.Serialize(buffer, (uint16_t) sizeof(buffer));
    if (bResult)
    {
        bResult = s_Eeprom24C.Write(TEMPERATURE_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    }
    return bResult;
}

bool Storage::Query(TimeInfoData &timeInfoData)
{
    bool bResult = false;
    uint8_t buffer[TimeInfoData::BUFFER_SIZE] = { 0 };
    bResult = s_Eeprom24C.Read(TIME_INFO_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    if (bResult)
    {
        bResult = timeInfoData.Deserialize(buffer, (uint16_t) sizeof(buffer));
    }
    return bResult;
}

bool Storage::Write(const TimeInfoData &timeInfoData)
{
    bool bResult = false;
    uint8_t buffer[TimeInfoData::BUFFER_SIZE] = { 0 };
    bResult = timeInfoData.Serialize(buffer, (uint16_t) sizeof(buffer));
    if (bResult)
    {
        bResult = s_Eeprom24C.Write(TIME_INFO_PAGE, PAGE_OFFSET, buffer, (uint16_t) sizeof(buffer));
    }
    return bResult;
}
