#include "Incubator/GUI/TC1602UI/TC1602UIDevice.h"
#include "Incubator/TimeUtils/TimerTask/TimerTaskController.h"

using namespace GUI;

TC1602UIDevice::TC1602UIDevice() : 
    m_CurrentState { nullptr },
    m_States { 0 },
    m_TC1602ErrorWindowState { &m_Tc1602 }, 
    m_TC1602MainWindowState { &m_Tc1602 },
    m_TC1602MenuWindowState { &m_Tc1602 },
    m_TC1602RefreshingTimerTaskHandler { &m_CurrentState}
{
    m_States[TC1602_WINDOW_STATE_ERROR_WINDOW]  = &m_TC1602ErrorWindowState;
    m_States[TC1602_WINDOW_STATE_MAIN_WINDOW]   = &m_TC1602MainWindowState;
    m_States[TC1602_WINDOW_STATE_MENU_WINDOW]   = &m_TC1602MenuWindowState;

    m_CurrentState = m_States[TC1602_WINDOW_STATE_MAIN_WINDOW];
}

bool TC1602UIDevice::IsThereAnyErrorInData(const IncubatorData &incubatorData)
{
    bool bResult = false;
    if (incubatorData.m_MemoryDeviceErrorState == ERROR_STATE_ERROR ||
        incubatorData.m_HumiditySensorStatus == SENSOR_STATUS_ERROR ||
        incubatorData.m_TemperatureSensorStatus == SENSOR_STATUS_ERROR)
    {
        bResult = true;
    }
    return bResult;
}


void TC1602UIDevice::Initialize()
{
    TaskID tc1602RefreshingTimerTaskId = TimerTaskController::RegisterTask(&m_TC1602RefreshingTimerTaskHandler, TC1602_REFRESHING_TIME_IN_MILLISECOND, true);
    TimerTaskController::StartTask(tc1602RefreshingTimerTaskId);
    m_Tc1602.Initialize();
}

void TC1602UIDevice::Update(IncubatorData &incubatorData)
{
    if (IsThereAnyErrorInData(incubatorData))
    {
        m_CurrentState = m_States[TC1602_WINDOW_STATE_ERROR_WINDOW];
    }
    m_CurrentState->Update(incubatorData);
    EnumTC1602WindowState nextWindowState = m_CurrentState->GetNextWindowState();
    m_CurrentState = m_States[nextWindowState];
}
