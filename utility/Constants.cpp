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

CONSTANT_STRING(year_string,"year");
CONSTANT_STRING(month_string,"month");
CONSTANT_STRING(day_string,"day");
CONSTANT_STRING(hour_string,"hour");
CONSTANT_STRING(minute_string,"minute");
CONSTANT_STRING(second_string,"second");

// Interrupts

// Units
CONSTANT_STRING(hz_unit,"Hz");
CONSTANT_STRING(seconds_unit,"s");
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

CONSTANT_STRING(time_zone_offset_property_name,"timeZoneOffset");
const long time_zone_offset_min = -12;
const long time_zone_offset_max = 14;
const long time_zone_offset_default = -4;

// Parameters
CONSTANT_STRING(epoch_time_parameter_name,"epoch_time");

// Functions
CONSTANT_STRING(set_epoch_time_function_name,"setEpochTime");
CONSTANT_STRING(get_epoch_time_function_name,"getEpochTime");
CONSTANT_STRING(get_date_time_function_name,"getDateTime");
CONSTANT_STRING(run_experiment_function_name,"runExperiment");

// Callbacks

// Errors
CONSTANT_STRING(time_not_set_error,"Time is not set! Must use setEpochTime method. To get epoch time using bash: date +%s");

}
}
