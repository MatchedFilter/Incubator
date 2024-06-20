#ifndef _TIMEUTILS_H_
#define _TIMEUTILS_H_
#include <cinttypes>
class TimeUtils
{
public:
    static int64_t GetTimestampInMilliseconds();
    static void SetTimestampInMilliseconds(int64_t timestampInMilliseconds);
    static void SleepInMilliseconds(uint32_t timeInMilliseconds);
};
#endif // _TIMEUTILS_H_