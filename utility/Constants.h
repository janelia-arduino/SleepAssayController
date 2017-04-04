// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SLEEP_ASSAY_CONTROLLER_CONSTANTS_H
#define SLEEP_ASSAY_CONTROLLER_CONSTANTS_H
#include "ConstantVariable.h"
#include "HighPowerSwitchController.h"


namespace sleep_assay_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=19};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=5};
enum{CALLBACK_COUNT_MAX=2};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const long channel_min;
extern const long channel_max;

extern const long seconds_per_minute;
extern const long minutes_per_hour;
extern const long hours_per_day;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;
extern const long milliseconds_per_hour;
extern const long milliseconds_per_day;

extern ConstantString year_string;
extern ConstantString month_string;
extern ConstantString day_string;
extern ConstantString hour_string;
extern ConstantString minute_string;
extern ConstantString second_string;

extern const double camera_trigger_duty_cycle;
extern const double camera_trigger_duty_cycle_max;

// Interrupts

// Units
extern ConstantString hz_unit;
extern ConstantString seconds_unit;
extern ConstantString hours_unit;
extern ConstantString days_unit;
extern ConstantString military_time_hours_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString camera_trigger_channel_property_name;
extern const long camera_trigger_channel_default;

extern ConstantString camera_trigger_frequency_property_name;
extern const double camera_trigger_frequency_min;
extern const double camera_trigger_frequency_max;
extern const double camera_trigger_frequency_default;

extern ConstantString white_light_channel_property_name;
extern const long white_light_channel_default;

extern ConstantString white_light_power_property_name;
extern const long white_light_power_min;
extern const long white_light_power_max;
extern const long white_light_power_default;

extern ConstantString white_light_start_time_property_name;
extern const long white_light_start_time_min;
extern const long white_light_start_time_max;
extern const long white_light_start_time_default;

extern ConstantString white_light_on_duration_property_name;
extern const long white_light_on_duration_min;
extern const long white_light_on_duration_max;
extern const long white_light_on_duration_default;

extern ConstantString red_light_channel_property_name;
extern const long red_light_channel_default;

extern ConstantString red_light_power_property_name;
extern const long red_light_power_min;
extern const long red_light_power_max;
extern const long red_light_power_default;

extern ConstantString red_light_frequency_property_name;
extern const long red_light_frequency_min;
extern const long red_light_frequency_max;
extern const long red_light_frequency_default;

extern ConstantString red_light_duty_cycle_property_name;
extern const long red_light_duty_cycle_min;
extern const long red_light_duty_cycle_max;
extern const long red_light_duty_cycle_default;

extern ConstantString buzzer_channel_property_name;
extern const long buzzer_channel_default;

extern ConstantString buzzer_power_property_name;
extern const long buzzer_power_min;
extern const long buzzer_power_max;
extern const long buzzer_power_default;

extern ConstantString buzzer_on_duration_property_name;
extern const long buzzer_on_duration_min;
extern const long buzzer_on_duration_max;
extern const long buzzer_on_duration_default;

extern ConstantString buzzer_wait_min_property_name;
extern const long buzzer_wait_min_min;
extern const long buzzer_wait_min_max;
extern const long buzzer_wait_min_default;

extern ConstantString buzzer_wait_max_property_name;
extern const long buzzer_wait_max_min;
extern const long buzzer_wait_max_max;
extern const long buzzer_wait_max_default;

extern ConstantString time_zone_offset_property_name;
extern const long time_zone_offset_min;
extern const long time_zone_offset_max;
extern const long time_zone_offset_default;

extern ConstantString entrainment_duration_property_name;
extern const long entrainment_duration_min;
extern const long entrainment_duration_max;
extern const long entrainment_duration_default;

extern ConstantString recovery_duration_property_name;
extern const long recovery_duration_min;
extern const long recovery_duration_max;
extern const long recovery_duration_default;

extern ConstantString testing_day_duration_property_name;
extern const long testing_day_duration_min;
extern const long testing_day_duration_max;
extern const long testing_day_duration_default;

// Parameters
extern ConstantString epoch_time_parameter_name;

// Functions
extern ConstantString set_epoch_time_function_name;
extern ConstantString get_epoch_time_function_name;
extern ConstantString get_date_time_now_function_name;
extern ConstantString get_date_time_assay_start_function_name;
extern ConstantString get_date_time_assay_end_function_name;

// Callbacks
extern ConstantString run_assay_callback_name;
extern ConstantString test_assay_callback_name;

// Errors
extern ConstantString time_not_set_error;
extern ConstantString assay_not_started_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
