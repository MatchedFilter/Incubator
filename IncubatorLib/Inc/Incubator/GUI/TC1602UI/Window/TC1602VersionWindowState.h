#ifndef _GUI_TC1602VERSIONWINDOWSTATE_H_
#define _GUI_TC1602VERSIONWINDOWSTATE_H_
#include "ATC1602WindowState.h"

extern const char *INCUBATOR_VERSION;

namespace GUI
{
    class TC1602VersionWindowState : public ATC1602WindowState
    {
    public:
        TC1602VersionWindowState(TC1602 *tc1602, const char *incubatorVersion);
        ~TC1602VersionWindowState() = default;
        virtual void Update(IncubatorData &incubatorData, EnumTC1602WindowState previousState) override;
        virtual void Refresh() override;
        virtual EnumTC1602WindowState GetNextWindowState() override;

    private:
        const char *m_IncubatorSoftwareVersion;
        IncubatorData *m_IncubatorData;
        bool m_bIsInitial;

    private:
        void DetermineNextState();
        void InterruptedRefresh();
    };
} // namespace GUI

#endif // _GUI_TC1602VERSIONWINDOWSTATE_H_