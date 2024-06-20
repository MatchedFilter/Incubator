#include "DHT11/DHT11.h"
#include "DHT11/DHT11Dependencies.h"

using namespace Sensors;

constexpr int32_t INITIALIZATION_LOW_TIMEOUT_IN_MILISECONDS = 18;
constexpr int32_t MAX_LOOP_DURATION = 512;
constexpr int OUTPUT_HIGH = 1;
constexpr int OUTPUT_LOW = 0;

constexpr int32_t MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS = 0;
constexpr int32_t MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS = 500;
constexpr int32_t INITIALIZATION_MIN_OUTPUT_TIME_IN_MICROSECONDS = 75;
constexpr int32_t INITIALIZATION_MAX_OUTPUT_TIME_IN_MICROSECONDS = 85;

constexpr int32_t INPUT_LOW_DATA_MAX_DURATION_IN_MICROSECOND = 30;
constexpr int32_t INPUT_HIGH_DATA_MAX_DURATION_IN_MICROSECOND = 80;

constexpr int32_t HUMIDITY_START_BIT = 0;
constexpr int32_t HUMIDITY_END_BIT = 8;

constexpr int32_t HUMIDITY_DECIMAL_START_BIT = 8;
constexpr int32_t HUMIDITY_DECIMAL_END_BIT = 16;

constexpr int32_t TEMPERATURE_START_BIT = 16;
constexpr int32_t TEMPERATURE_END_BIT = 24;

constexpr int32_t TEMPERATURE_DECIMAL_START_BIT = 24;
constexpr int32_t TEMPERATURE_DECIMAL_END_BIT = 32;

constexpr int32_t PARITY_START_BIT = 32;
constexpr int32_t PARITY_END_BIT = 40;


inline bool WaitForGivenOutputToChange(int outputValue, uint32_t minimumTimeDurationInMicroseconds, uint32_t maximumTimeDurationInMicroseconds, uint32_t &durationInMicroseconds)
{
    bool bResult = false;
    bool bIsOutputDifferent = false;
    _reset_dht11_timer();
    durationInMicroseconds = _get_timestamp_in_microseconds_from_dht11_timer();
    while (durationInMicroseconds < MAX_LOOP_DURATION && !bIsOutputDifferent)
    {
        durationInMicroseconds = _get_timestamp_in_microseconds_from_dht11_timer();
        if (_read_dht11_data_pin() != outputValue)
        {
        	bIsOutputDifferent = true;
        }
    }

    if (bIsOutputDifferent)
    {
        if (durationInMicroseconds >= minimumTimeDurationInMicroseconds && durationInMicroseconds <= maximumTimeDurationInMicroseconds)
        {
            bResult = true;
        }
    }
    return bResult;
}

inline bool WaitForGivenOutputToChange(int outputValue, uint32_t minimumTimeDurationInMicroseconds, uint32_t maximumTimeDurationInMicroseconds)
{
    uint32_t tempDuration;
    bool bResult = WaitForGivenOutputToChange(outputValue, minimumTimeDurationInMicroseconds, maximumTimeDurationInMicroseconds, tempDuration);
    return bResult;
        
}

inline bool InitializeForReading()
{
    bool bResult = true;
    _set_dht11_data_pin_as_output();
    _set_dht11_data_pin_as_low();
    _delay_in_milliseconds(INITIALIZATION_LOW_TIMEOUT_IN_MILISECONDS);
    _set_dht11_data_pin_as_input();
    if (!WaitForGivenOutputToChange(OUTPUT_HIGH, MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS))
    {
        bResult = false;
    }
    if (bResult)
    {
        if (!WaitForGivenOutputToChange(OUTPUT_LOW, INITIALIZATION_MIN_OUTPUT_TIME_IN_MICROSECONDS, INITIALIZATION_MAX_OUTPUT_TIME_IN_MICROSECONDS))
        {
            bResult = false;
        }
    }

    if (bResult)
    {
        if (!WaitForGivenOutputToChange(OUTPUT_HIGH, INITIALIZATION_MIN_OUTPUT_TIME_IN_MICROSECONDS, INITIALIZATION_MAX_OUTPUT_TIME_IN_MICROSECONDS))
        {
            bResult = false;
        }
    }
    return bResult;
}

