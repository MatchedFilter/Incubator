#ifndef _INCUBATORCONTROLLERDEPENDENCIES_H_
#define _INCUBATORCONTROLLERDEPENDENCIES_H_
#include <inttypes.h>

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus

extern void _set_heater_pin_as_high();
extern void _set_heater_pin_as_low();
extern void _set_heater_pwm(uint8_t dutyCycle);
extern void _set_humidity_generator_pin_as_high();
extern void _set_humidity_generator_pin_as_low();
extern void _set_humidity_generator_pwm(uint8_t dutyCycle);

#ifdef _cplusplus
}
#endif // _cplusplus

#endif // _INCUBATORCONTROLLERDEPENDENCIES_H_