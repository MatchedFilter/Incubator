#include "Incubator/GUI/TC1602UI/Window/TC1602DayAdjustingValueWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"

using namespace GUI;

TC1602DayAdjustingValueWindowState::TC1602DayAdjustingValueWindowState(TC1602 *tc1602, EnumTC1602WindowState windowState)
    : ATC1602AdjustingValueWindowState{ windowState, TC1602_WINDOW_STATE_DAY_SET_WINDOW, tc1602 }
{
}

void TC1602DayAdjustingValueWindowState::PrintCurrentValue()
{
    int16_t day = GetCurrentDay();
    LOG_DEBUG("Güncel: %d", day);
    m_Tc1602->Print('G');
    m_Tc1602->Print(TC1602_CHAR_LOWER_U);
    m_Tc1602->Print("ncel: ");
    m_Tc1602->Print("%d", day);
}

void TC1602DayAdjustingValueWindowState::PrintAdjustingValue()
{
    LOG_DEBUG("%d", m_Value);
    m_Tc1602->Print("%d", m_Value);
}

void TC1602DayAdjustingValueWindowState::WriteChanges()
{
    TimeInfoData timeInfoData;
    if (Storage::Query(timeInfoData))
    {
        switch (m_CurrentWindowState)
        {
        case TC1602_WINDOW_STATE_CURRENT_DAY_ADJUSTING:
            timeInfoData.m_IncubatorCurrentTimestampInSeconds = m_Value * 24 * 60 * 60;
            break;

        case TC1602_WINDOW_STATE_TOTAL_DAY_ADJUSTING:
            timeInfoData.m_TotalDayCount = m_Value;
            break;
    
        case TC1602_WINDOW_STATE_MOTOR_OFF_DAY_ADJUSTING:
            timeInfoData.m_MotorOffDayCount = m_Value;
            break;
        
        default:
            break;
        }
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_READ_TIME_IN_MILLISECOND);
        if (Storage::Write(timeInfoData))
        {
            switch (m_CurrentWindowState)
            {
            case TC1602_WINDOW_STATE_CURRENT_DAY_ADJUSTING:
                m_IncubatorData->m_CurrentTimestampInSeconds = timeInfoData.m_IncubatorCurrentTimestampInSeconds;
                TimeUtils::SetTimestampInMilliseconds(m_IncubatorData->m_CurrentTimestampInSeconds * 1000);
                break;

            case TC1602_WINDOW_STATE_TOTAL_DAY_ADJUSTING:
                m_IncubatorData->m_TotalIncubationDayCount = m_Value;
                break;

            case TC1602_WINDOW_STATE_MOTOR_OFF_DAY_ADJUSTING:
                m_IncubatorData->m_MotorOffDayCount = m_Value;
                break;

            default:
                break;
            }
        }
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_WRITE_TIME_IN_MILLISECOND);
    }
}

int16_t TC1602DayAdjustingValueWindowState::GetInitialValue()
{
    return (int16_t)GetCurrentDay();
}

uint8_t TC1602DayAdjustingValueWindowState::GetCurrentDay()
{
    int32_t day;
    switch (m_CurrentWindowState)
    {
    case TC1602_WINDOW_STATE_CURRENT_DAY_ADJUSTING:
        day = m_IncubatorData->m_CurrentTimestampInSeconds / 24 / 60 / 60;
        break;

    case TC1602_WINDOW_STATE_TOTAL_DAY_ADJUSTING:
        day = m_IncubatorData->m_TotalIncubationDayCount;
        break;

    case TC1602_WINDOW_STATE_MOTOR_OFF_DAY_ADJUSTING:
        day = m_IncubatorData->m_MotorOffDayCount;
        break;


    default:
        day = 0;
        break;
    }
    return day;
}
