#ifndef _INCUBATOR_H_
#define _INCUBATOR_H_
#include "DHT11/DHT11.h"
#include "TC1602/TC1602.h"
#include "NTC/NTC.h"

class Incubator
{
public:
    Incubator();
    ~Incubator() = default;
    void Initialize();
    void Run();

private:
    Sensors::DHT11 m_Dht11;
    Sensors::NTC m_NtcSensor;
    GUI::TC1602 m_Tc1602;

    static const int32_t DHT11_MAX_FAILURE_COUNT = 16;
    int32_t m_Dht11FailureCount;
};



#endif // _INCUBATOR_H_
