#include "Incubator/GUI/TC1602UI/TimerTasks/TC1602RefreshingTimerTaskHandler.h"

using namespace GUI;

TC1602RefreshingTimerTaskHandler::TC1602RefreshingTimerTaskHandler(ATC1602WindowState **currentState) : 
    m_CurrentState { currentState }
{
}

void TC1602RefreshingTimerTaskHandler::OnTimeout(TaskID taskId)
{
    (*m_CurrentState)->Refresh();
}