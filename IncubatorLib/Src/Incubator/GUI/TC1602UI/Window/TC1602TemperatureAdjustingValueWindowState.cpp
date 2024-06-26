#include "Incubator/GUI/TC1602UI/Window/TC1602TemperatureAdjustingValueWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"

using namespace GUI;

TC1602TemperatureAdjustingValueWindowState::TC1602TemperatureAdjustingValueWindowState(TC1602 *tc1602, EnumTC1602WindowState windowState, EnumAdjustingType adjustingType)
    : ATC1602AdjustingValueWindowState{ windowState, TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW, tc1602 },
    m_AdjustingType { adjustingType }
{
}

void TC1602TemperatureAdjustingValueWindowState::PrintCurrentValue()
{
    int16_t temperature = GetCurrentTemperature();
    LOG_DEBUG("Güncel: %02d.%01d", temperature / 10, temperature % 10);
    m_Tc1602->Print('G');
    m_Tc1602->Print(TC1602_CHAR_LOWER_U);
    m_Tc1602->Print("ncel: ");
    m_Tc1602->Print("%02d.%01d", temperature / 10, temperature % 10);
}

void TC1602TemperatureAdjustingValueWindowState::PrintAdjustingValue()
{
    LOG_DEBUG("%02d.%01d ºC", m_Value / 10, m_Value % 10);
    m_Tc1602->Print("%02d.%01d ", m_Value / 10, m_Value % 10);
    m_Tc1602->Print(TC1602_CHAR_DEGREE_SYMBOL);
    m_Tc1602->Print('C');
}

void TC1602TemperatureAdjustingValueWindowState::WriteChanges()
{
    TemperatureData temperatureData;
    if (Storage::Query(temperatureData))
    {
        switch (m_AdjustingType)
        {
        case ADJUSTING_TYPE_MIN_NORMAL:
            temperatureData.m_TemperatureStartInDeciDegrees = m_Value;
            break;
    
        case ADJUSTING_TYPE_MAX_NORMAL:
            temperatureData.m_TemperatureEndInDeciDegrees = m_Value;
            break;
    
        case ADJUSTING_TYPE_MIN_MOTORS_OFF:
            temperatureData.m_MotorsOffTemperatureStartInDeciDegrees = m_Value;
            break;
    
        case ADJUSTING_TYPE_MAX_MOTORS_OFF:
            temperatureData.m_MotorsOffTemperatureEndInDeciDegrees = m_Value;
            break;
    
        default:
            break;
        }
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_READ_TIME_IN_MILLISECOND);
        if (Storage::Write(temperatureData))
        {
            switch (m_AdjustingType)
            {
            case ADJUSTING_TYPE_MIN_NORMAL:
                m_IncubatorData->m_TemperatureStart = m_Value;
                m_IncubatorData->m_TemperatureDesired = (m_IncubatorData->m_TemperatureEnd + m_IncubatorData->m_TemperatureStart) / 2;
                break;

            case ADJUSTING_TYPE_MAX_NORMAL:
                m_IncubatorData->m_TemperatureEnd = m_Value;
                m_IncubatorData->m_TemperatureDesired = (m_IncubatorData->m_TemperatureEnd + m_IncubatorData->m_TemperatureStart) / 2;
                break;

            case ADJUSTING_TYPE_MIN_MOTORS_OFF:
                m_IncubatorData->m_MotorsOffTemperatureStart = m_Value;
                m_IncubatorData->m_MotorsOffTemperatureDesired = (m_IncubatorData->m_MotorsOffTemperatureStart + m_IncubatorData->m_MotorsOffTemperatureEnd) / 2;
                break;

            case ADJUSTING_TYPE_MAX_MOTORS_OFF:
                m_IncubatorData->m_MotorsOffTemperatureEnd = m_Value;
                m_IncubatorData->m_MotorsOffTemperatureDesired = (m_IncubatorData->m_MotorsOffTemperatureStart + m_IncubatorData->m_MotorsOffTemperatureEnd) / 2;
                break;

            default:
                break;
            }
        }
        TimeUtils::SleepInMilliseconds(Storage::STORAGE_WRITE_TIME_IN_MILLISECOND);
    }
}

int16_t TC1602TemperatureAdjustingValueWindowState::GetInitialValue()
{
    return GetCurrentTemperature();
}

int16_t TC1602TemperatureAdjustingValueWindowState::GetCurrentTemperature()
{
    int32_t temperature;
    switch (m_AdjustingType)
    {
    case ADJUSTING_TYPE_MIN_NORMAL:
        temperature = m_IncubatorData->m_TemperatureStart;
        break;

    case ADJUSTING_TYPE_MAX_NORMAL:
        temperature = m_IncubatorData->m_TemperatureEnd;
        break;

    case ADJUSTING_TYPE_MIN_MOTORS_OFF:
        temperature = m_IncubatorData->m_MotorsOffTemperatureStart;
        break;

    case ADJUSTING_TYPE_MAX_MOTORS_OFF:
        temperature = m_IncubatorData->m_MotorsOffTemperatureEnd;
        break;


    default:
        temperature = 0;
        break;
    }
    return temperature;
}
