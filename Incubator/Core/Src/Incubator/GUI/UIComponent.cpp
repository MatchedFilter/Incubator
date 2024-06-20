#include "Incubator/GUI/UIComponent.h"

using namespace GUI;

UIComponent::UIComponent()
{
// #ifdef TC1602_USED
    m_Device = &m_TC1602UIDevice;
// #endif // TC1602_USED
}

void UIComponent::Initialize()
{
    m_Device->Initialize();
}

void UIComponent::Update(IncubatorData &incubatorData)
{
    m_Device->Update(incubatorData);
}
