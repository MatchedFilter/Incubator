#ifndef _GUI_TC1602ResetWindowState_H_
#define _GUI_TC1602ResetWindowState_H_
#include "ATC1602WindowState.h"
#include "TC1602MenuWindowState.h"
namespace GUI
{
    class TC1602ResetWindowState : public ATC1602WindowState
    {
    public:
        TC1602ResetWindowState(TC1602 *tc1602, TC1602MenuWindowState *menuWindowState);
        ~TC1602ResetWindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    private:
        static constexpr uint8_t MAX_SCROLL_POSITION = 2;
        uint8_t m_ScrollPosition;
        IncubatorData *m_IncubatorData;
        bool m_bIsInitial;
        TC1602MenuWindowState *m_MenuWindowState;

    private:
        void InterruptedRefresh();
        void PrintResetQuestion();
        void PrintSelectLine();
        void UpdateScrollPosition();
        void DetermineNextState();
    };
} // namespace GUI

#endif // _GUI_TC1602ResetWindowState_H_