#include "NTC/NTC.h"
#include <cmath>
#include "NTC/NTCDependencies.h"

using namespace Sensors;


NTC::NTC(uint8_t ntcID, double coeffA, double coeffB, double coeffC,
            int32_t pullDownResistor) : 
    m_NtcID { ntcID },
    m_CoeffA { coeffA }, m_CoeffB { coeffB }, m_CoeffC { coeffC },
    m_PullDownResistor { pullDownResistor }
{
}

void NTC::Initialize()
{
    _start_adc_for_ntc(m_NtcID);
}

inline double GetTemperature(int32_t resistance, int32_t lowerResistance, int32_t upperResistance, double lowerTemperature)
{
    return lowerTemperature - (double) (resistance - lowerResistance) / (double)(upperResistance - lowerResistance);
}

bool NTC::GetDetailedTemperatureFromMap(uint32_t resistance, double &temperatureInCelcius)
{
    static constexpr const double TEMPERATURE_MAP[] = {
        43.89, 42.78, 41.67, 40.56, 39.44, 38.33, 37.22,
        36.11, 35.00, 33.89, 32.78, 31.67, 30.56, 29.44
    };
    static constexpr const uint32_t TEMPERATURE_RESISTANCE_MAP[] = {
        43273, 45349, 47538, 49847, 52306, 54878, 57594,
        60461, 63491, 66692, 70076, 73654, 77438, 81479
    };
    static constexpr const int32_t TEMPERATURE_MAP_SIZE = sizeof(TEMPERATURE_MAP) / sizeof(double);
    
    bool bResult = false;
    for (uint8_t i = 0; i < TEMPERATURE_MAP_SIZE - 1 && !bResult; i++)
    {
        if (resistance < TEMPERATURE_RESISTANCE_MAP[i + 1])
        {
            bResult = true;
            temperatureInCelcius = GetTemperature(resistance, TEMPERATURE_RESISTANCE_MAP[i], TEMPERATURE_RESISTANCE_MAP[i + 1], TEMPERATURE_MAP[i]);
        }
    }
    return bResult;
}

bool NTC::CalculateTemperatureInCelcius(double &temperatureInCelcius)
{
    constexpr double KELVIN_TO_CELCIUS_CONSTANT = 273.15;
    static const int32_t TermistorConstant = 4095 * m_PullDownResistor;
    bool bResult = false;
    uint32_t adcValue = _get_adc_value_for_ntc(m_NtcID);
    if (adcValue > 0 )
    {
        bResult = true;
        int32_t resistance = (TermistorConstant / adcValue) - m_PullDownResistor;
        if (!GetDetailedTemperatureFromMap(resistance, temperatureInCelcius))
        {
            const double temperatureCoeff = log(resistance);
            temperatureInCelcius = (1 / (m_CoeffA + (m_CoeffB + (m_CoeffC * temperatureCoeff * temperatureCoeff)) * temperatureCoeff)) - KELVIN_TO_CELCIUS_CONSTANT;
        }
    }
    return bResult;
}
