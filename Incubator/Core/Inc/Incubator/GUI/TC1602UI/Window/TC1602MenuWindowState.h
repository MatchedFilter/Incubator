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
        virtual void Update(IncubatorData &incubatorData) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    private:
        uint8_t m_ScrollPosition;
        bool m_bIsInitial;
    };
} // namespace GUI

#endif // _GUI_TC1602MENUWINDOWSTATE_H_