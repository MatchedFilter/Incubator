#ifndef _TIMERTASKCONTROLLER_H_
#define _TIMERTASKCONTROLLER_H_
#include "ITimerTaskHandler.h"
class TimerTaskController
{
public:
    static TaskID RegisterTask(ITimerTaskHandler *taskHandler, int64_t durationInMilliseconds, bool m_bIsPeriodic = false);
    static void StartTask(TaskID taskID);
    static void StopTask(TaskID taskID);
    static void DeleteTask(TaskID taskID);
    static void Run();
    
};
#endif // _TIMERTASKCONTROLLER_H_