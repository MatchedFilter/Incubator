#include "Incubator/GUI/TC1602UI/Window/TC1602MainWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602MainWindowState::TC1602MainWindowState(TC1602 *tc1602)
    : ATC1602WindowState{TC1602_WINDOW_STATE_MAIN_WINDOW, tc1602},
        m_ScrollPosition { 0 }, m_IncubatorData { nullptr }, m_bIsInitial { true } { }



void TC1602MainWindowState::PrintLine(uint8_t lineCount)
{
    switch (lineCount)
    {
    case 0:
    	{
    		m_Tc1602->Print("Nem: ");
    		LOG_DEBUG_WITHOUT_ENDL("Nem: ");
            if (m_IncubatorData->m_HumiditySensorStatus == SENSOR_STATUS_INITIALIZATION)
            {
                m_Tc1602->Print("...");
    		    LOG_DEBUG_RAW("...");
            }
            else
            {
                m_Tc1602->Print("%%%d", m_IncubatorData->m_HumidityInPercentage);
    		    LOG_DEBUG_RAW("%%%d", m_IncubatorData->m_HumidityInPercentage);
            }
    		m_Tc1602->Print(" / %%%d", m_IncubatorData->m_HumidityDesired);
    		LOG_DEBUG_RAW(" / %%%d\n", m_IncubatorData->m_HumidityDesired);
    	}
        break;

    case 1:
    	{
            if (m_IncubatorData->m_TemperatureSensorStatus == SENSOR_STATUS_INITIALIZATION)
            {
    		    m_Tc1602->Print("...");
    		    LOG_DEBUG_WITHOUT_ENDL("...");
            }
            else
            {
    		    m_Tc1602->Print("%02d.%02d", m_IncubatorData->m_TemperatureInMilliDegree / 1000, (m_IncubatorData->m_TemperatureInMilliDegree / 10) % 100);
    		    LOG_DEBUG_WITHOUT_ENDL("%02d.%02d", m_IncubatorData->m_TemperatureInMilliDegree / 1000, (m_IncubatorData->m_TemperatureInMilliDegree / 10) % 100);
            }
        	m_Tc1602->Print(" / %02d.%02d ", m_IncubatorData->m_TemperatureDesired / 1000, (m_IncubatorData->m_TemperatureDesired / 10) % 100);
        	m_Tc1602->Print(TC1602_CHAR_DEGREE_SYMBOL);
			m_Tc1602->Print("C");
    		LOG_DEBUG_RAW(" / %02d.%02d ºC\n", m_IncubatorData->m_TemperatureDesired / 1000, (m_IncubatorData->m_TemperatureDesired / 10) % 100);
		}
        break;

    case 2:
    	{
    		const uint8_t leftDayCount = (m_IncubatorData->m_CurrentTimestampInSeconds - m_IncubatorData->m_StartTimestampInSeconds) / 60 / 60 / 24;
    		m_Tc1602->Print("%d / %d g", leftDayCount, m_IncubatorData->m_TotalIncubationDayCount);
    		m_Tc1602->Print(TC1602_CHAR_LOWER_U);
    		m_Tc1602->Print("n");
            LOG_DEBUG("%d / %d gün", leftDayCount, m_IncubatorData->m_TotalIncubationDayCount);
    	}
        break;
    
    default:
        break;
    }
}

void TC1602MainWindowState::UpdateScrollPosition()
{
    if (m_ScrollPosition < MAX_SCROLL_POSITION && m_IncubatorData->m_bIsButtonDown)
    {
        m_ScrollPosition++;
        Refresh();
    }
    else if (m_ScrollPosition > 0 && m_IncubatorData->m_bIsButtonUp)
    {
        m_ScrollPosition--;
        Refresh();
    }
    else
    {
    }
}

void TC1602MainWindowState::DetermineNextState(const IncubatorData &incubatorData)
{
    if (m_IncubatorData->m_bIsButtonClicked == true)
    {
        m_ScrollPosition = 0;
        m_bIsInitial = true;
        m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
    }
}

void TC1602MainWindowState::Update(IncubatorData &incubatorData)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = TC1602_WINDOW_STATE_MAIN_WINDOW;
    if (m_bIsInitial)
    {
        Refresh();
        m_bIsInitial = false;
    }
    UpdateScrollPosition();
    DetermineNextState(incubatorData);
}

void TC1602MainWindowState::Refresh()
{
    if (m_IncubatorData != nullptr)
    {
        m_Tc1602->ClearScreen();
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
        PrintLine(m_ScrollPosition);
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
        PrintLine(m_ScrollPosition + 1);
    }
}

EnumTC1602WindowState TC1602MainWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}