#include "Incubator/GUI/TC1602UI/Window/TC1602TemperatureSetWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602TemperatureSetWindowState::TC1602TemperatureSetWindowState(TC1602 *tc1602)
    : ATC1602WindowState{TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW, tc1602}, m_ScrollPosition { 0 }, m_IncubatorData { nullptr }, m_bIsInitial { true } { }


void TC1602TemperatureSetWindowState::UpdateScrollPosition()
{
    if (m_ScrollPosition < MAX_SCROLL_POSITION && m_IncubatorData->m_bIsButtonDown)
    {
        m_ScrollPosition++;
        InterruptedRefresh();
    }
    else if (m_ScrollPosition > 0 && m_IncubatorData->m_bIsButtonUp)
    {
        m_ScrollPosition--;
        InterruptedRefresh();
    }
    else if (m_IncubatorData->m_bIsButtonLeft)
    {
        m_ScrollPosition = 0;
        m_bIsInitial = true;
        m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
    }
    else
    {
    }
}

void TC1602TemperatureSetWindowState::PrintLine(uint8_t lineCount)
{
    switch (lineCount)
    {
    case 0:
    	{
            LOG_DEBUG_RAW("Sck. ayarla\n");
            m_Tc1602->Print("Sck. ayarla");
    	}
        break;

    case 1:
    	{
            LOG_DEBUG_RAW("Maksimum ayarla\n");
            m_Tc1602->Print("Maksimum ayarla");
		}
        break;

    case 2:
    	{
            LOG_DEBUG_RAW("Minimum ayarla\n");
            m_Tc1602->Print("Minimum ayarla");
    	}
        break;

    case 3:
    	{
            LOG_DEBUG_RAW("\n");
    	}
        break;

    default:
        break;
    }
}

void TC1602TemperatureSetWindowState::DetermineNextState()
{
    if (m_IncubatorData->m_bIsButtonClicked == true)
    {
        switch (m_ScrollPosition)
        {
        case 0:
            m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
            break;

        
        default:
            break;
        }
        m_ScrollPosition = 0;
        m_bIsInitial = true;
    }
}

void TC1602TemperatureSetWindowState::Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW;
    if (m_bIsInitial)
    {
        InterruptedRefresh();
        m_bIsInitial = false;
    }
    UpdateScrollPosition();
    DetermineNextState();
}

void TC1602TemperatureSetWindowState::Refresh()
{
}

void TC1602TemperatureSetWindowState::InterruptedRefresh()
{
    if (m_IncubatorData != nullptr)
    {
        m_Tc1602->ClearScreen();
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
        if (m_ScrollPosition != 0)
        {
            m_Tc1602->Print(TC1602_CHAR_ARROW_SYMBOL);
            LOG_DEBUG_WITHOUT_ENDL("->");
        }
        else
        {
            LOG_DEBUG_WITHOUT_ENDL("");
        }
        PrintLine(m_ScrollPosition);
        LOG_DEBUG_WITHOUT_ENDL("");
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
        PrintLine(m_ScrollPosition + 1);
    }
}



EnumTC1602WindowState TC1602TemperatureSetWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
