#include "Incubator/GUI/TC1602UI/Window/TC1602MinTemperatureAdjustingValueWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"

using namespace GUI;

TC1602MinTemperatureAdjustingValueWindowState::TC1602MinTemperatureAdjustingValueWindowState(TC1602 *tc1602)
    : ATC1602AdjustingValueWindowState{ TC1602_WINDOW_STATE_MIN_TEMPERATURE_ADJUSTING_VALUE, TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW, tc1602 }
{
}

void TC1602MinTemperatureAdjustingValueWindowState::PrintCurrentValue()
{
    LOG_DEBUG("Güncel: %02d.%01d", m_IncubatorData->m_TemperatureStart / 10, m_IncubatorData->m_TemperatureStart % 10);
    m_Tc1602->Print('G');
    m_Tc1602->Print(TC1602_CHAR_LOWER_U);
    m_Tc1602->Print("ncel: ");
    m_Tc1602->Print("%02d.%01d", m_IncubatorData->m_TemperatureStart / 10, m_IncubatorData->m_TemperatureStart % 10);
}

void TC1602MinTemperatureAdjustingValueWindowState::PrintAdjustingValue()
{
    LOG_DEBUG("%02d.%01d ºC", m_Value / 10, m_Value % 10);
    m_Tc1602->Print("%02d.%01d ", m_Value / 10, m_Value % 10);
    m_Tc1602->Print(TC1602_CHAR_DEGREE_SYMBOL);
    m_Tc1602->Print('C');
}

void TC1602MinTemperatureAdjustingValueWindowState::WriteChanges()
{
    TemperatureData temperatureData;
    if (Storage::Query(temperatureData))
    {
        TimeUtils::SleepInMilliseconds(50);
        temperatureData.m_TemperatureStartInDeciDegrees = m_Value;
        if (Storage::Write(temperatureData))
        {
            m_IncubatorData->m_TemperatureStart = m_Value;
            m_IncubatorData->m_TemperatureDesired = (m_IncubatorData->m_TemperatureEnd + m_IncubatorData->m_TemperatureStart) / 2;
        }
        TimeUtils::SleepInMilliseconds(50);
    }
}

int32_t TC1602MinTemperatureAdjustingValueWindowState::GetInitialValue()
{
    return m_IncubatorData->m_TemperatureStart;
}
