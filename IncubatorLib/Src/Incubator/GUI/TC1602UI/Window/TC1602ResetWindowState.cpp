#include "Incubator/GUI/TC1602UI/Window/TC1602ResetWindowState.h"
#include "Incubator/Logger/Logger.h"
#include "Incubator/Storage/Storage.h"
#include "Incubator/Utils/IncubatorUtils.h"
#include "Incubator/TimeUtils/TimeUtils.h"
#include "Incubator/TimeUtils/TimerTask/TimerTaskController.h"

using namespace GUI;

TC1602ResetWindowState::TC1602ResetWindowState(TC1602 *tc1602, TC1602MenuWindowState *menuWindowState)
    : ATC1602WindowState{TC1602_WINDOW_STATE_RESET, tc1602}, m_ScrollPosition { 0 },
        m_IncubatorData { nullptr }, m_bIsInitial { true }, m_MenuWindowState { menuWindowState} { }


void TC1602ResetWindowState::PrintResetQuestion()
{
    LOG_DEBUG("Sıfırlansın mı?");
    m_Tc1602->Print('S');
    m_Tc1602->Print(TC1602_CHAR_LOWER_I);
    m_Tc1602->Print('f');
    m_Tc1602->Print(TC1602_CHAR_LOWER_I);
    m_Tc1602->Print("rlans");
    m_Tc1602->Print(TC1602_CHAR_LOWER_I);
    m_Tc1602->Print("n m");
    m_Tc1602->Print(TC1602_CHAR_LOWER_I);
    m_Tc1602->Print('?');
}

void TC1602ResetWindowState::PrintSelectLine()
{
    if (m_ScrollPosition == 1)
    {
        m_Tc1602->Print(" Hay");
        m_Tc1602->Print(TC1602_CHAR_LOWER_I);
        m_Tc1602->Print("r    [Evet]");
        LOG_DEBUG(" Hayır    [Evet]");
    }
    else
    {
        m_Tc1602->Print("[Hay");
        m_Tc1602->Print(TC1602_CHAR_LOWER_I);
        m_Tc1602->Print("r]    Evet ");
        LOG_DEBUG("[Hayır]    Evet ");
    }
}

void TC1602ResetWindowState::UpdateScrollPosition()
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

void TC1602ResetWindowState::DetermineNextState()
{
    if (m_IncubatorData->m_bIsButtonClicked == true)
    {
        switch (m_ScrollPosition)
        {
        case 0:
            m_NextWindowState = TC1602_WINDOW_STATE_MENU_WINDOW;
            break;
        case 1:
            Storage::Reset();
            TimeUtils::SleepInMilliseconds(1);
            TimeUtils::SetTimestampInMilliseconds(0);
            Storage::Initialize();
            TimeUtils::SleepInMilliseconds(3);
            m_Tc1602->ClearScreen();
            m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
            m_Tc1602->Print("Bekleyiniz");
            IncubatorUtils::ReadStorageData(*m_IncubatorData);
            TimeUtils::SleepInMilliseconds(100);
            TimerTaskController::ResetAllTasks();
            m_MenuWindowState->m_ScrollPosition = 0;
            m_NextWindowState = TC1602_WINDOW_STATE_MAIN_WINDOW;
            break;

        default:
            break;
        }
        m_ScrollPosition = 0;
        m_bIsInitial = true;
    }
}

void TC1602ResetWindowState::Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState)
{
    m_IncubatorData = &incubatorData;
    m_NextWindowState = TC1602_WINDOW_STATE_RESET;
    if (m_bIsInitial)
    {
        InterruptedRefresh();
        m_bIsInitial = false;
    }
    UpdateScrollPosition();
    DetermineNextState();
}

void TC1602ResetWindowState::Refresh()
{
}

void TC1602ResetWindowState::InterruptedRefresh()
{
    if (m_IncubatorData != nullptr)
    {
        m_Tc1602->ClearScreen();
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_1);
        PrintResetQuestion();
        m_Tc1602->SetCursorToLine(TC1602_LINE_COUNT_2);
        PrintSelectLine();
    }
}

EnumTC1602WindowState TC1602ResetWindowState::GetNextWindowState()
{
    return m_NextWindowState;
}
