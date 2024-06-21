#ifndef _GUI_TC1602REFRESHINGTIMERTASKHANDLER_H_
#define _GUI_TC1602REFRESHINGTIMERTASKHANDLER_H_
#include "Incubator/TimeUtils/TimerTask/ITimerTaskHandler.h"
#include "DHT11/DHT11.h"
#include "Incubator/IncubatorData.h"
#include "Incubator/GUI/TC1602UI/Window/ATC1602WindowState.h"
namespace GUI
{
    class TC1602RefreshingTimerTaskHandler : public ITimerTaskHandler
    {
    public:
        TC1602RefreshingTimerTaskHandler(ATC1602WindowState **currentState);
        ~TC1602RefreshingTimerTaskHandler() = default;
        virtual void OnTimeout(TaskID taskId) override;

    private:
        ATC1602WindowState **m_CurrentState;

    };
} // namespace GUI
#endif // _GUI_TC1602REFRESHINGTIMERTASKHANDLER_H_