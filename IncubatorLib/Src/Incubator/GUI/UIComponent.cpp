#include "Incubator/GUI/UIComponent.h"

using namespace GUI;

UIComponent::UIComponent(const char* incubatorVersion) : 
#ifdef TC1602_LCD_USED
    m_TC1602UIDevice { incubatorVersion }
#endif // TC1602_LCD_USED
{
#ifdef TC1602_LCD_USED
    m_Device = &m_TC1602UIDevice;
#endif // TC1602_LCD_USED
}

void UIComponent::Initialize()
{
    m_Device->Initialize();
}

void UIComponent::Update(IncubatorData &incubatorData)
{
    m_Device->Update(incubatorData);
}
