// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace sleep_assay_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"sleep_assay_controller");

CONSTANT_STRING(firmware_name,"SleepAssayController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

const long channel_min = 0;
const long channel_max = high_power_switch_controller::constants::CHANNEL_COUNT;

const long milliseconds_per_second = 1000;
const long seconds_per_minute = 60;
const long minutes_per_hour = 60;
const long hours_per_day = 24;
const long milliseconds_per_hour = milliseconds_per_second*seconds_per_minute*minutes_per_hour;
const long milliseconds_per_day = milliseconds_per_second*hours_per_day;

// Interrupts

// Units
CONSTANT_STRING(hz_unit,"Hz");
CONSTANT_STRING(hours_unit,"hours");
CONSTANT_STRING(days_unit,"days");

// Properties
CONSTANT_STRING(camera_trigger_channel_property_name,"cameraTriggerChannel");

CONSTANT_STRING(white_light_channel_property_name,"whiteLightChannel");

CONSTANT_STRING(red_light_channel_property_name,"redLightChannel");

CONSTANT_STRING(camera_trigger_frequency_property_name,"cameraTriggerFrequency");
const double camera_trigger_frequency_min = 0.01;
const double camera_trigger_frequency_max = 100;
const double camera_trigger_frequency_default = 0.5;

// Parameters

// Functions
CONSTANT_STRING(run_experiment_function_name,"runExperiment");

// Callbacks

// Errors
}
}
