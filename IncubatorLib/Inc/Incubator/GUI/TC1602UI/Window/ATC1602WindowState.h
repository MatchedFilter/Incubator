#ifndef _GUI_ATC1602WINDOWSTATE_H_
#define _GUI_ATC1602WINDOWSTATE_H_
#include "Incubator/IncubatorData.h"
#include "EnumTC1602WindowState.h"
#include "TC1602/TC1602.h"
namespace GUI
{
    class ATC1602WindowState
    {
    public:
        ATC1602WindowState(EnumTC1602WindowState windowState, TC1602 *tc1602) :
            m_CurrentWindowState { windowState },
            m_Tc1602 { tc1602 },
            m_NextWindowState { m_CurrentWindowState } {}
        virtual ~ATC1602WindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) = 0;
        virtual void Refresh() = 0;
        virtual EnumTC1602WindowState GetNextWindowState() = 0;
        const EnumTC1602WindowState m_CurrentWindowState;

    protected:
        TC1602 *m_Tc1602;
        EnumTC1602WindowState m_NextWindowState;

    };
} // namespace GUI

#endif // _GUI_ATC1602WINDOWSTATE_H_