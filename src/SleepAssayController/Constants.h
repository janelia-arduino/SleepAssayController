// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SLEEP_ASSAY_CONTROLLER_CONSTANTS_H
#define SLEEP_ASSAY_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <BacklightController.h>


namespace sleep_assay_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=12};
enum{PARAMETER_COUNT_MAX=6};
enum{FUNCTION_COUNT_MAX=25};
enum{CALLBACK_COUNT_MAX=17};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const double fan_power;
extern const double indicator_power;
extern const double camera_trigger_power;
extern const double camera_trigger_duty_cycle;

struct ExperimentDayInfo
{
  double visible_backlight_intensity;
  double visible_backlight_delay_hours;
  double visible_backlight_duration_hours;
  double white_light_power;
  double buzzer_power;
  double buzzer_delay_hours;
  double buzzer_duration_hours;
};

struct AssayStatus
{
  time_t time;
  double assay_day;
  const ConstantString * phase_ptr;
  double phase_day;
  bool white_light_on;
  bool visible_backlight_pulsing;
  bool buzzing_possible;
  bool buzzing;
  bool testing;
};

extern ConstantString time_now_string;
extern ConstantString time_entrainment_start_string;
extern ConstantString time_assay_start_string;
extern ConstantString time_experiment_start_string;
extern ConstantString time_experiment_end_string;
extern ConstantString time_assay_end_string;
extern ConstantString date_time_now_string;
extern ConstantString assay_day_string;
extern ConstantString phase_string;
extern ConstantString phase_day_string;
extern ConstantString phase_assay_not_started_string;
extern ConstantString phase_entrainment_string;
extern ConstantString phase_experiment_string;
extern ConstantString phase_recovery_string;
extern ConstantString phase_assay_finished_string;
extern ConstantString white_light_on_string;
extern ConstantString visible_backlight_pulsing_string;
extern ConstantString buzzing_possible_string;
extern ConstantString buzzing_string;
extern ConstantString testing_string;
extern ConstantString visible_backlight_intensity_string;
extern ConstantString white_light_power_string;
extern ConstantString buzzer_power_string;

// Pins

// Units
extern ConstantString hz_units;
extern ConstantString hours_units;
extern ConstantString days_units;
extern ConstantString military_time_hours_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString visible_backlight_frequency_property_name;
extern const double visible_backlight_frequency_min;
extern const double visible_backlight_frequency_max;
extern const double visible_backlight_frequency_default;

extern ConstantString visible_backlight_duty_cycle_property_name;
extern const long visible_backlight_duty_cycle_min;
extern const long visible_backlight_duty_cycle_max;
extern const long visible_backlight_duty_cycle_default;

extern ConstantString white_light_start_time_property_name;
extern const long white_light_start_time_min;
extern const long white_light_start_time_max;
extern const long white_light_start_time_default;

extern ConstantString white_light_on_duration_property_name;
extern const long white_light_on_duration_min;
extern const long white_light_on_duration_max;
extern const long white_light_on_duration_default;

extern ConstantString buzzer_on_duration_min_property_name;
extern const long buzzer_on_duration_min;
extern const long buzzer_on_duration_max;
extern const long buzzer_on_duration_min_default;

extern ConstantString buzzer_on_duration_max_property_name;
extern const long buzzer_on_duration_max_default;

extern ConstantString buzzer_wait_min_property_name;
extern const long buzzer_wait_min_min;
extern const long buzzer_wait_min_max;
extern const long buzzer_wait_min_default;

extern ConstantString buzzer_wait_max_property_name;
extern const long buzzer_wait_max_min;
extern const long buzzer_wait_max_max;
extern const long buzzer_wait_max_default;

extern ConstantString camera_trigger_frequency_property_name;
extern const double camera_trigger_frequency_min;
extern const double camera_trigger_frequency_max;
extern const double camera_trigger_frequency_default;

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
extern ConstantString experiment_day_parameter_name;

extern ConstantString visible_backlight_delay_parameter_name;
extern const double visible_backlight_delay_min;
extern const double visible_backlight_delay_max;

extern ConstantString visible_backlight_duration_parameter_name;
extern const double visible_backlight_duration_min;
extern const double visible_backlight_duration_max;

extern ConstantString buzzer_delay_parameter_name;
extern const double buzzer_delay_min;
extern const double buzzer_delay_max;

extern ConstantString buzzer_duration_parameter_name;
extern const double buzzer_duration_min;
extern const double buzzer_duration_max;

extern ConstantString day_count_parameter_name;

// Functions
extern ConstantString set_ir_backlight_and_fan_on_at_power_function_name;
extern ConstantString set_ir_backlight_and_fan_on_at_intensity_function_name;
extern ConstantString set_visible_backlight_and_indicator_on_at_power_function_name;
extern ConstantString set_visible_backlight_and_indicator_on_at_intensity_function_name;
extern ConstantString set_white_light_and_indicator_on_at_power_function_name;
extern ConstantString set_buzzer_and_indicator_on_at_power_function_name;

extern ConstantString get_assay_start_function_name;
extern ConstantString get_assay_end_function_name;
extern ConstantString get_assay_duration_function_name;
extern ConstantString get_experiment_start_function_name;
extern ConstantString get_experiment_end_function_name;
extern ConstantString get_experiment_duration_function_name;
extern ConstantString get_entrainment_start_function_name;
extern ConstantString get_experiment_info_function_name;
extern ConstantString get_experiment_day_info_function_name;
extern ConstantString add_experiment_day_function_name;
extern ConstantString add_experiment_days_function_name;
extern ConstantString add_experiment_day_copy_function_name;
extern ConstantString add_experiment_day_copies_function_name;
extern ConstantString remove_last_experiment_day_function_name;
extern ConstantString remove_all_experiment_days_function_name;
extern ConstantString set_experiment_day_visible_backlight_function_name;
extern ConstantString set_experiment_day_white_light_function_name;
extern ConstantString set_experiment_day_buzzer_function_name;
extern ConstantString get_assay_status_function_name;

// Callbacks
extern ConstantString set_ir_backlight_and_fan_on_callback_name;
extern ConstantString set_ir_backlight_and_fan_off_callback_name;
extern ConstantString toggle_ir_backlight_and_fan_callback_name;
extern ConstantString set_visible_backlight_and_indicator_on_callback_name;
extern ConstantString set_visible_backlight_and_indicator_off_callback_name;
extern ConstantString toggle_visible_backlight_and_indicator_callback_name;
extern ConstantString set_white_light_and_indicator_on_callback_name;
extern ConstantString set_white_light_and_indicator_off_callback_name;
extern ConstantString toggle_white_light_and_indicator_callback_name;
extern ConstantString set_buzzer_and_indicator_on_callback_name;
extern ConstantString set_buzzer_and_indicator_off_callback_name;
extern ConstantString toggle_buzzer_and_indicator_callback_name;
extern ConstantString start_camera_trigger_callback_name;
extern ConstantString stop_camera_trigger_callback_name;

extern ConstantString run_assay_callback_name;
extern ConstantString test_assay_callback_name;
extern ConstantString stop_assay_callback_name;

// Errors
extern ConstantString assay_not_started_error;
extern ConstantString experiment_day_does_not_exist_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
