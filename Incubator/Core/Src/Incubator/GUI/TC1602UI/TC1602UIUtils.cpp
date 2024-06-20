#include "Incubator/GUI/TC1602UI/TC1602UIUtils.h"

using namespace GUI;


void TC1602UIUtils::PrintTemperatureStringWithoutInitialLetter(TC1602 *tc1602)
{
    tc1602->Print(TC1602_CHAR_LOWER_I);
    tc1602->Print("cakl");
    tc1602->Print(TC1602_CHAR_LOWER_I);
    tc1602->Print("k");
}
