#ifndef _GUI_TC1602_H_
#define _GUI_TC1602_H_
#include <cinttypes>
namespace GUI
{
    enum EnumTC1602LineCount : uint8_t
    {
        TC1602_LINE_COUNT_1,
        TC1602_LINE_COUNT_2
    };

    constexpr const uint8_t TC1602_CHAR_LOWER_I = 0x00;
    constexpr const uint8_t TC1602_CHAR_LOWER_U = 0x01;
    constexpr const uint8_t TC1602_CHAR_LOWER_O = 0x02;
    constexpr const uint8_t TC1602_CHAR_LOWER_G = 0x03;
    constexpr const uint8_t TC1602_CHAR_DEGREE_SYMBOL = 0xDF;
    constexpr const uint8_t TC1602_CHAR_ARROW_SYMBOL = 0x7E;

    class TC1602
    {
    public:
        TC1602() = default;
        ~TC1602() = default;
        void Initialize();
        void ClearScreen();
        void Print(const char *format, ...);
        void Print(uint8_t ch);
        void DisplayOff();
        void DisplayOn();
        void SetCursorToLine(EnumTC1602LineCount lineCount);
    };
} // namespace GUI

#endif // _GUI_TC1602_H_
