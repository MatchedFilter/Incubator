#ifndef _SENSORS_JOYSTICK_H_
#define _SENSORS_JOYSTICK_H_
#include <cinttypes>
namespace Sensors
{
    enum EnumJoystickPressState : uint8_t
    {
        JOYSTICK_PRESS_STATE_NOT_PRESSED = 0,
        JOYSTICK_PRESS_STATE_PRESSED = 1,
        JOYSTICK_PRESS_STATE_CLICKED = 2,
    };

    struct JoystickData
    {
        uint16_t m_RightPosition;
        uint16_t m_UpPosition;
        EnumJoystickPressState m_PressState;
    };

    class Joystick
    {
    public:
        Joystick(uint8_t joystickId = 0);
        ~Joystick() = default;
        JoystickData GetJoystickValues();

    private:
        const uint8_t m_JoystickId;
        EnumJoystickPressState m_LastPressState;
    };
} // namespace Sensors

#endif // _SENSORS_JOYSTICK_H_