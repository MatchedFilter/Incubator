#include "Incubator/GUI/TC1602UI/Window/TC1602ErrorWindowState.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602ErrorWindowState::TC1602ErrorWindowState(TC1602 *tc1602)
    : ATC1602WindowState{TC1602_WINDOW_STATE_ERROR_WINDOW, tc1602}, m_LastErrorCode { ERROR_CODE_NO_ERROR } { }


void TC1602ErrorWindowState::SendSensorErrorString()
{
    m_Tc1602->Print("sens");
    m_Tc1602->Print(TC1602_CHAR_LOWER_O);
    m_Tc1602->Print("r hatas");
    m_Tc1602->Print(TC1602_CHAR_LOWER_I);
}


void TC1602ErrorWindowState::Update(IncubatorData &incubatorData)
{
    m_NextWindowState = TC1602_WINDOW_STATE_ERROR_WINDOW;
    if (incubatorData.m_MemoryDeviceErrorState == ERROR_STATE_ERROR)
    {
        if (m_LastErrorCode != ERROR_CODE_MEMORY_ERROR)
        {
            m_LastErrorCode = ERROR_CODE_MEMORY_ERROR;
            m_Tc1602->ClearScreen();
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
            m_Tc1602->Print("HATA: Bellek");
            LOG_DEBUG("HATA: Bellek");
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
            SendSensorErrorString();
            LOG_DEBUG("sensör hatası");
        }
    }
    else if (incubatorData.m_HumiditySensorStatus == SENSOR_STATUS_ERROR)
    {
        if (m_LastErrorCode != ERROR_CODE_HUMIDITY_ERROR)
        {
            m_LastErrorCode = ERROR_CODE_HUMIDITY_ERROR;
            m_Tc1602->ClearScreen();
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
            m_Tc1602->Print("HATA: Nem");
            LOG_DEBUG("HATA: Nem");
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
            SendSensorErrorString();
            LOG_DEBUG("sensör hatası");
        }
    }
    else if (incubatorData.m_TemperatureSensorStatus == SENSOR_STATUS_ERROR )
    {
        if (m_LastErrorCode != ERROR_CODE_TEMPERATURE_ERROR)
        {
            m_LastErrorCode = ERROR_CODE_TEMPERATURE_ERROR;
            m_Tc1602->ClearScreen();
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
            m_Tc1602->Print("HATA: S");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            m_Tc1602->Print("cakl");
            m_Tc1602->Print(TC1602_CHAR_LOWER_I);
            m_Tc1602->Print("k");
            LOG_DEBUG("HATA: Sıcaklık");
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
            SendSensorErrorString();
            LOG_DEBUG("sensör hatası");
        }
    }
    else
    {
        m_LastErrorCode = ERROR_CODE_NO_ERROR;
        m_NextWindowState = TC1602_WINDOW_STATE_MAIN_WINDOW;
    }
}

void TC1602ErrorWindowState::Refresh()
{
}

EnumTC1602WindowState TC1602ErrorWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
