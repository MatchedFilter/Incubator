#ifndef _GUI_ATC1602ADJUSTINGVALUEWINDOWSTATE_H_
#define _GUI_ATC1602ADJUSTINGVALUEWINDOWSTATE_H_
#include "ATC1602WindowState.h"
namespace GUI
{
    class ATC1602AdjustingValueWindowState : public ATC1602WindowState
    {
    public:
        ATC1602AdjustingValueWindowState(EnumTC1602WindowState windowState, EnumTC1602WindowState previousState, TC1602 *tc1602);
        ~ATC1602AdjustingValueWindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    protected:
        static constexpr uint8_t MAX_SCROLL_POSITION = 2;
        const EnumTC1602WindowState m_PreviousState;
        IncubatorData *m_IncubatorData;
        bool m_bIsInitial;
        uint8_t m_ScrollPosition;
        int16_t m_Value;
        bool m_bIsInSaveScreen;

    protected:
        virtual void PrintCurrentValue() = 0;
        virtual void PrintAdjustingValue() = 0;
        virtual void WriteChanges() = 0;
        virtual int16_t GetInitialValue() = 0;
        void PrintAreChangesSavedQuestion();
        void PrintYesNo();
        void UpdateScrollPosition();
        void UpdateValue();
        void DetermineNextState();
        void InterruptedRefresh();
    };
} // namespace GUI

#endif // _GUI_ATC1602ADJUSTINGVALUEWINDOWSTATE_H_