#include "Incubator/TimeUtils/TimeUtils.h"

extern "C"
{
    int64_t _get_timestamp_in_milliseconds();
    void _delay_in_milliseconds(int32_t timeInMillisecond);
    void _set_timestamp_in_milliseconds(int64_t timestampInMilliseconds);

}

int64_t TimeUtils::GetTimestampInMilliseconds()
{
    return _get_timestamp_in_milliseconds();
}

void TimeUtils::SetTimestampInMilliseconds(int64_t timestampInMilliseconds)
{
    _set_timestamp_in_milliseconds(timestampInMilliseconds);
}


void TimeUtils::SleepInMilliseconds(uint32_t timeInMilliseconds)
{
    _delay_in_milliseconds(timeInMilliseconds);
}
