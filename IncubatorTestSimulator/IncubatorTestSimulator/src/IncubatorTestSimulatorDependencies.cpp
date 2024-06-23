#include <cinttypes>
#include "IncubatorTestSimulator.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>

extern ITS::IncubatorTestSimulator g_IncubatorTestSimulator;

static uint8_t s_Tc1602Data = 0;
static uint8_t s_Tc1602NibbleOffset = 4;
static bool s_IsTc1602EnPinHigh = false;
static bool s_IsTc1602RsPinHigh = false;
static constexpr const int32_t EEPROM24C32_SIZE = 32 * 8; // Just 8 pages
static uint8_t s_EepromBuffer[EEPROM24C32_SIZE];
std::chrono::_V2::system_clock::time_point s_DhtTimeStartPoint;
std::chrono::_V2::system_clock::time_point m_TestMicrosecondTimer;
uint8_t s_Dht11ReadingCount = 0;
uint8_t s_Dht11Data[40] = { 0 };


enum EnumDht11ReadingState
{
    DHT11_READING_STATE_STARTED = 0,
    DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH_INITIAL = 1,
    DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH = 2,
    DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW_INITIAL = 3,
    DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW = 4,
    DHT11_READING_STATE_READING_LOW_TO_HIGH = 5,
    DHT11_READING_STATE_READING_HIGH_TO_LOW_INITIAL = 6,
    DHT11_READING_STATE_READING_HIGH_TO_LOW = 7,
};

EnumDht11ReadingState s_Dht11ReadingState;

enum EnumJoystickReadingState
{
    JOYSTICK_READING_STATE_UP_DOWN = 0,
    JOYSTICK_READING_STATE_RIGHT_LEFT = 1,
};

static EnumJoystickReadingState s_JoystrickReadingState = JOYSTICK_READING_STATE_UP_DOWN;

constexpr const int32_t MAX_LOG_BUFFER_SIZE = 4096;
char s_LogBuffer[MAX_LOG_BUFFER_SIZE] = { 0 };

