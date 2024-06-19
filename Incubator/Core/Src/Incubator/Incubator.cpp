#include "Incubator/Incubator.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/Logger/Logger.h"

extern "C"
{
    void _delay_in_microseconds(int32_t duration_in_microseconds);
}

Incubator::Incubator() : m_Dht11FailureCount { 0 } { }

void Incubator::Initialize()
{
    TimeUtils::SleepInMilliseconds(2000);
    m_Tc1602.Initialize();
    m_NtcSensor.Initialize();
}

void Incubator::Run()
{
    m_Tc1602.ClearScreen();
    m_Tc1602.SetCursorToLine(GUI::TC1602_LINE_COUNT_1);
	Sensors::DHT11Data dht11Data;
    if (m_Dht11.RetreiveData(dht11Data))
    {
        m_Dht11FailureCount = 0;
        m_Tc1602.Print("Nem: %%%d, ", dht11Data.m_HumidityInPercentage);
        float temperatureInDegrees = (float)m_NtcSensor.CalculateTemperatureInCelcius();
    	LOG_DEBUG("Humidity: %d, temperature DHT11: %d, Temperature NTC: %.2f", dht11Data.m_HumidityInPercentage, dht11Data.m_TemperatureInDegrees, temperatureInDegrees);
        m_Tc1602.Print("%.2f C", temperatureInDegrees);
    }
    else
    {
        m_Dht11FailureCount++;
        if (m_Dht11FailureCount > DHT11_MAX_FAILURE_COUNT)
        {
    	    LOG_DEBUG("DHT 11 FAILURE COUNT LIMIT EXCEEDED");
            m_Tc1602.Print("DHT11 Hata");
            
        }
    	LOG_DEBUG("Unable to retreive data");
    }
    TimeUtils::SleepInMilliseconds(1000);
}
