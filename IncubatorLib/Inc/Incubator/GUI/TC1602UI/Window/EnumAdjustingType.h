#ifndef _GUI_ENUMADJUSTINGTYPE_H_
#define _GUI_ENUMADJUSTINGTYPE_H_
#include <cinttypes>
namespace GUI
{
    enum EnumAdjustingType : uint8_t
    {
        ADJUSTING_TYPE_MIN_NORMAL,
        ADJUSTING_TYPE_MAX_NORMAL,
        ADJUSTING_TYPE_MIN_MOTORS_OFF,
        ADJUSTING_TYPE_MAX_MOTORS_OFF
    };
} // namespace GUI

#endif // _GUI_ENUMADJUSTINGTYPE_H_