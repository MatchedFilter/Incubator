#ifndef _GUI_IUIDEVICE_H_
#define _GUI_IUIDEVICE_H_
#include "Incubator/IncubatorData.h"
namespace GUI
{
    class IUIDevice
    {
    public:
        virtual ~IUIDevice() = default;
        virtual void Initialize() = 0;
        virtual void Update(IncubatorData &incubatorData) = 0;
    };
} // namespace GUI

#endif // _GUI_IUIDEVICE_H_