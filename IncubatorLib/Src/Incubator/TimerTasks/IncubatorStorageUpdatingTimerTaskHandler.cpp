#include "Incubator/TimerTasks/IncubatorStorageUpdatingTimerTaskHandler.h"
#include "Incubator/Utils/IncubatorUtils.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/Storage/Storage.h"

IncubatorStorageUpdatingTimerTaskHandler::IncubatorStorageUpdatingTimerTaskHandler(IncubatorData *incubatorData) :
    m_IncubatorData { incubatorData }
{
}

void IncubatorStorageUpdatingTimerTaskHandler::OnTimeout(TaskID taskId)
{
    TimeInfoData timeInfoData;
    if (Storage::Query(timeInfoData))
    {
        TimeUtils::SleepInMilliseconds(1);
        timeInfoData.m_IncubatorCurrentTimestampInSeconds = static_cast<uint32_t>(TimeUtils::GetTimestampInMilliseconds() / 1000);
        Storage::Write(timeInfoData);
        TimeUtils::SleepInMilliseconds(1);
    }
}
