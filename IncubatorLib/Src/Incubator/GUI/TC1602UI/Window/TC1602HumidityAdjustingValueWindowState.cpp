#include "Incubator/GUI/TC1602UI/Window/TC1602HumidityAdjustingValueWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"

using namespace GUI;

TC1602HumidityAdjustingValueWindowState::TC1602HumidityAdjustingValueWindowState(TC1602 *tc1602, EnumTC1602WindowState windowState, EnumAdjustingType adjustingType)
    : ATC1602AdjustingValueWindowState{ windowState, TC1602_WINDOW_STATE_HUMIDITY_SET_WINDOW, tc1602 },
    m_AdjustingType { adjustingType }
{
}

void TC1602HumidityAdjustingValueWindowState::PrintCurrentValue()
{
    int16_t humidity = GetCurrentHumidity();
    LOG_DEBUG("Güncel: %%%02d", humidity);
    m_Tc1602->Print('G');
    m_Tc1602->Print(TC1602_CHAR_LOWER_U);
    m_Tc1602->Print("ncel: ");
    m_Tc1602->Print("%%%02d", humidity);
}

void TC1602HumidityAdjustingValueWindowState::PrintAdjustingValue()
{
    LOG_DEBUG("%%%02d", m_Value);
    m_Tc1602->Print("%%%02d", m_Value);
}

void TC1602HumidityAdjustingValueWindowState::WriteChanges()
{
    HumidityData humidityData;
    if (Storage::Query(humidityData))
    {
        switch (m_AdjustingType)
        {
        case ADJUSTING_TYPE_MIN_NORMAL:
            humidityData.m_HumidityStartPercentage = m_Value;
            break;
    
        case ADJUSTING_TYPE_MAX_NORMAL:
            humidityData.m_HumidityEndPercentage = m_Value;
            break;
    
        case ADJUSTING_TYPE_MIN_MOTORS_OFF:
            humidityData.m_MotorsOffHumidityStartPercentage = m_Value;
            break;
    
        case ADJUSTING_TYPE_MAX_MOTORS_OFF:
            humidityData.m_MotorsOffHumidityEndPercentage = m_Value;
            break;
    
        default:
            break;
        }
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_READ_TIME_IN_MILLISECOND);
        if (Storage::Write(humidityData))
        {
            switch (m_AdjustingType)
            {
            case ADJUSTING_TYPE_MIN_NORMAL:
                m_IncubatorData->m_HumidityStart = m_Value;
                m_IncubatorData->m_HumidityDesired = (m_IncubatorData->m_HumidityEnd + m_IncubatorData->m_HumidityStart) / 2;
                break;

            case ADJUSTING_TYPE_MAX_NORMAL:
                m_IncubatorData->m_HumidityEnd = m_Value;
                m_IncubatorData->m_HumidityDesired = (m_IncubatorData->m_HumidityEnd + m_IncubatorData->m_HumidityStart) / 2;
                break;

            case ADJUSTING_TYPE_MIN_MOTORS_OFF:
                m_IncubatorData->m_MotorsOffHumidityStart = m_Value;
                m_IncubatorData->m_MotorsOffHumidityDesired = (m_IncubatorData->m_MotorsOffHumidityStart + m_IncubatorData->m_MotorsOffHumidityEnd) / 2;
                break;

            case ADJUSTING_TYPE_MAX_MOTORS_OFF:
                m_IncubatorData->m_MotorsOffHumidityEnd = m_Value;
                m_IncubatorData->m_MotorsOffHumidityDesired = (m_IncubatorData->m_MotorsOffHumidityStart + m_IncubatorData->m_MotorsOffHumidityEnd) / 2;
                break;

            default:
                break;
            }
        }
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_WRITE_TIME_IN_MILLISECOND);
    }
}

int16_t TC1602HumidityAdjustingValueWindowState::GetInitialValue()
{
    return (int16_t)GetCurrentHumidity();
}

uint8_t TC1602HumidityAdjustingValueWindowState::GetCurrentHumidity()
{
    int32_t humidity;
    switch (m_AdjustingType)
    {
    case ADJUSTING_TYPE_MIN_NORMAL:
        humidity = m_IncubatorData->m_HumidityStart;
        break;

    case ADJUSTING_TYPE_MAX_NORMAL:
        humidity = m_IncubatorData->m_HumidityEnd;
        break;

    case ADJUSTING_TYPE_MIN_MOTORS_OFF:
        humidity = m_IncubatorData->m_MotorsOffHumidityStart;
        break;

    case ADJUSTING_TYPE_MAX_MOTORS_OFF:
        humidity = m_IncubatorData->m_MotorsOffHumidityEnd;
        break;


    default:
        humidity = 0;
        break;
    }
    return humidity;
}
