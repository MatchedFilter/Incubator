#include "Incubator/Logger/Logger.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include <cinttypes>
#include <cstring>
#include <cstdarg>
#include <cstdio>

extern "C"
{
    void _transmit_log_buffer(uint8_t *buffer, int32_t size);
}

#ifdef DEBUG
void LOG_DEBUG(const char *format, ...)
{
    constexpr int32_t MAX_LOG_SIZE = 256;
    constexpr int32_t TIME_STAMP_SIZE = 10;
    constexpr int32_t END_LINE_CHAR_SIZE = 1;
    constexpr int32_t BUFFER_LOG_SIZE = MAX_LOG_SIZE + TIME_STAMP_SIZE + END_LINE_CHAR_SIZE;
    static char buffer[BUFFER_LOG_SIZE];

    memset(buffer, 0, sizeof(buffer));
    uint32_t timestampInMilliseconds = TimeUtils::GetTimestampInMilliseconds();
    
    sprintf(buffer, "%09u:", (unsigned int)timestampInMilliseconds);
    
    va_list args;
    va_start(args, format);
    vsprintf(&buffer[TIME_STAMP_SIZE], format, args);
    va_end(args);

    size_t logSize = strlen(buffer);
    buffer[logSize] = '\n';
    logSize++;
    _transmit_log_buffer((uint8_t*) buffer, logSize);

}
#else // RELEASE
void LOG_DEBUG(const char *data, ...) {}
#endif // DEBUG
