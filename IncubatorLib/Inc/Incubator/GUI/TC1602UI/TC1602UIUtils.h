#ifndef _GUI_TC1602UIUTILS_H_
#define _GUI_TC1602UIUTILS_H_
#include "TC1602/TC1602.h"
namespace GUI
{
    class TC1602UIUtils
    {
    public:
        static void PrintTemperatureStringWithoutInitialLetter(TC1602 *tc1602);
    };
} // namespace GUI

#endif // _GUI_TC1602UIUTILS_H_