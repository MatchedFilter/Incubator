#ifndef _GUI_UICOMPONENT_H_
#define _GUI_UICOMPONENT_H_
// #ifdef TC1602_USED
#include "TC1602UI/TC1602UIDevice.h"
// #endif // TC1602_USED
namespace GUI
{
    class UIComponent
    {
    public:
        UIComponent(const char* incubatorVersion);
        ~UIComponent() = default;
        void Initialize();
        void Update(IncubatorData &incubatorData);

    private:
        IUIDevice *m_Device;
// #ifdef TC1602_USED
        TC1602UIDevice m_TC1602UIDevice;
// #endif // TC1602_USED
        
    };
} // namespace GUI

#endif // _GUI_UICOMPONENT_H_