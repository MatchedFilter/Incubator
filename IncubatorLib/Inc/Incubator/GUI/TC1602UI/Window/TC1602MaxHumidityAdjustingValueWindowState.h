#ifndef _GUI_TC1602MAXHUMIDITYADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_TC1602MAXHUMIDITYADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602AdjustingValueWindowState.h"
namespace GUI
{
    class TC1602MaxHumidityAdjustingValueWindowState : public ATC1602AdjustingValueWindowState
    {
    public:
        TC1602MaxHumidityAdjustingValueWindowState(TC1602 *tc1602);
        ~TC1602MaxHumidityAdjustingValueWindowState() = default;

    protected:
        virtual void PrintCurrentValue() override;
        virtual void PrintAdjustingValue() override;
        virtual void WriteChanges() override;
        virtual int32_t GetInitialValue() override;
    };
} // namespace GUI

#endif // _GUI_TC1602MAXHUMIDITYADJUSTINGVALUEWINDOWSTATE_H_