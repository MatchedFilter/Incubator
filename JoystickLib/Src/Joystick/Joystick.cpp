#include "Joystick/Joystick.h"
#include "Joystick/JoystickDependencies.h"

using namespace Sensors;

Joystick::Joystick(uint8_t joystickId) :
    m_JoystickId { joystickId }, m_LastPressState { JOYSTICK_PRESS_STATE_NOT_PRESSED }
{
}

JoystickData Joystick::GetJoystickValues()
{
    JoystickData joystickData;
    constexpr int32_t CONVERSION_TIME_IN_MICROSECONDS = 750;
    _start_adc_for_joystick_with_id_for_right_position(m_JoystickId);
    _delay_in_microseconds(CONVERSION_TIME_IN_MICROSECONDS);
    joystickData.m_RightPosition = _get_adc_value_for_joystick_with_id(m_JoystickId);
    _start_adc_for_joystick_with_id_for_up_position(m_JoystickId);
    _delay_in_microseconds(CONVERSION_TIME_IN_MICROSECONDS);
    joystickData.m_UpPosition = _get_adc_value_for_joystick_with_id(m_JoystickId);
    EnumJoystickPressState pressState = static_cast<EnumJoystickPressState> (_get_pressed_state_for_joystick_with_id(m_JoystickId));
    if (pressState == JOYSTICK_PRESS_STATE_NOT_PRESSED && m_LastPressState == JOYSTICK_PRESS_STATE_PRESSED)
    {
        joystickData.m_PressState = JOYSTICK_PRESS_STATE_CLICKED;
    }
    else
    {
        joystickData.m_PressState = pressState;
    }
    m_LastPressState = joystickData.m_PressState;
    return joystickData;
}
