#include "Incubator/GUI/TC1602UI/Window/TC1602MenuWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602MenuWindowState::TC1602MenuWindowState(TC1602 *tc1602)
    : ATC1602WindowState{TC1602_WINDOW_STATE_MENU_WINDOW, tc1602}, m_bIsInitial { true } { }


void TC1602MenuWindowState::Update(IncubatorData &incubatorData)
{
    m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
    if (m_bIsInitial)
    {
        m_bIsInitial = false;
        m_Tc1602->ClearScreen();
        m_Tc1602->Print("Men");
        m_Tc1602->Print(TC1602_CHAR_LOWER_U);
        m_Tc1602->Print(" Ekran");
        m_Tc1602->Print(TC1602_CHAR_LOWER_I);
        LOG_DEBUG("Menü Ekranı");
    }
    if (incubatorData.m_bIsButtonClicked == true)
    {
        m_bIsInitial = true;
        m_NextWindowState = TC1602_WINDOW_STATE_MAIN_WINDOW;
    }
}

void TC1602MenuWindowState::Refresh()
{
}


EnumTC1602WindowState TC1602MenuWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
