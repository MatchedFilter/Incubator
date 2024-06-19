#ifndef _NTCDEPENDENCIES_H_
#define _NTCDEPENDENCIES_H_
#include <inttypes.h>

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus

/**
 * @brief start adc for reading
*/
extern void _start_adc_for_ntc();

/**
 * @brief reads adc value
*/
extern uint32_t _get_adc_value_for_ntc();

#ifdef _cplusplus
}
#endif // _cplusplus

#endif // _NTCDEPENDENCIES_H_