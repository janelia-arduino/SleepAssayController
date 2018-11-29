// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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
  .version_major=2,
  .version_minor=0,
  .version_patch=0,
};

const double fan_power = 100.0;
const double indicator_power = 100.0;
const double camera_trigger_power = 100.0;
const double camera_trigger_duty_cycle = 50.0;

CONSTANT_STRING(time_now_string,"time_now");
CONSTANT_STRING(time_entrainment_start_string,"time_entrainment_start");
CONSTANT_STRING(time_assay_start_string,"time_assay_start");
CONSTANT_STRING(time_experiment_start_string,"time_experiment_start");
CONSTANT_STRING(time_experiment_end_string,"time_experiment_end");
CONSTANT_STRING(time_assay_end_string,"time_assay_end");
CONSTANT_STRING(date_time_now_string,"date_time_now");
CONSTANT_STRING(assay_day_string,"assay_day");
CONSTANT_STRING(phase_string,"phase");
CONSTANT_STRING(phase_day_string,"phase_day");
CONSTANT_STRING(phase_assay_not_started_string,"ASSAY_NOT_STARTED");
CONSTANT_STRING(phase_entrainment_string,"ENTRAINMENT");
CONSTANT_STRING(phase_experiment_string,"EXPERIMENT");
CONSTANT_STRING(phase_recovery_string,"RECOVERY");
CONSTANT_STRING(phase_assay_finished_string,"ASSAY_FINISHED");
CONSTANT_STRING(white_light_on_string,"white_light_on");
CONSTANT_STRING(visible_backlight_pulsing_string,"visible_backlight_pulsing");
CONSTANT_STRING(buzzing_possible_string,"buzzing_possible");
CONSTANT_STRING(buzzing_string,"buzzing");
CONSTANT_STRING(testing_string,"testing");
CONSTANT_STRING(visible_backlight_intensity_string,"visible_backlight_intensity");
CONSTANT_STRING(white_light_power_string,"white_light_power");
CONSTANT_STRING(buzzer_power_string,"buzzer_power");

// Pins

// Units
CONSTANT_STRING(hz_units,"Hz");
CONSTANT_STRING(hours_units,"hours");
CONSTANT_STRING(days_units,"days");
CONSTANT_STRING(military_time_hours_units,"military_time_hours");

// Properties
CONSTANT_STRING(visible_backlight_frequency_property_name,"visibleBacklightFrequency");
const double visible_backlight_frequency_min = 0.01;
const double visible_backlight_frequency_max = 100;
const double visible_backlight_frequency_default = 10;

CONSTANT_STRING(visible_backlight_duty_cycle_property_name,"visibleBacklightDutyCycle");
const long visible_backlight_duty_cycle_min = 0;
const long visible_backlight_duty_cycle_max = 100;
const long visible_backlight_duty_cycle_default = 50;

CONSTANT_STRING(white_light_start_time_property_name,"whiteLightStartTime");
const long white_light_start_time_min = 4;
const long white_light_start_time_max = 12;
const long white_light_start_time_default = 9;

CONSTANT_STRING(white_light_on_duration_property_name,"whiteLightOnDuration");
const long white_light_on_duration_min = 1;
const long white_light_on_duration_max = 23;
const long white_light_on_duration_default = 12;

CONSTANT_STRING(buzzer_on_duration_min_property_name,"buzzerOnDurationMin");
const long buzzer_on_duration_min = 1;
const long buzzer_on_duration_max = 10;
const long buzzer_on_duration_min_default = 1;

CONSTANT_STRING(buzzer_on_duration_max_property_name,"buzzerOnDurationMax");
const long buzzer_on_duration_max_default = 4;

CONSTANT_STRING(buzzer_wait_min_property_name,"buzzerWaitMin");
const long buzzer_wait_min_min = 1;
const long buzzer_wait_min_max = 60;
const long buzzer_wait_min_default = 1;

CONSTANT_STRING(buzzer_wait_max_property_name,"buzzerWaitMax");
const long buzzer_wait_max_min = 1;
const long buzzer_wait_max_max = 3600;
const long buzzer_wait_max_default = 3;

CONSTANT_STRING(camera_trigger_frequency_property_name,"cameraTriggerFrequency");
const double camera_trigger_frequency_min = 0.01;
const double camera_trigger_frequency_max = 100;
const double camera_trigger_frequency_default = 0.5;

CONSTANT_STRING(entrainment_duration_property_name,"entrainmentDuration");
const long entrainment_duration_min = 1;
const long entrainment_duration_max = 10;
const long entrainment_duration_default = 2;

CONSTANT_STRING(recovery_duration_property_name,"recoveryDuration");
const long recovery_duration_min = 0;
const long recovery_duration_max = 10;
const long recovery_duration_default = 2;

CONSTANT_STRING(testing_day_duration_property_name,"testingDayDuration");
const long testing_day_duration_min = 1;
const long testing_day_duration_max = 240;
const long testing_day_duration_default = 24;

// Parameters
CONSTANT_STRING(experiment_day_parameter_name,"experiment_day");

CONSTANT_STRING(visible_backlight_delay_parameter_name,"visible_backlight_delay");
const double visible_backlight_delay_min = 0.0;
const double visible_backlight_delay_max = 24.0;

