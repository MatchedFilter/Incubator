#ifndef _IC_INCUBATORCONTROLLER_H_
#define _IC_INCUBATORCONTROLLER_H_
namespace IC
{
    class IncubatorController
    {
    public:
        IncubatorController() = default;
        ~IncubatorController() = default;
        void TurnOnHeater();
        void TurnOffHeater();
        void TurnOnHumidityGenerator();
        void TurnOffHumidityGenerator();
    };
} // namespace IC

#endif // _IC_INCUBATORCONTROLLER_H_