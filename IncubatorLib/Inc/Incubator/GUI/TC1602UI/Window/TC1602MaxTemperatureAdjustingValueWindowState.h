#ifndef _GUI_TC1602MAXTEMPERATUREADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_TC1602MAXTEMPERATUREADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602AdjustingValueWindowState.h"
namespace GUI
{
    class TC1602MaxTemperatureAdjustingValueWindowState : public ATC1602AdjustingValueWindowState
    {
    public:
        TC1602MaxTemperatureAdjustingValueWindowState(TC1602 *tc1602);
        ~TC1602MaxTemperatureAdjustingValueWindowState() = default;

    protected:
        virtual void PrintCurrentValue() override;
        virtual void PrintAdjustingValue() override;
        virtual void WriteChanges() override;
        virtual int32_t GetInitialValue() override;
    };
} // namespace GUI

#endif // _GUI_TC1602MAXTEMPERATUREADJUSTINGVALUEWINDOWSTATE_H_