#ifndef _GUI_TC1602UIDEVICE_H_
#define _GUI_TC1602UIDEVICE_H_
#include "Incubator/GUI/IUIDevice.h"
#include "TC1602/TC1602.h"
#include "Window/TC1602ErrorWindowState.h"
#include "Window/TC1602MainWindowState.h"
#include "Window/TC1602MenuWindowState.h"
#include "Window/TC1602TemperatureSetWindowState.h"
#include "Window/TC1602ResetWindowState.h"
#include "TimerTasks/TC1602RefreshingTimerTaskHandler.h"

namespace GUI
{
    class TC1602UIDevice : public IUIDevice
    {
    public:
        TC1602UIDevice();
        ~TC1602UIDevice() = default;
        virtual void Initialize() override;
        virtual void Update(IncubatorData &incubatorData) override;

    private:
        TC1602 m_Tc1602;

        // WindowStates
        ATC1602WindowState *m_CurrentState;
        ATC1602WindowState *m_States[TC1602_WINDOW_STATE_SIZE];
        TC1602ErrorWindowState m_TC1602ErrorWindowState;
        TC1602MainWindowState m_TC1602MainWindowState;
        TC1602MenuWindowState m_TC1602MenuWindowState;
        TC1602TemperatureSetWindowState m_TC1602TemperatureSetWindowState;
        TC1602ResetWindowState m_TC1602ResetWindowState;

        static constexpr const uint16_t TC1602_REFRESHING_TIME_IN_MILLISECOND = 3000;
        TC1602RefreshingTimerTaskHandler m_TC1602RefreshingTimerTaskHandler;

        EnumTC1602WindowState m_PreviousState;

    private:
        bool IsThereAnyErrorInData(const IncubatorData &incubatorData);
    };
} // namespace GUI

#endif // _GUI_TC1602UIDEVICE_H_