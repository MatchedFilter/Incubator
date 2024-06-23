#ifndef _GUI_TC1602MAINWINDOWSTATE_H_
#define _GUI_TC1602MAINWINDOWSTATE_H_
#include "ATC1602WindowState.h"
namespace GUI
{
    class TC1602MainWindowState : public ATC1602WindowState
    {
    public:
        TC1602MainWindowState(TC1602 *tc1602);
        ~TC1602MainWindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    private:
        static constexpr uint8_t MAX_SCROLL_POSITION = 1;
        uint8_t m_ScrollPosition;
        IncubatorData *m_IncubatorData;
        bool m_bIsInitial;

    private:
        void PrintLine(uint8_t lineCount);
        void UpdateScrollPosition();
        void DetermineNextState(const IncubatorData &incubatorData);
    };
} // namespace GUI

#endif // _GUI_TC1602MAINWINDOWSTATE_H_