#ifndef _TC1602DEPENDENCIES_H_
#define _TC1602DEPENDENCIES_H_
#include <inttypes.h>

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_d4_pin_output(uint8_t outputValue);

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_d5_pin_output(uint8_t outputValue);

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_d6_pin_output(uint8_t outputValue);

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_d7_pin_output(uint8_t outputValue);

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_en_pin_output(uint8_t outputValue);

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_reset_pin_output(uint8_t outputValue);

    /**
     * @brief 1 as set, 0 as reset
    */
    extern void _set_rw_pin_output(uint8_t outputValue);

    extern void _delay_in_milliseconds(int32_t duration_in_milliseconds);
    extern void _delay_in_microseconds(int32_t duration_in_microseconds);
#ifdef _cplusplus
}
#endif // _cplusplus

#endif // _TC1602DEPENDENCIES_H_