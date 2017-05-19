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

const long seconds_per_minute = 60;
const long minutes_per_hour = 60;
const long hours_per_day = 24;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;
const long milliseconds_per_hour = milliseconds_per_second*seconds_per_minute*minutes_per_hour;
const long milliseconds_per_day = milliseconds_per_hour*hours_per_day;
const long seconds_per_hour = seconds_per_minute*minutes_per_hour;
const long seconds_per_day = seconds_per_hour*hours_per_day;

CONSTANT_STRING(year_string,"year");
CONSTANT_STRING(month_string,"month");
CONSTANT_STRING(day_string,"day");
CONSTANT_STRING(hour_string,"hour");
CONSTANT_STRING(minute_string,"minute");
CONSTANT_STRING(second_string,"second");

const double camera_trigger_duty_cycle = 50.0;
const double camera_trigger_duty_cycle_max = 100.0;

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
CONSTANT_STRING(red_light_pulsing_string,"red_light_pulsing");
CONSTANT_STRING(buzzing_string,"buzzing");
CONSTANT_STRING(testing_string,"testing");

// Interrupts

// Units
CONSTANT_STRING(hz_units,"Hz");
CONSTANT_STRING(seconds_units,"s");
CONSTANT_STRING(hours_units,"hours");
CONSTANT_STRING(days_units,"days");
CONSTANT_STRING(military_time_hours_units,"military_time_hours");

// Properties
CONSTANT_STRING(camera_trigger_channel_property_name,"cameraTriggerChannel");

CONSTANT_STRING(camera_trigger_frequency_property_name,"cameraTriggerFrequency");
const double camera_trigger_frequency_min = 0.01;
const double camera_trigger_frequency_max = 100;
const double camera_trigger_frequency_default = 0.5;

CONSTANT_STRING(white_light_channel_property_name,"whiteLightChannel");

CONSTANT_STRING(white_light_indicator_channel_property_name,"whiteLightIndicatorChannel");

CONSTANT_STRING(white_light_power_property_name,"whiteLightPower");
const long white_light_power_min = 10;
const long white_light_power_max = 100;
const long white_light_power_default = 50;

CONSTANT_STRING(white_light_start_time_property_name,"whiteLightStartTime");
const long white_light_start_time_min = 4;
const long white_light_start_time_max = 12;
const long white_light_start_time_default = 9;

CONSTANT_STRING(white_light_on_duration_property_name,"whiteLightOnDuration");
const long white_light_on_duration_min = 1;
const long white_light_on_duration_max = 23;
const long white_light_on_duration_default = 12;

CONSTANT_STRING(red_light_channel_property_name,"redLightChannel");

CONSTANT_STRING(red_light_indicator_channel_property_name,"redLightIndicatorChannel");

CONSTANT_STRING(red_light_power_property_name,"redLightPower");
const long red_light_power_min = 10;
const long red_light_power_max = 100;
const long red_light_power_default = 50;

CONSTANT_STRING(red_light_frequency_property_name,"redLightFrequency");
const long red_light_frequency_min = 1;
const long red_light_frequency_max = 100;
const long red_light_frequency_default = 10;

CONSTANT_STRING(red_light_duty_cycle_property_name,"redLightDutyCycle");
const long red_light_duty_cycle_min = 0;
const long red_light_duty_cycle_max = 100;
const long red_light_duty_cycle_default = 50;

CONSTANT_STRING(buzzer_channel_property_name,"buzzerChannel");

CONSTANT_STRING(buzzer_power_property_name,"buzzerPower");
const long buzzer_power_min = 10;
const long buzzer_power_max = 100;
const long buzzer_power_default = 50;

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

CONSTANT_STRING(time_zone_offset_property_name,"timeZoneOffset");
const long time_zone_offset_min = -12;
const long time_zone_offset_max = 14;
const long time_zone_offset_default = -4;

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
CONSTANT_STRING(epoch_time_parameter_name,"epoch_time");
const long epoch_time_min = 1490000000;
const long epoch_time_max = 2147483647;

CONSTANT_STRING(adjust_time_parameter_name,"adjust_time");

CONSTANT_STRING(experiment_day_parameter_name,"experiment_day");

CONSTANT_STRING(white_light_parameter_name,"white_light");

CONSTANT_STRING(red_light_parameter_name,"red_light");

CONSTANT_STRING(red_light_delay_parameter_name,"red_light_delay");
const double red_light_delay_min = 0.0;
const double red_light_delay_max = 24.0;

CONSTANT_STRING(red_light_duration_parameter_name,"red_light_duration");
const double red_light_duration_min = 0.0;
const double red_light_duration_max = 24.0;

CONSTANT_STRING(buzzer_parameter_name,"buzzer");

CONSTANT_STRING(buzzer_delay_parameter_name,"buzzer_delay");
const double buzzer_delay_min = 0.0;
const double buzzer_delay_max = 24.0;

CONSTANT_STRING(buzzer_duration_parameter_name,"buzzer_duration");
const double buzzer_duration_min = 0.0;
const double buzzer_duration_max = 24.0;

CONSTANT_STRING(day_count_parameter_name,"day_count");

// Functions
CONSTANT_STRING(set_time_function_name,"setTime");
CONSTANT_STRING(get_time_function_name,"getTime");
CONSTANT_STRING(adjust_time_function_name,"adjustTime");
CONSTANT_STRING(now_function_name,"now");
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
CONSTANT_STRING(set_experiment_day_white_light_function_name,"setExperimentDayWhiteLight");
CONSTANT_STRING(set_experiment_day_red_light_function_name,"setExperimentDayRedLight");
CONSTANT_STRING(set_experiment_day_buzzer_function_name,"setExperimentDayBuzzer");
CONSTANT_STRING(get_assay_status_function_name,"getAssayStatus");
CONSTANT_STRING(test_white_light_power_function_name,"testWhiteLightPower");
CONSTANT_STRING(test_red_light_power_function_name,"testRedLightPower");
CONSTANT_STRING(test_buzzer_power_function_name,"testBuzzerPower");
CONSTANT_STRING(stop_all_power_tests_function_name,"stopAllPowerTests");

// Callbacks
CONSTANT_STRING(run_assay_callback_name,"runAssay");
CONSTANT_STRING(test_assay_callback_name,"testAssay");
CONSTANT_STRING(stop_assay_callback_name,"stopAssay");

// Errors
CONSTANT_STRING(time_not_set_error,"Time is not set! Must use setTime method. To get epoch time manually, you can visit https://www.epochconverter.com/ or use bash: date +%s");
CONSTANT_STRING(assay_not_started_error,"Assay not started!");
CONSTANT_STRING(experiment_day_does_not_exist_error,"Experiment day does not exist!");

}
}
