#ifndef _JOYSTICKDEPENDENCIES_H_
#define _JOYSTICKDEPENDENCIES_H_
#include <inttypes.h>

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus

/**
 * @brief start adc for reading
*/
extern void _start_adc_for_joystick_with_id_for_right_position(uint8_t joystickId);

/**
 * @brief start adc for reading
*/
extern void _start_adc_for_joystick_with_id_for_up_position(uint8_t joystickId);

/**
 * @brief reads adc value
*/
extern uint32_t _get_adc_value_for_joystick_with_id(uint8_t joystickId);

/**
 * @brief returns 1 if pressed, 0 if not pressed
*/
extern uint8_t _get_pressed_state_for_joystick_with_id(uint8_t joystickId);

extern void _delay_in_microseconds(int32_t duration_in_microseconds);


#ifdef _cplusplus
}
#endif // _cplusplus

#endif // _JOYSTICKDEPENDENCIES_H_