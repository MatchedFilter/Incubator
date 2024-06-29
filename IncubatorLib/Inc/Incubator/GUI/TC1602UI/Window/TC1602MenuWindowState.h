#ifndef _GUI_TC1602MENUWINDOWSTATE_H_
#define _GUI_TC1602MENUWINDOWSTATE_H_
#include "ATC1602WindowState.h"
namespace GUI
{
    class TC1602MenuWindowState : public ATC1602WindowState
    {
    public:
        TC1602MenuWindowState(TC1602 *tc1602);
        ~TC1602MenuWindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    private:
        static constexpr uint8_t MAX_SCROLL_POSITION = 5;
        uint8_t m_ScrollPosition;
        IncubatorData *m_IncubatorData;
        bool m_bIsInitial;

    private:
        void UpdateScrollPosition();
        void PrintLine(uint8_t lineCount);
        void DetermineNextState();
        void InterruptedRefresh();
        friend class TC1602ResetWindowState;
    };
} // namespace GUI

#endif // _GUI_TC1602MENUWINDOWSTATE_H_