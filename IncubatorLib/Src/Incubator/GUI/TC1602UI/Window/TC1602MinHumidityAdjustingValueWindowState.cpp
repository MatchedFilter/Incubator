#include "Incubator/GUI/TC1602UI/Window/TC1602MinHumidityAdjustingValueWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"

using namespace GUI;

TC1602MinHumidityAdjustingValueWindowState::TC1602MinHumidityAdjustingValueWindowState(TC1602 *tc1602)
    : ATC1602AdjustingValueWindowState{ TC1602_WINDOW_STATE_MIN_HUMIDITY_ADJUSTING_VALUE, TC1602_WINDOW_STATE_HUMIDITY_SET_WINDOW, tc1602 }
{
}

void TC1602MinHumidityAdjustingValueWindowState::PrintCurrentValue()
{
    LOG_DEBUG("Güncel: %%%02d", m_IncubatorData->m_HumidityStart);
    m_Tc1602->Print('G');
    m_Tc1602->Print(TC1602_CHAR_LOWER_U);
    m_Tc1602->Print("ncel: ");
    m_Tc1602->Print("%%%02d", m_IncubatorData->m_HumidityStart);
}

void TC1602MinHumidityAdjustingValueWindowState::PrintAdjustingValue()
{
    LOG_DEBUG("%%%02d", m_Value);
    m_Tc1602->Print("%%%02d", m_Value);
}

void TC1602MinHumidityAdjustingValueWindowState::WriteChanges()
{
    HumidityData humidityData;
    if (Storage::Query(humidityData))
    {
        TimeUtils::SleepInMilliseconds(50);
        humidityData.m_HumidityStartPercentage = m_Value;
        if (Storage::Write(humidityData))
        {
            m_IncubatorData->m_HumidityStart = m_Value;
            m_IncubatorData->m_HumidityDesired = (m_IncubatorData->m_HumidityEnd + m_IncubatorData->m_HumidityStart) / 2;
        }
        TimeUtils::SleepInMilliseconds(50);
    }
}

int32_t TC1602MinHumidityAdjustingValueWindowState::GetInitialValue()
{
    return m_IncubatorData->m_HumidityStart;
}