CONSTANT_STRING(visible_backlight_duration_parameter_name,"visible_backlight_duration");
const double visible_backlight_duration_min = 0.0;
const double visible_backlight_duration_max = 24.0;

CONSTANT_STRING(buzzer_delay_parameter_name,"buzzer_delay");
const double buzzer_delay_min = 0.0;
const double buzzer_delay_max = 24.0;

CONSTANT_STRING(buzzer_duration_parameter_name,"buzzer_duration");
const double buzzer_duration_min = 0.0;
const double buzzer_duration_max = 24.0;

CONSTANT_STRING(day_count_parameter_name,"day_count");

// Functions
CONSTANT_STRING(set_ir_backlight_and_fan_on_at_power_function_name,"setIrBacklightAndFanOnAtPower");
CONSTANT_STRING(set_ir_backlight_and_fan_on_at_intensity_function_name,"setIrBacklightAndFanOnAtIntensity");
CONSTANT_STRING(set_visible_backlight_and_indicator_on_at_power_function_name,"setVisibleBacklightAndIndicatorOnAtPower");
CONSTANT_STRING(set_visible_backlight_and_indicator_on_at_intensity_function_name,"setVisibleBacklightAndIndicatorOnAtIntensity");
CONSTANT_STRING(set_white_light_and_indicator_on_at_power_function_name,"setWhiteLightAndIndicatorOnAtPower");
CONSTANT_STRING(set_buzzer_and_indicator_on_at_power_function_name,"setBuzzerAndIndicatorOnAtPower");

CONSTANT_STRING(get_assay_start_function_name,"getAssayStart");
CONSTANT_STRING(get_assay_end_function_name,"getAssayEnd");
CONSTANT_STRING(get_assay_duration_function_name,"getAssayDuration");
CONSTANT_STRING(get_experiment_start_function_name,"getExperimentStart");
CONSTANT_STRING(get_experiment_end_function_name,"getExperimentEnd");
CONSTANT_STRING(get_experiment_duration_function_name,"getExperimentDuration");
CONSTANT_STRING(get_entrainment_start_function_name,"getEntrainmentStart");
CONSTANT_STRING(get_experiment_info_function_name,"getExperimentInfo");
CONSTANT_STRING(get_experiment_day_info_function_name,"getExperimentDayInfo");
CONSTANT_STRING(add_experiment_day_function_name,"addExperimentDay");
CONSTANT_STRING(add_experiment_days_function_name,"addExperimentDays");
CONSTANT_STRING(add_experiment_day_copy_function_name,"addExperimentDayCopy");
CONSTANT_STRING(add_experiment_day_copies_function_name,"addExperimentDayCopies");
CONSTANT_STRING(remove_last_experiment_day_function_name,"removeLastExperimentDay");
CONSTANT_STRING(remove_all_experiment_days_function_name,"removeAllExperimentDays");
CONSTANT_STRING(set_experiment_day_visible_backlight_function_name,"setExperimentDayVisibleBacklight");
CONSTANT_STRING(set_experiment_day_white_light_function_name,"setExperimentDayWhiteLight");
CONSTANT_STRING(set_experiment_day_buzzer_function_name,"setExperimentDayBuzzer");
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");

// Callbacks
CONSTANT_STRING(set_ir_backlight_and_fan_on_callback_name,"setIrBacklightAndFanOn");
CONSTANT_STRING(set_ir_backlight_and_fan_off_callback_name,"setIrBacklightAndFanOff");
CONSTANT_STRING(toggle_ir_backlight_and_fan_callback_name,"toggleIrBacklightAndFan");
CONSTANT_STRING(set_visible_backlight_and_indicator_on_callback_name,"setVisibleBacklightAndIndicatorOn");
CONSTANT_STRING(set_visible_backlight_and_indicator_off_callback_name,"setVisibleBacklightAndIndicatorOff");
CONSTANT_STRING(toggle_visible_backlight_and_indicator_callback_name,"toggleVisibleBacklightAndIndicator");
CONSTANT_STRING(set_white_light_and_indicator_on_callback_name,"setWhiteLightAndIndicatorOn");
CONSTANT_STRING(set_white_light_and_indicator_off_callback_name,"setWhiteLightAndIndicatorOff");
CONSTANT_STRING(toggle_white_light_and_indicator_callback_name,"toggleWhiteLightAndIndicator");
CONSTANT_STRING(set_buzzer_and_indicator_on_callback_name,"setBuzzerAndIndicatorOn");
CONSTANT_STRING(set_buzzer_and_indicator_off_callback_name,"setBuzzerAndIndicatorOff");
CONSTANT_STRING(toggle_buzzer_and_indicator_callback_name,"toggleBuzzerAndIndicator");
CONSTANT_STRING(start_camera_trigger_callback_name,"startCameraTrigger");
CONSTANT_STRING(stop_camera_trigger_callback_name,"stopCameraTrigger");

CONSTANT_STRING(run_assay_callback_name,"runAssay");
CONSTANT_STRING(test_assay_callback_name,"testAssay");
CONSTANT_STRING(stop_assay_callback_name,"stopAssay");

// Errors
CONSTANT_STRING(assay_not_started_error,"Assay not started!");
CONSTANT_STRING(experiment_day_does_not_exist_error,"Experiment day does not exist!");

}
}
