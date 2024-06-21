#ifndef _IncubatorStorageUpdatingTimerTaskHandler_H_
#define _IncubatorStorageUpdatingTimerTaskHandler_H_
#include "Incubator/TimeUtils/TimerTask/ITimerTaskHandler.h"
#include "Incubator/IncubatorData.h"
class IncubatorStorageUpdatingTimerTaskHandler : public ITimerTaskHandler
{
public:
    IncubatorStorageUpdatingTimerTaskHandler(IncubatorData *incubatorData);
    ~IncubatorStorageUpdatingTimerTaskHandler() = default;
    virtual void OnTimeout(TaskID taskId) override;

private:
    IncubatorData *m_IncubatorData;

};
#endif // _IncubatorStorageUpdatingTimerTaskHandler_H_