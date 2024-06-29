#include "IncubatorController/IncubatorController.h"
#include "IncubatorController/IncubatorControllerDependencies.h"

using namespace IC;

void IncubatorController::TurnOnHeater()
{
    _set_heater_pin_as_high();
}

void IncubatorController::TurnOffHeater()
{
    _set_heater_pin_as_low();
}

void IncubatorController::TurnOnHumidityGenerator()
{
    _set_humidity_generator_pin_as_high();
}

void IncubatorController::TurnOffHumidityGenerator()
{
    _set_humidity_generator_pin_as_low();
}