#include "Incubator/GUI/TC1602UI/Window/TC1602VersionWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602VersionWindowState::TC1602VersionWindowState(TC1602 *tc1602, const char *incubatorVersion)
    : ATC1602WindowState{TC1602_WINDOW_STATE_VERSION, tc1602}, m_IncubatorSoftwareVersion { incubatorVersion },
    m_IncubatorData { nullptr }, m_bIsInitial { true } { }

void TC1602VersionWindowState::DetermineNextState()
{
    if (m_IncubatorData->m_bIsButtonClicked == true || m_IncubatorData->m_bIsButtonLeft == true)
    {
        m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
        m_bIsInitial = true;
    }
}

void TC1602VersionWindowState::Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = TC1602_WINDOW_STATE_VERSION;
    if (m_bIsInitial)
    {
        InterruptedRefresh();
        m_bIsInitial = false;
    }
    DetermineNextState();
}

void TC1602VersionWindowState::Refresh()
{
}

void TC1602VersionWindowState::InterruptedRefresh()
{
    if (m_IncubatorData != nullptr)
    {
        m_Tc1602->ClearScreen();
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
        m_Tc1602->Print("Versiyon: %s", m_IncubatorSoftwareVersion);
        LOG_DEBUG("Versiyon: %s", m_IncubatorSoftwareVersion);
    }
}

EnumTC1602WindowState TC1602VersionWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
