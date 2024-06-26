#ifndef _GUI_TC1602DAYADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_TC1602DAYADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602AdjustingValueWindowState.h"
#include "EnumAdjustingType.h"
namespace GUI
{
    class TC1602DayAdjustingValueWindowState : public ATC1602AdjustingValueWindowState
    {
    public:
        TC1602DayAdjustingValueWindowState(TC1602 *tc1602, EnumTC1602WindowState windowState);
        ~TC1602DayAdjustingValueWindowState() = default;

    protected:
        virtual void PrintCurrentValue() override;
        virtual void PrintAdjustingValue() override;
        virtual void WriteChanges() override;
        virtual int16_t GetInitialValue() override;

    private:
        uint8_t GetCurrentDay();
    };
} // namespace GUI

#endif // _GUI_TC1602DAYADJUSTINGVALUEWINDOWSTATE_H_