#ifndef _SENSORS_NTC_H_
#define _SENSORS_NTC_H_
#include <cinttypes>
namespace Sensors
{
    class NTC
    {
    public:
        /**
         * @brief defaults for 100k 28 - 40 C
        */
        NTC(uint8_t ntcID = 0, double coeffA = 0.8022799015e-3, double coeffB = 2.033227644e-4, double coeffC = 1.382036989e-7,
            int32_t pullDownResistor = 10000);
        ~NTC() = default;
        void Initialize();
        bool CalculateTemperatureInCelcius(double &temperatureInCelcius);
    
    private:
        const uint8_t m_NtcID;
        const double m_CoeffA;
        const double m_CoeffB;
        const double m_CoeffC;
        const int32_t m_PullDownResistor;

    private:
        bool GetDetailedTemperatureFromMap(uint32_t resistance, double &temperatureInCelcius);
    };
} // namespace Sensors

#endif // _SENSORS_NTC_H_
