#include "Incubator/TimeUtils/TimerTask/TimerTaskController.h"
#include "Incubator/TimeUtils/TimeUtils.h"

#include "TimerTask.h"

static constexpr const int32_t TIMER_TASK_SIZE = 8;
static TimerTask s_TimerTasks[TIMER_TASK_SIZE];
static ITimerTaskHandler *s_TaskHandlers[TIMER_TASK_SIZE] = { 0 };


TaskID TimerTaskController::RegisterTask(ITimerTaskHandler *taskHandler, int64_t durationInMilliseconds, bool m_bIsPeriodic)
{
    TaskID taskID = INVALID_TIMER_TASK_ID;
    for (uint8_t i = 0; i < TIMER_TASK_SIZE; i++)
    {
        if(s_TimerTasks[i].m_TaskId == INVALID_TIMER_TASK_ID)
        {
            s_TimerTasks[i].m_TaskId = i;
            s_TimerTasks[i].m_DurationInMillisecond = durationInMilliseconds;
            s_TimerTasks[i].m_bIsPeriodic = m_bIsPeriodic;
            taskID = s_TimerTasks[i].m_TaskId;
            s_TaskHandlers[i] = taskHandler;
            break;
        }
    }
    return taskID;
}

void TimerTaskController::StartTask(TaskID taskID)
{
    if (s_TimerTasks[taskID].m_TaskId == taskID)
    {
        s_TimerTasks[taskID].m_StartTimestampInMillisecond = TimeUtils::GetTimestampInMilliseconds();
        s_TimerTasks[taskID].m_bIsStarted = true;
    }
}

void TimerTaskController::StopTask(TaskID taskID)
{
    if (s_TimerTasks[taskID].m_TaskId == taskID)
    {
        s_TimerTasks[taskID].m_bIsStarted = false;
    }
}

void TimerTaskController::DeleteTask(TaskID taskID)
{
    if (s_TimerTasks[taskID].m_TaskId == taskID)
    {
        s_TimerTasks[taskID].Reset();
    }
}

void TimerTaskController::Run()
{
    for (TaskID taskId = 0; taskId < TIMER_TASK_SIZE; taskId++)
    {
        if (s_TimerTasks[taskId].m_TaskId == taskId)
        {
            if (s_TimerTasks[taskId].m_bIsStarted)
            {
                if (s_TimerTasks[taskId].m_DurationInMillisecond + s_TimerTasks[taskId].m_StartTimestampInMillisecond < TimeUtils::GetTimestampInMilliseconds())
                {
                    if (s_TimerTasks[taskId].m_bIsPeriodic)
                    {
                        s_TimerTasks[taskId].m_StartTimestampInMillisecond = TimeUtils::GetTimestampInMilliseconds();
                        s_TimerTasks[taskId].m_bIsStarted = true;
                    }
                    else
                    {
                        s_TimerTasks[taskId].m_bIsStarted = false;
                    }
                    s_TaskHandlers[taskId]->OnTimeout(taskId);
                }
            }
        }
    }
}
