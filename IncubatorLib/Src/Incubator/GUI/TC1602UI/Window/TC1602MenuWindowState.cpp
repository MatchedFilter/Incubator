#include "Incubator/GUI/TC1602UI/Window/TC1602MenuWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602MenuWindowState::TC1602MenuWindowState(TC1602 *tc1602)
    : ATC1602WindowState{TC1602_WINDOW_STATE_MENU_WINDOW, tc1602}, m_ScrollPosition { 0 }, m_IncubatorData { nullptr }, m_bIsInitial { true } { }


void TC1602MenuWindowState::UpdateScrollPosition()
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
        m_NextWindowState = TC1602_WINDOW_STATE_MAIN_WINDOW;
    }
    else
    {
    }
}

void TC1602MenuWindowState::PrintLine(uint8_t lineCount)
{
    switch (lineCount)
    {
    case 0:
    	{
            m_Tc1602->Print("Men");
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print(" Ekran");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            LOG_DEBUG("Menü Ekranı");
    	}
        break;

    case 1:
    	{
            m_Tc1602->Print('S');
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            m_Tc1602->Print("cakl");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            m_Tc1602->Print("k ayar");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            LOG_DEBUG_RAW("Sıcaklık ayarı\n");
		}
        break;

    case 2:
    	{
            m_Tc1602->Print('G');
            m_Tc1602->Print(TC1602_CHAR_LOWER_U);
            m_Tc1602->Print("n ");
            m_Tc1602->Print("ayar");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            LOG_DEBUG_RAW("Gün ayarı\n");
    	}
        break;

    case 3:
    	{
            m_Tc1602->Print("Nem ");
            m_Tc1602->Print("ayar");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            LOG_DEBUG_RAW("Nem ayarı\n");
    	}
        break;

    case 4:
    	{
            m_Tc1602->Print("Versiyon");
            LOG_DEBUG_RAW("Versiyon\n");
    	}
        break;

    case 5:
    	{
            m_Tc1602->Print('S');
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            m_Tc1602->Print('f');
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            m_Tc1602->Print("rla");
            LOG_DEBUG_RAW("Sıfırla\n");
    	}
        break;

    case 6:
        LOG_DEBUG_RAW("\n");
        break;
    
    default:
        break;
    }
}

void TC1602MenuWindowState::DetermineNextState()
{
    if (m_IncubatorData->m_bIsButtonClicked == true || m_IncubatorData->m_bIsButtonRight == true)
    {
        switch (m_ScrollPosition)
        {
        case 0:
        {
            if (m_IncubatorData->m_bIsButtonRight != true)
            {
                m_NextWindowState = TC1602_WINDOW_STATE_MAIN_WINDOW;
            }
            break;
        }

        case 1:
            m_NextWindowState = TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW;
            break;

        case 2:
            m_NextWindowState = TC1602_WINDOW_STATE_DAY_SET_WINDOW;
            break;

        case 3:
            m_NextWindowState = TC1602_WINDOW_STATE_HUMIDITY_SET_WINDOW;
            break;

        case 4:
            m_NextWindowState = TC1602_WINDOW_STATE_VERSION;
            break;

        case 5:
            m_NextWindowState = TC1602_WINDOW_STATE_RESET;
            break;

        default:
            m_ScrollPosition = 0;
            break;
        }
        m_bIsInitial = true;
    }
}

void TC1602MenuWindowState::Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
    if (m_bIsInitial)
    {
    switch (previousState)
    {
    case TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW:
        m_ScrollPosition = 1;
        break;

    case TC1602_WINDOW_STATE_HUMIDITY_SET_WINDOW:
        m_ScrollPosition = 3;
        break;

    case TC1602_WINDOW_STATE_VERSION:
        m_ScrollPosition = 4;
        break;

    case TC1602_WINDOW_STATE_RESET:
        m_ScrollPosition = 5;
        break;
    
    default:
        break;
    }
        InterruptedRefresh();
        m_bIsInitial = false;
    }
    UpdateScrollPosition();
    DetermineNextState();
}

void TC1602MenuWindowState::Refresh()
{
}

void TC1602MenuWindowState::InterruptedRefresh()
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

EnumTC1602WindowState TC1602MenuWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
