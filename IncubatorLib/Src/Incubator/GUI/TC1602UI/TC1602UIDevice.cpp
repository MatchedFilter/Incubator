#include "Incubator/GUI/TC1602UI/TC1602UIDevice.h"
#include "Incubator/TimeUtils/TimerTask/TimerTaskController.h"
#include "Incubator/Logger/Logger.h"

using namespace GUI;

TC1602UIDevice::TC1602UIDevice(const char *incubatorVersion) : 
    m_CurrentState { nullptr },
    m_States { 0 },
    m_TC1602ErrorWindowState { &m_Tc1602 }, 
    m_TC1602MainWindowState { &m_Tc1602 },
    m_TC1602MenuWindowState { &m_Tc1602 },
    m_TC1602TemperatureSetWindowState { &m_Tc1602 },
    m_TC1602HumiditySetWindowState { &m_Tc1602 },
    m_TC1602DaySetWindowState { &m_Tc1602 },
    m_TC1602MaxTemperatureAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MAX_TEMPERATURE_ADJUSTING, ADJUSTING_TYPE_MAX_NORMAL },
    m_TC1602MinTemperatureAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MIN_TEMPERATURE_ADJUSTING, ADJUSTING_TYPE_MIN_NORMAL },
    m_TC1602MotorOffMaxTemperatureAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MAX_MOTOR_OFF_TEMPERATURE_ADJUSTING, ADJUSTING_TYPE_MAX_MOTORS_OFF },
    m_TC1602MotorOffMinTemperatureAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MIN_MOTOR_OFF_TEMPERATURE_ADJUSTING, ADJUSTING_TYPE_MIN_MOTORS_OFF },
    m_TC1602MaxHumidityAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MAX_HUMIDITY_ADJUSTING, ADJUSTING_TYPE_MAX_NORMAL },
    m_TC1602MinHumidityAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MIN_HUMIDITY_ADJUSTING, ADJUSTING_TYPE_MIN_NORMAL },
    m_TC1602MotorOffMaxHumidityAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MAX_MOTOR_OFF_HUMIDITY_ADJUSTING, ADJUSTING_TYPE_MAX_MOTORS_OFF },
    m_TC1602MotorOffMinHumidityAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MIN_MOTOR_OFF_HUMIDITY_ADJUSTING, ADJUSTING_TYPE_MIN_MOTORS_OFF },
    m_TC1602TotalDayAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_TOTAL_DAY_ADJUSTING },
    m_TC1602MotorOffDayAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_MOTOR_OFF_DAY_ADJUSTING },
    m_TC1602CurrentDayAdjustingValueWindowState { &m_Tc1602, TC1602_WINDOW_STATE_CURRENT_DAY_ADJUSTING },
    m_TC1602VersionWindowState { &m_Tc1602, incubatorVersion },
    m_TC1602ResetWindowState { &m_Tc1602, &m_TC1602MenuWindowState},
    m_TC1602RefreshingTimerTaskHandler { &m_CurrentState},
    m_PreviousState { TC1602_WINDOW_STATE_MAIN_WINDOW }
{
    m_States[TC1602_WINDOW_STATE_ERROR_WINDOW]                          = &m_TC1602ErrorWindowState;
    m_States[TC1602_WINDOW_STATE_MAIN_WINDOW]                           = &m_TC1602MainWindowState;
    m_States[TC1602_WINDOW_STATE_MENU_WINDOW]                           = &m_TC1602MenuWindowState;
    m_States[TC1602_WINDOW_STATE_TEMPERATURE_SET_WINDOW]                = &m_TC1602TemperatureSetWindowState;
    m_States[TC1602_WINDOW_STATE_HUMIDITY_SET_WINDOW]                   = &m_TC1602HumiditySetWindowState;
    m_States[TC1602_WINDOW_STATE_DAY_SET_WINDOW]                        = &m_TC1602DaySetWindowState;
    m_States[TC1602_WINDOW_STATE_MAX_TEMPERATURE_ADJUSTING]             = &m_TC1602MaxTemperatureAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MIN_TEMPERATURE_ADJUSTING]             = &m_TC1602MinTemperatureAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MAX_MOTOR_OFF_TEMPERATURE_ADJUSTING]   = &m_TC1602MotorOffMaxTemperatureAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MIN_MOTOR_OFF_TEMPERATURE_ADJUSTING]   = &m_TC1602MotorOffMinTemperatureAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MAX_HUMIDITY_ADJUSTING]                = &m_TC1602MaxHumidityAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MIN_HUMIDITY_ADJUSTING]                = &m_TC1602MinHumidityAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MAX_MOTOR_OFF_HUMIDITY_ADJUSTING]      = &m_TC1602MotorOffMaxHumidityAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MIN_MOTOR_OFF_HUMIDITY_ADJUSTING]      = &m_TC1602MotorOffMinHumidityAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_TOTAL_DAY_ADJUSTING]                   = &m_TC1602TotalDayAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_MOTOR_OFF_DAY_ADJUSTING]               = &m_TC1602MotorOffDayAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_CURRENT_DAY_ADJUSTING]                 = &m_TC1602CurrentDayAdjustingValueWindowState;
    m_States[TC1602_WINDOW_STATE_VERSION]                               = &m_TC1602VersionWindowState;
    m_States[TC1602_WINDOW_STATE_RESET]                                 = &m_TC1602ResetWindowState;

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
    if (m_CurrentState != nullptr)
    {
        if (IsThereAnyErrorInData(incubatorData))
        {
            m_CurrentState = m_States[TC1602_WINDOW_STATE_ERROR_WINDOW];
        }
        m_CurrentState->Update(incubatorData, m_PreviousState);
        m_PreviousState = m_CurrentState->m_CurrentWindowState;
        EnumTC1602WindowState nextWindowState = m_CurrentState->GetNextWindowState();
        m_CurrentState = m_States[nextWindowState];
    }
    else
    {
        LOG_DEBUG("TC1602UIDevice::Update Currenstate is null");
    }
}
