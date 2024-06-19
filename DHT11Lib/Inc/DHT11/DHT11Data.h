#ifndef _SENSORS_DHT11DATA_H_
#define _SENSORS_DHT11DATA_H_
#include <cinttypes>
namespace Sensors
{
    struct DHT11Data
    {
        DHT11Data() : m_HumidityInPercentage { 0xFF }, m_TemperatureInDegrees { 0xFF } { }
        ~DHT11Data() = default;
        uint8_t m_HumidityInPercentage;
        uint8_t m_TemperatureInDegrees;
    };
} // namespace DHT11

#endif // _SENSORS_DHT11DATA_H_