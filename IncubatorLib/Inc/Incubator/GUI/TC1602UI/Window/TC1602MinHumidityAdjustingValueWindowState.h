#ifndef _GUI_TC1602MINHUMIDITYADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_TC1602MINHUMIDITYADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602AdjustingValueWindowState.h"
namespace GUI
{
    class TC1602MinHumidityAdjustingValueWindowState : public ATC1602AdjustingValueWindowState
    {
    public:
        TC1602MinHumidityAdjustingValueWindowState(TC1602 *tc1602);
        ~TC1602MinHumidityAdjustingValueWindowState() = default;

    protected:
        virtual void PrintCurrentValue() override;
        virtual void PrintAdjustingValue() override;
        virtual void WriteChanges() override;
        virtual int32_t GetInitialValue() override;
    };
} // namespace GUI

#endif // _GUI_TC1602MINHUMIDITYADJUSTINGVALUEWINDOWSTATE_H_