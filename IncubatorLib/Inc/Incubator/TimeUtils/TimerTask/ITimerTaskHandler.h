#ifndef _ITIMERTASKHANDLER_H_
#define _ITIMERTASKHANDLER_H_
#include "TimerTaskDefinitions.h"
class ITimerTaskHandler
{
public:
    virtual ~ITimerTaskHandler() = default;
    virtual void OnTimeout(TaskID taskId) = 0;
};
#endif // _ITIMERTASKHANDLER_H_