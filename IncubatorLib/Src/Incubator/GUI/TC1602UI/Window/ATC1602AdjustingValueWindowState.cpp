#include "Incubator/GUI/TC1602UI/Window/ATC1602AdjustingValueWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/TimeUtils/TimeUtils.h"

using namespace GUI;

ATC1602AdjustingValueWindowState::ATC1602AdjustingValueWindowState(EnumTC1602WindowState windowState, EnumTC1602WindowState previousState, TC1602 *tc1602)
    : ATC1602WindowState{windowState, tc1602},
        m_PreviousState { previousState },
        m_IncubatorData { nullptr },
        m_bIsInitial { true }, m_ScrollPosition { 0 }, m_Value { 0 },
        m_bIsInSaveScreen { false } { }


void ATC1602AdjustingValueWindowState::PrintAreChangesSavedQuestion()
{
    LOG_DEBUG("Kaydedilsin mi?");
    m_Tc1602->Print("Kaydedilsin mi?");
}

void ATC1602AdjustingValueWindowState::PrintYesNo()
{
    switch (m_ScrollPosition)
    {
    case 0:
        m_Tc1602->Print("[Hay");
        m_Tc1602->Print(TC1602_CHAR_LOWER_I);
        m_Tc1602->Print("r]    Evet ");
        LOG_DEBUG("[Hayır]    Evet ");
        break;

    case 1:
        m_Tc1602->Print(" Hay");
        m_Tc1602->Print(TC1602_CHAR_LOWER_I);
        m_Tc1602->Print("r    [Evet]");
        LOG_DEBUG(" Hayır    [Evet]");
        break;
    
    default:
        break;
    }
}

void ATC1602AdjustingValueWindowState::UpdateScrollPosition()
{
    if (m_ScrollPosition < MAX_SCROLL_POSITION && m_IncubatorData->m_bIsButtonRight)
    {
        m_ScrollPosition++;
        InterruptedRefresh();
    }
    else if (m_ScrollPosition > 0 && m_IncubatorData->m_bIsButtonLeft)
    {
        m_ScrollPosition--;
        InterruptedRefresh();
    }
    else
    {
    }
}

void ATC1602AdjustingValueWindowState::UpdateValue()
{
    if (m_IncubatorData->m_bIsButtonRight)
    {
        m_Value += 10;
        InterruptedRefresh();
    }
    else if (m_IncubatorData->m_bIsButtonLeft)
    {
        m_Value -= 10;
        InterruptedRefresh();
    }
    else if (m_IncubatorData->m_bIsButtonUp)
    {
        m_Value += 1;
        InterruptedRefresh();
    }
    else if (m_IncubatorData->m_bIsButtonDown)
    {
        m_Value -= 1;
        InterruptedRefresh();
    }
    else
    {

    }
}

void ATC1602AdjustingValueWindowState::DetermineNextState()
{
    if (m_IncubatorData->m_bIsButtonClicked == true)
    {
        if (m_bIsInSaveScreen)
        {
            if (m_ScrollPosition == 1)
            {
                WriteChanges();
            }
            m_NextWindowState = m_PreviousState;
            m_bIsInitial = true;
            m_bIsInSaveScreen = false;
        }
        else
        {
            m_bIsInitial = true;
            m_bIsInSaveScreen = true;
            m_ScrollPosition = 0;
        }
    }
}


void ATC1602AdjustingValueWindowState::Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = m_CurrentWindowState;
    if (m_bIsInitial)
    {
        if (!m_bIsInSaveScreen)
        {
            m_Value = GetInitialValue();
        }
        InterruptedRefresh();
        m_bIsInitial = false;
    }
    if (m_bIsInSaveScreen)
    {
        UpdateScrollPosition();
    }
    else
    {
        UpdateValue();
    }
    DetermineNextState();
}

void ATC1602AdjustingValueWindowState::Refresh()
{
}

void ATC1602AdjustingValueWindowState::InterruptedRefresh()
{
    if (m_IncubatorData != nullptr)
    {
        m_Tc1602->ClearScreen();
        if (m_bIsInSaveScreen)
        {
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
            PrintAreChangesSavedQuestion();
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
            PrintYesNo();
        }
        else
        {
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
            PrintCurrentValue();
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
            PrintAdjustingValue();
        }
    }
}

EnumTC1602WindowState ATC1602AdjustingValueWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
