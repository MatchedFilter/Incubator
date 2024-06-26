#ifndef _GUI_TC1602HUMIDITYADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_TC1602HUMIDITYADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602AdjustingValueWindowState.h"
#include "EnumAdjustingType.h"
namespace GUI
{
    class TC1602HumidityAdjustingValueWindowState : public ATC1602AdjustingValueWindowState
    {
    public:
        TC1602HumidityAdjustingValueWindowState(TC1602 *tc1602, EnumTC1602WindowState windowState, EnumAdjustingType adjustingType);
        ~TC1602HumidityAdjustingValueWindowState() = default;

    protected:
        virtual void PrintCurrentValue() override;
        virtual void PrintAdjustingValue() override;
        virtual void WriteChanges() override;
        virtual int16_t GetInitialValue() override;

    private:
        uint8_t GetCurrentHumidity();

        const EnumAdjustingType m_AdjustingType;
    };
} // namespace GUI

#endif // _GUI_TC1602HUMIDITYADJUSTINGVALUEWINDOWSTATE_H_