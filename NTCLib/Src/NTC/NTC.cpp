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

bool NTC::CalculateTemperatureInCelcius(double &temperatureInCelcius)
{
    constexpr double KELVIN_TO_CELCIUS_CONSTANT = 273.15;
    static const int32_t TermistorConstant = 4095 * m_PullDownResistor;
    bool bResult = false;
    uint32_t adcValue = _get_adc_value_for_ntc(m_NtcID);
    if (adcValue > 0 )
    {
        const double temperatureCoeff = log(((TermistorConstant / adcValue) - m_PullDownResistor));
        temperatureInCelcius = (1 / (m_CoeffA + (m_CoeffB + (m_CoeffC * temperatureCoeff * temperatureCoeff)) * temperatureCoeff)) - KELVIN_TO_CELCIUS_CONSTANT;
        bResult = true;
    }
    return bResult;
}
