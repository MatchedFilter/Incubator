#ifndef _GUI_TC1602ERRORWINDOWSTATE_H_
#define _GUI_TC1602ERRORWINDOWSTATE_H_
#include "ATC1602WindowState.h"
namespace GUI
{

    enum EnumErrorCode
    {
        ERROR_CODE_NO_ERROR = 0,
        ERROR_CODE_MEMORY_ERROR,
        ERROR_CODE_HUMIDITY_ERROR,
        ERROR_CODE_TEMPERATURE_ERROR,
    };

    class TC1602ErrorWindowState : public ATC1602WindowState
    {
    public:
        TC1602ErrorWindowState(TC1602 *tc1602);
        ~TC1602ErrorWindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    private:
        EnumErrorCode m_LastErrorCode;

    private:
        void SendSensorErrorString();
        void UpdateScreen(IncubatorData &incubatorData);
        void DetermineNextState(const IncubatorData &incubatorData);
    };
} // namespace GUI

#endif // _GUI_TC1602ERRORWINDOWSTATE_H_