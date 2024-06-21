#ifndef _TIMERTASK_H_H
#define _TIMERTASK_H_H
#include "Incubator/TimeUtils/TimerTask/TimerTaskDefinitions.h"

class TimerTask
{

public:
    TimerTask() { Reset(); }
    ~TimerTask() = default;
    TaskID GetTaskID() const { return m_TaskId; };
    void Reset()
    {
        m_TaskId = INVALID_TIMER_TASK_ID; 
        m_DurationInMillisecond = 0;
        m_bIsPeriodic = false;
        m_StartTimestampInMillisecond = -1;
        m_bIsStarted = false;
    }

private:
    TaskID m_TaskId;
    int64_t m_DurationInMillisecond;
    bool m_bIsPeriodic;
    int64_t m_StartTimestampInMillisecond;
    bool m_bIsStarted;

    friend class TimerTaskController;
};
#endif // _TIMERTASK_H_H