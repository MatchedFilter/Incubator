#ifndef _DHT11DEPENDENCIES_H_
#define _DHT11DEPENDENCIES_H_
#include <inttypes.h>

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus
    extern void _start_dht11_timer();
    extern void _reset_dht11_timer();
    extern void _stop_dht11_timer();
    extern uint32_t _get_timestamp_in_microseconds_from_dht11_timer();
    extern void _delay_in_milliseconds(int32_t duration_in_milliseconds);
    extern void _set_dht11_data_pin_as_output();
    extern void _set_dht11_data_pin_as_input();
    extern void _set_dht11_data_pin_as_low();

    /**
     * @returns 1 if high, 0 if low
    */
    extern int _read_dht11_data_pin();
#ifdef _cplusplus
}
#endif // _cplusplus
#endif // _DHT11DEPENDENCIES_H_
