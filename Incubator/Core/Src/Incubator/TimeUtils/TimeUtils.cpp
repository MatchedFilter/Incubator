#include "Incubator/TimeUtils/TimeUtils.h"

extern "C"
{
    uint32_t _get_timestamp_in_milliseconds();
    void _sleep_in_millisecond(int32_t timeInMillisecond);
}

uint32_t TimeUtils::GetTimestampInMilliseconds()
{
    return _get_timestamp_in_milliseconds();
}

void TimeUtils::SleepInMilliseconds(uint32_t timeInMilliseconds)
{
    _sleep_in_millisecond(timeInMilliseconds);
}
