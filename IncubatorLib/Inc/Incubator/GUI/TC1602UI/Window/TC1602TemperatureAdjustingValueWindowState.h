#ifndef _GUI_TC1602TEMPERATUREADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_TC1602TEMPERATUREADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602AdjustingValueWindowState.h"
#include "EnumAdjustingType.h"
namespace GUI
{
    class TC1602TemperatureAdjustingValueWindowState : public ATC1602AdjustingValueWindowState
    {
    public:
        TC1602TemperatureAdjustingValueWindowState(TC1602 *tc1602, EnumTC1602WindowState windowState, EnumAdjustingType adjustingType);
        ~TC1602TemperatureAdjustingValueWindowState() = default;

    protected:
        virtual void PrintCurrentValue() override;
        virtual void PrintAdjustingValue() override;
        virtual void WriteChanges() override;
        virtual int16_t GetInitialValue() override;

    private:
        int16_t GetCurrentTemperature();

        const EnumAdjustingType m_AdjustingType;
    };
} // namespace GUI

#endif // _GUI_TC1602TEMPERATUREADJUSTINGVALUEWINDOWSTATE_H_