inline bool ReadTemperatureAndHumidity(uint8_t &humidityPercantage, uint8_t &temperatureInDegrees)
{
    bool bResult = false;
    constexpr uint8_t DATA_SIZE = 40;
    uint8_t data[DATA_SIZE] = { 0 };
    bool bIsDataRead = true;
    for (int32_t i = 0; i < DATA_SIZE; i++)
    {
        if (!WaitForGivenOutputToChange(OUTPUT_LOW, MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS))
        {
            bIsDataRead = false;
            break;
        }
        uint32_t durationInMicroSeconds;
        if (!WaitForGivenOutputToChange(OUTPUT_HIGH, MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, durationInMicroSeconds))
        {
            bIsDataRead = false;
            break;
        }
        if (durationInMicroSeconds < INPUT_LOW_DATA_MAX_DURATION_IN_MICROSECOND)
        {
            data[i] = OUTPUT_LOW;
        }
        else if (durationInMicroSeconds < INPUT_HIGH_DATA_MAX_DURATION_IN_MICROSECOND)
        {
            data[i] = OUTPUT_HIGH;
        }
        else
        {
            bIsDataRead = false;
            break;
        }
    }
    if (bIsDataRead)
    {
        int16_t tempHumidityIntegralValue = 0;
        for (int32_t i = HUMIDITY_START_BIT; i < HUMIDITY_END_BIT; i++)
        {
        	tempHumidityIntegralValue |= (data[i] << (7 - (i - HUMIDITY_START_BIT)));
        }

        int16_t tempHumidityDecimalValue = 0;
        for (int32_t i = HUMIDITY_DECIMAL_START_BIT; i < HUMIDITY_DECIMAL_END_BIT; i++)
        {
        	tempHumidityDecimalValue |= (data[i] << (7 - (i - HUMIDITY_DECIMAL_START_BIT)));
        }

        int16_t tempTemperatureIntegralValue = 0;
        for (int32_t i = TEMPERATURE_START_BIT; i < TEMPERATURE_END_BIT; i++)
        {
        	tempTemperatureIntegralValue |= (data[i] << (7 - (i - TEMPERATURE_START_BIT)));
        }

        int16_t tempTemperatureDecimalValue = 0;
        for (int32_t i = TEMPERATURE_DECIMAL_START_BIT; i < TEMPERATURE_DECIMAL_END_BIT; i++)
        {
        	tempTemperatureDecimalValue |= (data[i] << (7 - (i - TEMPERATURE_DECIMAL_START_BIT)));
        }

        int16_t parityValue = 0;
        for (int32_t i = PARITY_START_BIT; i < PARITY_END_BIT; i++)
        {
        	parityValue |= (data[i] <<  (7 - (i - PARITY_START_BIT)));
        }

        uint8_t calculatedParity = tempHumidityIntegralValue + tempHumidityDecimalValue + tempTemperatureIntegralValue + tempTemperatureDecimalValue;
        if (calculatedParity == parityValue)
        {
            bResult = true;
            humidityPercantage = tempHumidityIntegralValue;
            temperatureInDegrees = tempTemperatureIntegralValue;
        }
    }
    return bResult;
}

bool DHT11::RetreiveData(DHT11Data &dht11Data)
{
    bool bResult = false;
    _start_dht11_timer();
    if (InitializeForReading())
    {
        bResult = ReadTemperatureAndHumidity(dht11Data.m_HumidityInPercentage, dht11Data.m_TemperatureInDegrees);
    }
    _stop_dht11_timer();

    return bResult;
}
