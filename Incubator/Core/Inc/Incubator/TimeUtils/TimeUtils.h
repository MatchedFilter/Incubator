#ifndef _TIMEUTILS_H_
#define _TIMEUTILS_H_
#include <cinttypes>
class TimeUtils
{
public:
    static uint32_t GetTimestampInMilliseconds();
    static void SleepInMilliseconds(uint32_t timeInMilliseconds);
};
#endif // _TIMEUTILS_H_