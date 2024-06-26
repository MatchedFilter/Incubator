#include "Incubator/GUI/TC1602UI/Window/TC1602DaySetWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602DaySetWindowState::TC1602DaySetWindowState(TC1602 *tc1602)
    : ATC1602WindowState{TC1602_WINDOW_STATE_DAY_SET_WINDOW, tc1602}, m_ScrollPosition { 0 }, m_IncubatorData { nullptr }, m_bIsInitial { true } { }


void TC1602DaySetWindowState::UpdateScrollPosition()
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

void TC1602DaySetWindowState::PrintLine(uint8_t lineCount)
{
    switch (lineCount)
    {
    case 0:
    	{
            LOG_DEBUG_RAW("Gün ayarla\n");
            m_Tc1602->Print('G');
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print("n ayarla");
    	}
        break;

    case 1:
    	{
            LOG_DEBUG_RAW("Toplam gün\n");
            m_Tc1602->Print("Toplam g");
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print('n');
		}
        break;

    case 2:
    	{
            LOG_DEBUG_RAW("Motorsuz gün\n");
            m_Tc1602->Print("Motorsuz");
            m_Tc1602->Print(" g");
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print('n');
    	}
        break;

    case 3:
    	{
            LOG_DEBUG_RAW("Güncel gün\n");
            m_Tc1602->Print('G');
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print("ncel g");
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print('n');
    	}
        break;

    case 5:
    	{
            LOG_DEBUG_RAW("\n");
    	}
        break;

    default:
        break;
    }
}

void TC1602DaySetWindowState::DetermineNextState()
{
    if (m_IncubatorData->m_bIsButtonClicked == true)
    {
        switch (m_ScrollPosition)
        {
        case 0:
            m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
            break;

        case 1:
            m_NextWindowState = TC1602_WINDOW_STATE_TOTAL_DAY_ADJUSTING;
            break;

        case 2:
            m_NextWindowState = TC1602_WINDOW_STATE_MOTOR_OFF_DAY_ADJUSTING;
            break;

        case 3:
            m_NextWindowState = TC1602_WINDOW_STATE_CURRENT_DAY_ADJUSTING;
            break;

        default:
            m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
            m_ScrollPosition = 0;
            break;
        }
        m_bIsInitial = true;
    }
}

void TC1602DaySetWindowState::Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = TC1602_WINDOW_STATE_DAY_SET_WINDOW;
    if (m_bIsInitial)
    {
        InterruptedRefresh();
        m_bIsInitial = false;
    }
    UpdateScrollPosition();
    DetermineNextState();
}

void TC1602DaySetWindowState::Refresh()
{
}

void TC1602DaySetWindowState::InterruptedRefresh()
{
    if (m_IncubatorData != nullptr)
    {
        m_Tc1602->ClearScreen();
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
        if (m_ScrollPosition != 0)
        {
            m_Tc1602->Print(TC1602_CHAR_ARROW_SYMBOL);
            LOG_DEBUG_WITHOUT_ENDL("→");
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

EnumTC1602WindowState TC1602DaySetWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
