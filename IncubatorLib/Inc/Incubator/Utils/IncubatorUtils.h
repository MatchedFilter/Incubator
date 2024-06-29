#ifndef _INCUBATORUTILS_H_
#define _INCUBATORUTILS_H_
#include "Incubator/IncubatorData.h"
class IncubatorUtils
{
public:
    static void ReadStorageData(IncubatorData &incubatorData);
    static bool IsInMotorsOffTime(const IncubatorData &incubatorData);
};
#endif // _INCUBATORUTILS_H_