extern "C"
{
    int64_t _get_timestamp_in_milliseconds();

    void _start_dht11_timer()
    {
    }

    void _reset_dht11_timer()
    {
        s_DhtTimeStartPoint = std::chrono::high_resolution_clock::now();
    }

    void _stop_dht11_timer()
    {
    }

    uint32_t _get_timestamp_in_microseconds_from_dht11_timer()
    {
        auto elapsed = std::chrono::high_resolution_clock::now() - s_DhtTimeStartPoint;
        uint32_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return microseconds;
    }

    void _delay_in_microseconds(int32_t duration_in_microseconds)
    {
        _reset_dht11_timer();
        while (_get_timestamp_in_microseconds_from_dht11_timer() < (uint32_t)duration_in_microseconds) {}
    }

    void _delay_in_milliseconds(int32_t duration_in_miliseconds)
    {
        int64_t lastTimeStampInMillisecond = _get_timestamp_in_milliseconds() + duration_in_miliseconds;
        if (duration_in_miliseconds > 5)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(duration_in_miliseconds - 1));
        }
        while(_get_timestamp_in_milliseconds() < lastTimeStampInMillisecond) { }
    }

    void _set_dht11_data_pin_as_output()
    {
    }

    void _set_dht11_data_pin_as_input()
    {
    }

    void _set_dht11_data_pin_as_low()
    {
        s_Dht11ReadingState = DHT11_READING_STATE_STARTED;
        s_Dht11ReadingCount = 0;
    }

    int _read_dht11_data_pin()
    {
        int dataPinValue;
        switch (s_Dht11ReadingState)
        {
        case DHT11_READING_STATE_STARTED:
            dataPinValue = 0;
            s_Dht11ReadingState = DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH;
            break;

        case DHT11_READING_STATE_INITIALIZATION_LOW_TO_HIGH:
            {
                if (_get_timestamp_in_microseconds_from_dht11_timer() < 80)
                {
                    dataPinValue = 0;
                }
                else
                {
                    dataPinValue = 1;
                    s_Dht11ReadingState = DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW;
                }
            }
            break;


        case DHT11_READING_STATE_INITIALIZATION_HIGH_TO_LOW:
            {
                uint8_t humidityPercentage, temperatureInCelcius;
                bool bDhtValidity = g_IncubatorTestSimulator.GetHumidityPercentageAndTemperatureInCelcius(humidityPercentage, temperatureInCelcius);
                uint8_t checkSum = humidityPercentage + temperatureInCelcius;
                s_Dht11Data[0] = (humidityPercentage & 0b10000000) != 0;
                s_Dht11Data[1] = (humidityPercentage & 0b01000000) != 0;
                s_Dht11Data[2] = (humidityPercentage & 0b00100000) != 0;
                s_Dht11Data[3] = (humidityPercentage & 0b00010000) != 0;
                s_Dht11Data[4] = (humidityPercentage & 0b00001000) != 0;
                s_Dht11Data[5] = (humidityPercentage & 0b00000100) != 0;
                s_Dht11Data[6] = (humidityPercentage & 0b00000010) != 0;
                s_Dht11Data[7] = (humidityPercentage & 0b00000001) != 0;
                s_Dht11Data[16] = (temperatureInCelcius & 0b10000000) != 0;
                s_Dht11Data[17] = (temperatureInCelcius & 0b01000000) != 0;
                s_Dht11Data[18] = (temperatureInCelcius & 0b00100000) != 0;
                s_Dht11Data[19] = (temperatureInCelcius & 0b00010000) != 0;
                s_Dht11Data[20] = (temperatureInCelcius & 0b00001000) != 0;
                s_Dht11Data[21] = (temperatureInCelcius & 0b00000100) != 0;
                s_Dht11Data[22] = (temperatureInCelcius & 0b00000010) != 0;
                s_Dht11Data[23] = (temperatureInCelcius & 0b00000001) != 0;
                s_Dht11Data[32] = (checkSum & 0b10000000) != 0;
                s_Dht11Data[33] = (checkSum & 0b01000000) != 0;
                s_Dht11Data[34] = (checkSum & 0b00100000) != 0;
                s_Dht11Data[35] = (checkSum & 0b00010000) != 0;
                s_Dht11Data[36] = (checkSum & 0b00001000) != 0;
                s_Dht11Data[37] = (checkSum & 0b00000100) != 0;
                s_Dht11Data[38] = (checkSum & 0b00000010) != 0;
                s_Dht11Data[39] = (checkSum & 0b00000001) != 0;
                if (_get_timestamp_in_microseconds_from_dht11_timer() < 80)
                {
                    dataPinValue = 1;
                }
                else
                {
                    if (bDhtValidity)
                    {
                        dataPinValue = 0;
                        s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                    }
                    else
                    {
                        if (_get_timestamp_in_microseconds_from_dht11_timer() < 90)
                        {
                            dataPinValue = 1;
                        }
                        else
                        {
                            dataPinValue = 0;
                            s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                        }
                    }
                }
            }
            break;

        case DHT11_READING_STATE_READING_LOW_TO_HIGH:
                dataPinValue = 1;
                if (_get_timestamp_in_microseconds_from_dht11_timer() < 20)
                {
                    dataPinValue = 0;
                }
                else
                {
                    dataPinValue = 1;
                    s_Dht11ReadingState = DHT11_READING_STATE_READING_HIGH_TO_LOW;
                }
            break;

        case DHT11_READING_STATE_READING_HIGH_TO_LOW:
            {
                if (!s_Dht11Data[s_Dht11ReadingCount])
                {
                    if (_get_timestamp_in_microseconds_from_dht11_timer() < 23)
                    {
                        dataPinValue = 1;
                    }
                    else
                    {
                        dataPinValue = 0;
                        s_Dht11ReadingCount++;
                        s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                    }
                }
                else
                {
                    if (_get_timestamp_in_microseconds_from_dht11_timer() < 75)
                    {
                        dataPinValue = 1;
                    }
                    else
                    {
                        dataPinValue = 0;
                        s_Dht11ReadingCount++;
                        s_Dht11ReadingState = DHT11_READING_STATE_READING_LOW_TO_HIGH;
                    }
                }
            }
            break;
        
        default:
            dataPinValue = 0;
            break;
        }
        return dataPinValue;
    }

    void _transmit_log_buffer(uint8_t *buffer, int32_t size)
    {
        memset(s_LogBuffer, 0, sizeof(s_LogBuffer));
        memcpy(s_LogBuffer, buffer, size);
        fprintf(stdout, s_LogBuffer);
    }

    int64_t _get_timestamp_in_milliseconds()
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        int64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return milliseconds - g_IncubatorTestSimulator.GetSimulatorStartTimestampInMillisecond();
    }

    void _set_timestamp_in_milliseconds(int64_t timestampInMilliseconds)
    {
        int64_t currentTimeStampInMillisecond = _get_timestamp_in_milliseconds();
        int64_t timeDifference = timestampInMilliseconds - currentTimeStampInMillisecond;
        int64_t simulatorStartTimeInMillisecond = g_IncubatorTestSimulator.GetSimulatorStartTimestampInMillisecond();
        g_IncubatorTestSimulator.SetSimulatorStartTimestampInMillisecond(simulatorStartTimeInMillisecond - timeDifference);
    }

    void _set_d4_pin_output(uint8_t outputValue)
    {
        s_Tc1602Data |= outputValue << s_Tc1602NibbleOffset;
    }

    void _set_d5_pin_output(uint8_t outputValue)
    {
        s_Tc1602Data |= outputValue << (1 + s_Tc1602NibbleOffset);
    }

    void _set_d6_pin_output(uint8_t outputValue)
    {
        s_Tc1602Data |= outputValue << (2 + s_Tc1602NibbleOffset);
    }

    void _set_d7_pin_output(uint8_t outputValue)
    {
        s_Tc1602Data |= outputValue << (3 + s_Tc1602NibbleOffset);
    }

    void _set_en_pin_output(uint8_t outputValue)
    {
        if (outputValue == 0 && s_IsTc1602EnPinHigh)
        {
            if (s_Tc1602NibbleOffset == 4)
            {
                s_Tc1602NibbleOffset = 0;
            }
            else
            {
                s_Tc1602NibbleOffset = 4;
                if (s_IsTc1602RsPinHigh)
                {
                    g_IncubatorTestSimulator.SendDataToTC1602(s_Tc1602Data);
                }
                else
                {
                    g_IncubatorTestSimulator.SendCommandToTC1602(s_Tc1602Data);
                }
                s_Tc1602Data = 0;
            }
        }
        s_IsTc1602EnPinHigh = outputValue;
    }

    void _set_reset_pin_output(uint8_t outputValue)
    {
        s_IsTc1602RsPinHigh = outputValue;
    }

    void _set_rw_pin_output(uint8_t outputValue)
    {
    }

    void _start_adc_for_ntc(uint8_t ntc_id)
    {
    }

    uint32_t _get_adc_value_for_ntc(uint8_t ntc_id)
    {
        static const std::map<double, uint32_t> TEMPERATURE_RESISTANCE_LOOK_UP_MAP = {
            std::make_pair<double, uint32_t>(11.67, 190946),
            std::make_pair<double, uint32_t>(12.78, 180588),
            std::make_pair<double, uint32_t>(13.89, 170853),
            std::make_pair<double, uint32_t>(15.00, 161700),
            std::make_pair<double, uint32_t>(16.11, 153092),
            std::make_pair<double, uint32_t>(17.22, 144992),
            std::make_pair<double, uint32_t>(18.33, 137367),
            std::make_pair<double, uint32_t>(19.44, 130189),
            std::make_pair<double, uint32_t>(20.56, 123368),
            std::make_pair<double, uint32_t>(21.67, 117000),
            std::make_pair<double, uint32_t>(22.78, 110998),
            std::make_pair<double, uint32_t>(23.89, 105388),
            std::make_pair<double, uint32_t>(25.00, 100000),
            std::make_pair<double, uint32_t>(26.11, 94963),
            std::make_pair<double, uint32_t>(27.22, 90208),
            std::make_pair<double, uint32_t>(28.33, 85719),
            std::make_pair<double, uint32_t>(29.44, 81479),
            std::make_pair<double, uint32_t>(30.56, 77438),
            std::make_pair<double, uint32_t>(31.67, 73654),
            std::make_pair<double, uint32_t>(32.78, 70076),
            std::make_pair<double, uint32_t>(33.89, 66692),
            std::make_pair<double, uint32_t>(35.00, 63491),
            std::make_pair<double, uint32_t>(36.11, 60461),
            std::make_pair<double, uint32_t>(37.22, 57594),
            std::make_pair<double, uint32_t>(38.33, 54878),
            std::make_pair<double, uint32_t>(39.44, 52306),
            std::make_pair<double, uint32_t>(40.56, 49847),
            std::make_pair<double, uint32_t>(41.67, 47538),
            std::make_pair<double, uint32_t>(42.78, 45349),
            std::make_pair<double, uint32_t>(43.89, 43273)
            };
        uint32_t adcValue = 0;
        double temperatureInCelcius;
        if (g_IncubatorTestSimulator.GetTemperatureInCelcius(temperatureInCelcius))
        {
            auto tempIt = TEMPERATURE_RESISTANCE_LOOK_UP_MAP.upper_bound(temperatureInCelcius);
            if (tempIt == TEMPERATURE_RESISTANCE_LOOK_UP_MAP.begin())
            {
                adcValue = 4095;
            }
            else if (tempIt == TEMPERATURE_RESISTANCE_LOOK_UP_MAP.end())
            {
                adcValue = 1;
            }
            else
            {
                double upperTemperature = tempIt->first;
                uint32_t upperValue = tempIt->second;
                tempIt--;
                double lowerTemperature = tempIt->first;
                uint32_t lowerValue = tempIt->second;
                uint32_t resistance = lowerValue - ((lowerValue - upperValue) * (temperatureInCelcius - lowerTemperature) / (upperTemperature - lowerTemperature));
                adcValue = (4095 * 10000) / (10000 + resistance);
            }
        }
        return adcValue;
    }

    void _start_adc_for_joystick_with_id_for_right_position(uint8_t joystickId)
    {
        s_JoystrickReadingState = JOYSTICK_READING_STATE_RIGHT_LEFT;
    }

    void _start_adc_for_joystick_with_id_for_up_position(uint8_t joystickId)
    {
        s_JoystrickReadingState = JOYSTICK_READING_STATE_UP_DOWN;
    }

    uint32_t _get_adc_value_for_joystick_with_id(uint8_t joystickId)
    {
        bool bIsUpKeyPressed, bIsDownKeyPressed, bIsRightKeyPressed, bIsLeftKeyPressed;
        g_IncubatorTestSimulator.GetJoystickData(bIsUpKeyPressed, bIsDownKeyPressed, bIsRightKeyPressed, bIsLeftKeyPressed);
        uint32_t value = 4095 / 2;
        switch (s_JoystrickReadingState)
        {
        case JOYSTICK_READING_STATE_RIGHT_LEFT:
            {
                if (bIsRightKeyPressed)
                {
                    value = 4000;
                }
                else if (bIsLeftKeyPressed)
                {
                    value = 0;
                }
                else
                {
                }
            }
        case JOYSTICK_READING_STATE_UP_DOWN:
            {
                if (bIsUpKeyPressed)
                {
                    value = 4000;
                }
                else if (bIsDownKeyPressed)
                {
                    value = 0;
                }
                else
                {
                }
            }
            break;
        
        default:
            break;
        }
    	return value;
    }

    uint8_t _get_pressed_state_for_joystick_with_id(uint8_t joystickId)
    {
        uint8_t result = g_IncubatorTestSimulator.GetJoystickButtonState();
        return result;
    }

    bool _write_to_i2c_memory(uint16_t deviceAddres, uint16_t memoryAddress, uint8_t *buffer, uint16_t bufferSize)
    {
        bool bResult = false;
        std::ifstream eeprom24C32InFile ("Eeprom24C32.bin", std::ios::in | std::ios::binary);
        if (eeprom24C32InFile.is_open())
        {
            eeprom24C32InFile.read((char*)s_EepromBuffer, sizeof(s_EepromBuffer));
            eeprom24C32InFile.close();
            std::ofstream eeprom24C32OutFile ("Eeprom24C32.bin", std::ios::out | std::ios::binary);
            if (eeprom24C32OutFile.is_open())
            {
                bResult = true;
                memcpy(&s_EepromBuffer[memoryAddress], buffer, bufferSize);
                eeprom24C32OutFile.write((const char*)s_EepromBuffer, sizeof(s_EepromBuffer));
                eeprom24C32OutFile.close();
            }
        }
        return bResult;
    }

    bool _read_from_i2c_memory(uint16_t deviceAddres, uint16_t memoryAddress, uint8_t *buffer, uint16_t bufferSize)
    {
        bool bResult = false;
        std::ifstream eeprom24C32File ("Eeprom24C32.bin", std::ios::in | std::ios::binary);
        if (eeprom24C32File.is_open())
        {
            bResult = true;
            eeprom24C32File.read((char*)s_EepromBuffer, sizeof(s_EepromBuffer));
            eeprom24C32File.close();
            memcpy(buffer, &s_EepromBuffer[memoryAddress], bufferSize);
        }
        return bResult;
    }
}
