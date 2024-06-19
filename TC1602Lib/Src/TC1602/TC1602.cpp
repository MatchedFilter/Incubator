#include "TC1602/TC1602.h"
#include <cinttypes>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include "TC1602/TC1602Dependencies.h"

using namespace GUI;

constexpr int32_t HIGH = 1;
constexpr int32_t LOW = 0;

static void Send(bool bIsCommand, uint8_t data)
{
    constexpr int32_t ENABLE_LOW_TO_HIGH_TIME_DURATION_IN_MICROSECONDS = 20;
    constexpr int32_t NEXT_DATA_TIME_DURATION_IN_MICROSECONDS = 200;
    constexpr int32_t COMMAND_PROCESS_TIME_DURATION_IN_MILLISECOND = 3;
    constexpr int32_t DATA_PROCESS_TIME_DURATION_IN_MILLISECOND = 1;

    _set_d4_pin_output((data & 0b00010000) != 0);
    _set_d5_pin_output((data & 0b00100000) != 0);
    _set_d6_pin_output((data & 0b01000000) != 0);
    _set_d7_pin_output((data & 0b10000000) != 0);
    if (bIsCommand)
    {
        _set_reset_pin_output(LOW);
    }
    else
    {
        _set_reset_pin_output(HIGH);
    }
    _set_rw_pin_output(LOW);
    _set_en_pin_output(HIGH);
    _delay_in_microseconds(ENABLE_LOW_TO_HIGH_TIME_DURATION_IN_MICROSECONDS);
    _set_en_pin_output(LOW);
    _delay_in_microseconds(NEXT_DATA_TIME_DURATION_IN_MICROSECONDS);
    _set_d4_pin_output((data & 0b0001) != 0);
    _set_d5_pin_output((data & 0b0010) != 0);
    _set_d6_pin_output((data & 0b0100) != 0);
    _set_d7_pin_output((data & 0b1000) != 0);
    _set_en_pin_output(HIGH);
    _delay_in_microseconds(ENABLE_LOW_TO_HIGH_TIME_DURATION_IN_MICROSECONDS);
    _set_en_pin_output(LOW);
    if (bIsCommand)
    {
        _delay_in_milliseconds(COMMAND_PROCESS_TIME_DURATION_IN_MILLISECOND);
    }
    else
    {
        _delay_in_milliseconds(DATA_PROCESS_TIME_DURATION_IN_MILLISECOND);
    }
}


void TC1602::Initialize()
{
    constexpr int32_t _2LINES_4_BIT_MODE_CMD = 0x28;
    constexpr int32_t DISPLAY_ON_CURSOR_OFF_CMD = 0x0C;
    constexpr int32_t AUTO_CURSOR_SHIFT_TO_RIGHT_CMD = 0x06;
    Send(true, _2LINES_4_BIT_MODE_CMD);
    Send(true, DISPLAY_ON_CURSOR_OFF_CMD);
    Send(true, AUTO_CURSOR_SHIFT_TO_RIGHT_CMD);
    ClearScreen();
    SetCursorToLine(TC1602_LINE_COUNT_1);
}

void TC1602::ClearScreen()
{
    constexpr int32_t CLEAR_SCREEN_CMD = 0x01;
    Send(true, CLEAR_SCREEN_CMD);
}

void TC1602::ChangeColor(EnumTC1602Color tc1602Color)
{
}

void TC1602::Print(const char *format, ...)
{
    constexpr int32_t BUFFER_SIZE = 16 * 2  + sizeof('\0');
    static char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE - sizeof('\0'), format, args);
    va_end(args);

    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (buffer[i] == '\0')
        {
            break;
        }
        Send(false, (uint8_t)buffer[i]);
    }
}

void TC1602::SetCursorToLine(EnumTC1602LineCount lineCount)
{
    constexpr int32_t FORCE_TO_LINE_1_CMD = 0x80;
    constexpr int32_t FORCE_TO_LINE_2_CMD = 0xC0;
    switch (lineCount)
    {
    case TC1602_LINE_COUNT_1:
        Send(true, FORCE_TO_LINE_1_CMD);
        break;

    case TC1602_LINE_COUNT_2:
        Send(true, FORCE_TO_LINE_2_CMD);
        break;
        
    default:
        break;
    }
}
