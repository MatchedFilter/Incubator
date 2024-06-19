#ifndef _GUI_TC1602_H_
#define _GUI_TC1602_H_
#include <cinttypes>
namespace GUI
{
    enum EnumTC1602Color : uint8_t
    {
        TC1602_COLOR_BLACK_OVER_WHITE,
        TC1602_COLOR_WHITE_OVER_BLACK
    };

    enum EnumTC1602LineCount : uint8_t
    {
        TC1602_LINE_COUNT_1,
        TC1602_LINE_COUNT_2
    };  

    class TC1602
    {
    public:
        TC1602() = default;
        ~TC1602() = default;
        void Initialize();
        void ClearScreen();
        void ChangeColor(EnumTC1602Color tc1602Color);
        void Print(const char *format, ...);
        void SetCursorToLine(EnumTC1602LineCount lineCount);

    };
} // namespace GUI

#endif // _GUI_TC1602_H_
