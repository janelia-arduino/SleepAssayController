// ----------------------------------------------------------------------------
// SleepAssayController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "SleepAssayController.h"


using namespace sleep_assay_controller;

SleepAssayController::SleepAssayController()
{
}

void SleepAssayController::setup()
{
  // Parent Setup
  HighPowerSwitchController::setup();

  // Variable Setup
  stopAssay();

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & camera_trigger_channel_property = modular_server_.createProperty(constants::camera_trigger_channel_property_name,constants::camera_trigger_channel_default);
  camera_trigger_channel_property.setRange(constants::channel_min,constants::channel_max);

  modular_server::Property & camera_trigger_frequency_property = modular_server_.createProperty(constants::camera_trigger_frequency_property_name,constants::camera_trigger_frequency_default);
  camera_trigger_frequency_property.setRange(constants::camera_trigger_frequency_min,constants::camera_trigger_frequency_max);
  camera_trigger_frequency_property.setUnits(constants::hz_unit);

  modular_server::Property & white_light_channel_property = modular_server_.createProperty(constants::white_light_channel_property_name,constants::white_light_channel_default);
  white_light_channel_property.setRange(constants::channel_min,constants::channel_max);
  white_light_channel_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::updatePowersHandler));

  modular_server::Property & white_light_power_property = modular_server_.createProperty(constants::white_light_power_property_name,constants::white_light_power_default);
  white_light_power_property.setRange(constants::white_light_power_min,constants::white_light_power_max);
  white_light_power_property.setUnits(high_power_switch_controller::constants::percent_unit);
  white_light_power_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::updatePowersHandler));

  modular_server::Property & white_light_start_time_property = modular_server_.createProperty(constants::white_light_start_time_property_name,constants::white_light_start_time_default);
  white_light_start_time_property.setRange(constants::white_light_start_time_min,constants::white_light_start_time_max);
  white_light_start_time_property.setUnits(constants::military_time_hours_unit);

  modular_server::Property & white_light_on_duration_property = modular_server_.createProperty(constants::white_light_on_duration_property_name,constants::white_light_on_duration_default);
  white_light_on_duration_property.setRange(constants::white_light_on_duration_min,constants::white_light_on_duration_max);
  white_light_on_duration_property.setUnits(constants::hours_unit);

  modular_server::Property & red_light_channel_property = modular_server_.createProperty(constants::red_light_channel_property_name,constants::red_light_channel_default);
  red_light_channel_property.setRange(constants::channel_min,constants::channel_max);
  red_light_channel_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::updatePowersHandler));

  modular_server::Property & red_light_power_property = modular_server_.createProperty(constants::red_light_power_property_name,constants::red_light_power_default);
  red_light_power_property.setRange(constants::red_light_power_min,constants::red_light_power_max);
  red_light_power_property.setUnits(high_power_switch_controller::constants::percent_unit);
  red_light_power_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::updatePowersHandler));

  modular_server::Property & red_light_frequency_property = modular_server_.createProperty(constants::red_light_frequency_property_name,constants::red_light_frequency_default);
  red_light_frequency_property.setRange(constants::red_light_frequency_min,constants::red_light_frequency_max);
  red_light_frequency_property.setUnits(constants::hz_unit);

  modular_server::Property & red_light_duty_cycle_property = modular_server_.createProperty(constants::red_light_duty_cycle_property_name,constants::red_light_duty_cycle_default);
  red_light_duty_cycle_property.setRange(constants::red_light_duty_cycle_min,constants::red_light_duty_cycle_max);
  red_light_duty_cycle_property.setUnits(high_power_switch_controller::constants::percent_unit);

  modular_server::Property & buzzer_channel_property = modular_server_.createProperty(constants::buzzer_channel_property_name,constants::buzzer_channel_default);
  buzzer_channel_property.setRange(constants::channel_min,constants::channel_max);
  buzzer_channel_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::updatePowersHandler));

  modular_server::Property & buzzer_power_property = modular_server_.createProperty(constants::buzzer_power_property_name,constants::buzzer_power_default);
  buzzer_power_property.setRange(constants::buzzer_power_min,constants::buzzer_power_max);
  buzzer_power_property.setUnits(high_power_switch_controller::constants::percent_unit);
  buzzer_power_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::updatePowersHandler));

  modular_server::Property & buzzer_on_duration_property = modular_server_.createProperty(constants::buzzer_on_duration_property_name,constants::buzzer_on_duration_default);
  buzzer_on_duration_property.setRange(constants::buzzer_on_duration_min,constants::buzzer_on_duration_max);
  buzzer_on_duration_property.setUnits(constants::seconds_unit);

  modular_server::Property & buzzer_wait_min_property = modular_server_.createProperty(constants::buzzer_wait_min_property_name,constants::buzzer_wait_min_default);
  buzzer_wait_min_property.setRange(constants::buzzer_wait_min_min,constants::buzzer_wait_min_max);
  buzzer_wait_min_property.setUnits(constants::seconds_unit);

  modular_server::Property & buzzer_wait_max_property = modular_server_.createProperty(constants::buzzer_wait_max_property_name,constants::buzzer_wait_max_default);
  buzzer_wait_max_property.setRange(constants::buzzer_wait_max_min,constants::buzzer_wait_max_max);
  buzzer_wait_max_property.setUnits(constants::seconds_unit);

  modular_server::Property & time_zone_offset_property = modular_server_.createProperty(constants::time_zone_offset_property_name,constants::time_zone_offset_default);
  time_zone_offset_property.setRange(constants::time_zone_offset_min,constants::time_zone_offset_max);

  modular_server::Property & entrainment_duration_property = modular_server_.createProperty(constants::entrainment_duration_property_name,constants::entrainment_duration_default);
  entrainment_duration_property.setRange(constants::entrainment_duration_min,constants::entrainment_duration_max);
  entrainment_duration_property.setUnits(constants::days_unit);

  modular_server::Property & recovery_duration_property = modular_server_.createProperty(constants::recovery_duration_property_name,constants::recovery_duration_default);
  recovery_duration_property.setRange(constants::recovery_duration_min,constants::recovery_duration_max);
  recovery_duration_property.setUnits(constants::days_unit);

  modular_server::Property & testing_day_duration_property = modular_server_.createProperty(constants::testing_day_duration_property_name,constants::testing_day_duration_default);
  testing_day_duration_property.setRange(constants::testing_day_duration_min,constants::testing_day_duration_max);
  testing_day_duration_property.setUnits(constants::seconds_unit);

  updatePowersHandler();

  // Parameters
  modular_server::Parameter & epoch_time_parameter = modular_server_.createParameter(constants::epoch_time_parameter_name);
  epoch_time_parameter.setRange(constants::epoch_time_min,constants::epoch_time_max);
  epoch_time_parameter.setUnits(constants::seconds_unit);

  modular_server::Parameter & adjust_time_parameter = modular_server_.createParameter(constants::adjust_time_parameter_name);
  adjust_time_parameter.setTypeLong();
  adjust_time_parameter.setUnits(constants::seconds_unit);

  modular_server::Parameter & experiment_day_parameter = modular_server_.createParameter(constants::experiment_day_parameter_name);
  experiment_day_parameter.setTypeLong();
  experiment_day_parameter.setRange((long)0,(long)constants::EXPERIMENT_DAY_COUNT_MAX - 1);

  modular_server::Parameter & white_light_parameter = modular_server_.createParameter(constants::white_light_parameter_name);
  white_light_parameter.setTypeBool();

  modular_server::Parameter & red_light_parameter = modular_server_.createParameter(constants::red_light_parameter_name);
  red_light_parameter.setTypeBool();

  modular_server::Parameter & red_light_delay_parameter = modular_server_.createParameter(constants::red_light_delay_parameter_name);
  red_light_delay_parameter.setRange(constants::red_light_delay_min,constants::red_light_delay_max);
  red_light_delay_parameter.setUnits(constants::hours_unit);

  modular_server::Parameter & red_light_duration_parameter = modular_server_.createParameter(constants::red_light_duration_parameter_name);
  red_light_duration_parameter.setRange(constants::red_light_duration_min,constants::red_light_duration_max);
  red_light_duration_parameter.setUnits(constants::hours_unit);

  modular_server::Parameter & buzzer_parameter = modular_server_.createParameter(constants::buzzer_parameter_name);
  buzzer_parameter.setTypeBool();

  modular_server::Parameter & buzzer_delay_parameter = modular_server_.createParameter(constants::buzzer_delay_parameter_name);
  buzzer_delay_parameter.setRange(constants::buzzer_delay_min,constants::buzzer_delay_max);
  buzzer_delay_parameter.setUnits(constants::hours_unit);

  modular_server::Parameter & buzzer_duration_parameter = modular_server_.createParameter(constants::buzzer_duration_parameter_name);
  buzzer_duration_parameter.setRange(constants::buzzer_duration_min,constants::buzzer_duration_max);
  buzzer_duration_parameter.setUnits(constants::hours_unit);

  modular_server::Parameter & day_count_parameter = modular_server_.createParameter(constants::day_count_parameter_name);
  day_count_parameter.setRange((long)1,(long)constants::EXPERIMENT_DAY_COUNT_MAX);

  modular_server::Parameter & power_parameter = modular_server_.parameter(high_power_switch_controller::constants::power_parameter_name);

  // Functions
  modular_server::Function & set_time_function = modular_server_.createFunction(constants::set_time_function_name);
  set_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::setTimeHandler));
  set_time_function.addParameter(epoch_time_parameter);

  modular_server::Function & get_time_function = modular_server_.createFunction(constants::get_time_function_name);
  get_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getTimeHandler));
  get_time_function.setReturnTypeLong();

  modular_server::Function & adjust_time_function = modular_server_.createFunction(constants::adjust_time_function_name);
  adjust_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::adjustTimeHandler));
  adjust_time_function.addParameter(adjust_time_parameter);

  modular_server::Function & now_function = modular_server_.createFunction(constants::now_function_name);
  now_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::nowHandler));
  now_function.setReturnTypeObject();

  modular_server::Function & get_assay_start_function = modular_server_.createFunction(constants::get_assay_start_function_name);
  get_assay_start_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getAssayStartHandler));
  get_assay_start_function.setReturnTypeObject();

  modular_server::Function & get_assay_end_function = modular_server_.createFunction(constants::get_assay_end_function_name);
  get_assay_end_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getAssayEndHandler));
  get_assay_end_function.setReturnTypeObject();

  modular_server::Function & get_assay_duration_function = modular_server_.createFunction(constants::get_assay_duration_function_name);
  get_assay_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getAssayDurationHandler));
  get_assay_duration_function.setReturnTypeLong();

  modular_server::Function & get_experiment_start_function = modular_server_.createFunction(constants::get_experiment_start_function_name);
  get_experiment_start_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getExperimentStartHandler));
  get_experiment_start_function.setReturnTypeObject();

  modular_server::Function & get_experiment_end_function = modular_server_.createFunction(constants::get_experiment_end_function_name);
  get_experiment_end_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getExperimentEndHandler));
  get_experiment_end_function.setReturnTypeObject();

  modular_server::Function & get_experiment_duration_function = modular_server_.createFunction(constants::get_experiment_duration_function_name);
  get_experiment_duration_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getExperimentDurationHandler));
  get_experiment_duration_function.setReturnTypeLong();

  modular_server::Function & get_entrainment_start_function = modular_server_.createFunction(constants::get_entrainment_start_function_name);
  get_entrainment_start_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getEntrainmentStartHandler));
  get_entrainment_start_function.setReturnTypeObject();

  modular_server::Function & get_experiment_info_function = modular_server_.createFunction(constants::get_experiment_info_function_name);
  get_experiment_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getExperimentInfoHandler));
  get_experiment_info_function.setReturnTypeArray();

  modular_server::Function & get_experiment_day_info_function = modular_server_.createFunction(constants::get_experiment_day_info_function_name);
  get_experiment_day_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getExperimentDayInfoHandler));
  get_experiment_day_info_function.addParameter(experiment_day_parameter);
  get_experiment_day_info_function.setReturnTypeObject();

  modular_server::Function & add_experiment_day_function = modular_server_.createFunction(constants::add_experiment_day_function_name);
  add_experiment_day_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::addExperimentDayHandler));
  add_experiment_day_function.setReturnTypeLong();

  modular_server::Function & add_experiment_days_function = modular_server_.createFunction(constants::add_experiment_days_function_name);
  add_experiment_days_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::addExperimentDaysHandler));
  add_experiment_days_function.addParameter(day_count_parameter);
  add_experiment_days_function.setReturnTypeArray();

  modular_server::Function & add_experiment_day_copy_function = modular_server_.createFunction(constants::add_experiment_day_copy_function_name);
  add_experiment_day_copy_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::addExperimentDayCopyHandler));
  add_experiment_day_copy_function.addParameter(experiment_day_parameter);
  add_experiment_day_copy_function.setReturnTypeLong();

  modular_server::Function & add_experiment_day_copies_function = modular_server_.createFunction(constants::add_experiment_day_copies_function_name);
  add_experiment_day_copies_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::addExperimentDayCopiesHandler));
  add_experiment_day_copies_function.addParameter(experiment_day_parameter);
  add_experiment_day_copies_function.addParameter(day_count_parameter);
  add_experiment_day_copies_function.setReturnTypeArray();

  modular_server::Function & remove_last_experiment_day_function = modular_server_.createFunction(constants::remove_last_experiment_day_function_name);
  remove_last_experiment_day_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::removeLastExperimentDayHandler));

  modular_server::Function & remove_all_experiment_days_function = modular_server_.createFunction(constants::remove_all_experiment_days_function_name);
  remove_all_experiment_days_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::removeAllExperimentDaysHandler));

  modular_server::Function & set_experiment_day_white_light_function = modular_server_.createFunction(constants::set_experiment_day_white_light_function_name);
  set_experiment_day_white_light_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::setExperimentDayWhiteLightHandler));
  set_experiment_day_white_light_function.addParameter(experiment_day_parameter);
  set_experiment_day_white_light_function.addParameter(white_light_parameter);
  set_experiment_day_white_light_function.setReturnTypeObject();

  modular_server::Function & set_experiment_day_red_light_function = modular_server_.createFunction(constants::set_experiment_day_red_light_function_name);
  set_experiment_day_red_light_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::setExperimentDayRedLightHandler));
  set_experiment_day_red_light_function.addParameter(experiment_day_parameter);
  set_experiment_day_red_light_function.addParameter(red_light_parameter);
  set_experiment_day_red_light_function.addParameter(red_light_delay_parameter);
  set_experiment_day_red_light_function.addParameter(red_light_duration_parameter);
  set_experiment_day_red_light_function.setReturnTypeObject();

  modular_server::Function & set_experiment_day_buzzer_function = modular_server_.createFunction(constants::set_experiment_day_buzzer_function_name);
  set_experiment_day_buzzer_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::setExperimentDayBuzzerHandler));
  set_experiment_day_buzzer_function.addParameter(experiment_day_parameter);
  set_experiment_day_buzzer_function.addParameter(buzzer_parameter);
  set_experiment_day_buzzer_function.addParameter(buzzer_delay_parameter);
  set_experiment_day_buzzer_function.addParameter(buzzer_duration_parameter);
  set_experiment_day_buzzer_function.setReturnTypeObject();

  modular_server::Function & get_assay_status_function = modular_server_.createFunction(constants::get_assay_status_function_name);
  get_assay_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getAssayStatusHandler));
  get_assay_status_function.setReturnTypeObject();

  modular_server::Function & test_white_light_power_function = modular_server_.createFunction(constants::test_white_light_power_function_name);
  test_white_light_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::testWhiteLightPowerHandler));
  test_white_light_power_function.addParameter(power_parameter);

  modular_server::Function & test_red_light_power_function = modular_server_.createFunction(constants::test_red_light_power_function_name);
  test_red_light_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::testRedLightPowerHandler));
  test_red_light_power_function.addParameter(power_parameter);

  modular_server::Function & test_buzzer_power_function = modular_server_.createFunction(constants::test_buzzer_power_function_name);
  test_buzzer_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::testBuzzerPowerHandler));
  test_buzzer_power_function.addParameter(power_parameter);

  modular_server::Function & stop_all_power_tests_function = modular_server_.createFunction(constants::stop_all_power_tests_function_name);
  stop_all_power_tests_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::stopAllPowerTestsHandler));

  // Callbacks
  modular_server::Callback & run_assay_callback = modular_server_.createCallback(constants::run_assay_callback_name);
  run_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&SleepAssayController::runAssayHandler));

  modular_server::Callback & test_assay_callback = modular_server_.createCallback(constants::test_assay_callback_name);
  test_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&SleepAssayController::testAssayHandler));

  modular_server::Callback & stop_assay_callback = modular_server_.createCallback(constants::stop_assay_callback_name);
  stop_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&SleepAssayController::stopAssayHandler));

}

void SleepAssayController::setTime(const time_t epoch_time)
{
  ::setTime(epoch_time);
}

time_t SleepAssayController::getTime()
{
  return ::now();
}

void SleepAssayController::adjustTime(const long adjust_time)
{
  ::adjustTime(adjust_time);
}

bool SleepAssayController::timeIsSet()
{
  timeStatus_t time_status = timeStatus();
  return (time_status != timeNotSet);
}

time_t SleepAssayController::epochTimeToLocalTime(const time_t epoch_time)
{
  long time_zone_offset;
  modular_server_.property(constants::time_zone_offset_property_name).getValue(time_zone_offset);

  return epoch_time + time_zone_offset*constants::seconds_per_hour;
}


void SleepAssayController::runAssay()
{
  if (!timeIsSet() || (assayStarted() && !assayFinished()))
  {
    return;
  }
  testing_ = false;
  startAssay();
}

void SleepAssayController::testAssay()
{
  if (!timeIsSet() || (assayStarted() && !assayFinished()))
  {
    return;
  }
  testing_ = true;
  startAssay();
}

void SleepAssayController::stopAssay()
{
  stopAllPwm();
  setAllChannelsOff();

  assay_started_ = false;
  assay_finished_ = false;
  testing_ = false;

  time_assay_start_ = 0;
  time_experiment_start_ = 0;

  buzzer_enabled_ = false;
  buzzing_ = false;
}

bool SleepAssayController::assayStarted()
{
  return assay_started_;
}

bool SleepAssayController::assayFinished()
{
  return assay_finished_;
}

bool SleepAssayController::testing()
{
  return testing_;
}

long SleepAssayController::scaleDuration(const long duration)
{
  if (testing())
  {
    long testing_day_duration;
    modular_server_.property(constants::testing_day_duration_property_name).getValue(testing_day_duration);
    double scale_factor = (double)testing_day_duration/(double)constants::seconds_per_day;
    return (double)duration*scale_factor;
  }
  return duration;
}

time_t SleepAssayController::now()
{
  return ::now();
}

time_t SleepAssayController::getAssayStart()
{
  return time_assay_start_;
}

time_t SleepAssayController::getAssayEnd()
{
  if (!assayStarted())
  {
    return 0;
  }
  long recovery_duration;
  modular_server_.property(constants::recovery_duration_property_name).getValue(recovery_duration);

  time_t time_assay_end = getExperimentEnd();
  time_assay_end += scaleDuration(recovery_duration*constants::seconds_per_day);
  return time_assay_end;
}

uint8_t SleepAssayController::getAssayDuration()
{
  long entrainment_duration;
  modular_server_.property(constants::entrainment_duration_property_name).getValue(entrainment_duration);

  long recovery_duration;
  modular_server_.property(constants::recovery_duration_property_name).getValue(recovery_duration);

  uint8_t experiment_duration = getExperimentDuration();

  return entrainment_duration + experiment_duration + recovery_duration;
}

time_t SleepAssayController::getExperimentStart()
{
  return time_experiment_start_;
}

time_t SleepAssayController::getExperimentEnd()
{
  if (!assayStarted())
  {
    return 0;
  }
  time_t time_experiment_end = getExperimentStart();
  time_experiment_end += scaleDuration(experiment_day_array_.size()*constants::seconds_per_day);
  return time_experiment_end;
}

uint8_t SleepAssayController::getExperimentDuration()
{
  return experiment_day_array_.size();
}

time_t SleepAssayController::getEntrainmentStart()
{
  if (!assayStarted())
  {
    return 0;
  }

  long entrainment_duration;
  modular_server_.property(constants::entrainment_duration_property_name).getValue(entrainment_duration);

  time_t time_entrainment_start = getExperimentStart();
  time_entrainment_start -= scaleDuration(entrainment_duration*constants::seconds_per_day);

  return time_entrainment_start;
}

SleepAssayController::experiment_day_info_array_t SleepAssayController::getExperimentInfo()
{
  return experiment_day_array_;
}

size_t SleepAssayController::addExperimentDay()
{
  constants::ExperimentDayInfo experiment_day_info;
  experiment_day_info.white_light = true;
  experiment_day_info.red_light = false;
  experiment_day_info.red_light_delay_hours = 0.0;
  experiment_day_info.red_light_duration_hours = 0.0;
  experiment_day_info.buzzer = false;
  experiment_day_info.buzzer_delay_hours = 0.0;
  experiment_day_info.buzzer_duration_hours = 0.0;
  experiment_day_array_.push_back(experiment_day_info);
  size_t experiment_day = experiment_day_array_.size() - 1;
  return experiment_day;
}

SleepAssayController::experiment_day_array_t SleepAssayController::addExperimentDays(const size_t day_count)
{
  size_t days_to_be_added = day_count;
  size_t days_available = experiment_day_array_.max_size() - experiment_day_array_.size();
  if (day_count > days_available)
  {
    days_to_be_added = days_available;
  }
  experiment_day_array_t days_added;
  for (size_t day=0; day<days_to_be_added; ++day)
  {
    size_t day_added = addExperimentDay();
    days_added.push_back(day_added);
  }
  return days_added;
}

size_t SleepAssayController::addExperimentDayCopy(const size_t experiment_day)
{
  constants::ExperimentDayInfo experiment_day_info;
  if (experimentDayExists(experiment_day))
  {
    experiment_day_info = experiment_day_array_[experiment_day];
  }
  experiment_day_array_.push_back(experiment_day_info);
  return experiment_day_array_.size() - 1;
}

SleepAssayController::experiment_day_array_t SleepAssayController::addExperimentDayCopies(const size_t experiment_day,
                                                                                          const size_t day_count)
{
  size_t days_to_be_added = day_count;
  size_t days_available = experiment_day_array_.max_size() - experiment_day_array_.size();
  if (day_count > days_available)
  {
    days_to_be_added = days_available;
  }
  experiment_day_array_t days_added;
  for (size_t day=0; day<days_to_be_added; ++day)
  {
    size_t day_added = addExperimentDayCopy(experiment_day);
    days_added.push_back(day_added);
  }
  return days_added;
}

void SleepAssayController::removeLastExperimentDay()
{
  experiment_day_array_.pop_back();
}

void SleepAssayController::removeAllExperimentDays()
{
  experiment_day_array_.clear();
}

void SleepAssayController::setExperimentDayWhiteLight(const size_t experiment_day,
                                                      const bool white_light)
{
  if (!experimentDayExists(experiment_day))
  {
    return;
  }
  experiment_day_array_[experiment_day].white_light = white_light;
}

void SleepAssayController::setExperimentDayRedLight(const size_t experiment_day,
                                                    const bool red_light,
                                                    const double red_light_delay_hours,
                                                    const double red_light_duration_hours)
{
  if (!experimentDayExists(experiment_day))
  {
    return;
  }
  experiment_day_array_[experiment_day].red_light = red_light;
  experiment_day_array_[experiment_day].red_light_delay_hours = red_light_delay_hours;
  if ((red_light_duration_hours + red_light_delay_hours) < constants::red_light_duration_max)
  {
    experiment_day_array_[experiment_day].red_light_duration_hours = red_light_duration_hours;
  }
  else
  {
    experiment_day_array_[experiment_day].red_light_duration_hours = constants::red_light_duration_max - red_light_delay_hours;
  }
}

void SleepAssayController::setExperimentDayBuzzer(const size_t experiment_day,
                                                  const bool buzzer,
                                                  const double buzzer_delay_hours,
                                                  const double buzzer_duration_hours)
{
  if (!experimentDayExists(experiment_day))
  {
    return;
  }
  experiment_day_array_[experiment_day].buzzer = buzzer;
  experiment_day_array_[experiment_day].buzzer_delay_hours = buzzer_delay_hours;
  if ((buzzer_duration_hours + buzzer_delay_hours) < constants::buzzer_duration_max)
  {
    experiment_day_array_[experiment_day].buzzer_duration_hours = buzzer_duration_hours;
  }
  else
  {
    experiment_day_array_[experiment_day].buzzer_duration_hours = constants::buzzer_duration_max - buzzer_delay_hours;
  }
}

sleep_assay_controller::constants::AssayStatus SleepAssayController::getAssayStatus()
{
  constants::AssayStatus assay_status;
  time_t time_now = getTime();

  assay_status.time = time_now;
  assay_status.assay_day = -1;
  assay_status.phase_ptr = &constants::phase_assay_not_started_string;
  assay_status.phase_day = -1;
  assay_status.white_light_on = false;
  assay_status.red_light_pulsing = false;
  assay_status.buzzing = false;
  assay_status.testing = testing();

  if (assayStarted())
  {
    time_t time_entrainment_start = getEntrainmentStart();
    time_t time_assay_start = getAssayStart();
    time_t time_experiment_start = getExperimentStart();
    time_t time_experiment_end = getExperimentEnd();
    time_t time_assay_end = getAssayEnd();
    double seconds_per_day_scaled = scaleDuration(constants::seconds_per_day);

    assay_status.assay_day = (time_now - time_entrainment_start)/seconds_per_day_scaled;

    if (time_now < time_experiment_start)
    {
      assay_status.phase_ptr = &constants::phase_entrainment_string;
      assay_status.phase_day = (double)(time_now - time_entrainment_start)/seconds_per_day_scaled;
    }
    else if (time_now < time_experiment_end)
    {
      assay_status.phase_ptr = &constants::phase_experiment_string;
      assay_status.phase_day = (double)(time_now - time_experiment_start)/seconds_per_day_scaled;
      assay_status.red_light_pulsing = redLightPulsing();
      assay_status.buzzing = buzzing();
    }
    else if (time_now < time_assay_end)
    {
      assay_status.phase_ptr = &constants::phase_recovery_string;
      assay_status.phase_day = (double)(time_now - time_experiment_end)/seconds_per_day_scaled;
    }
    else
    {
      assay_status.assay_day = (double)(time_assay_end - time_entrainment_start)/seconds_per_day_scaled;
      assay_status.phase_ptr = &constants::phase_assay_finished_string;
      assay_status.phase_day = (double)(time_assay_end - time_experiment_end)/seconds_per_day_scaled;
    }

    assay_status.white_light_on = whiteLightOn();
  }

  return assay_status;
}

bool SleepAssayController::whiteLightOn()
{
  long channel;
  modular_server_.property(constants::white_light_channel_property_name).getValue(channel);

  return channelIsOn(channel);
}

bool SleepAssayController::redLightPulsing()
{
  long channel;
  modular_server_.property(constants::red_light_channel_property_name).getValue(channel);

  ChannelsPwmIndexes channels_pwm_indexes = getChannelsPwmIndexes();
  RecursivePwmValues channel_pwm_indexes = channels_pwm_indexes[channel];

  bool red_light_pulsing = false;

  for (size_t i=0; i<channel_pwm_indexes.size(); ++i)
  {
    if (channel_pwm_indexes[i] >= 0)
    {
      red_light_pulsing = true;
      break;
    }
  }
  return red_light_pulsing;
}

bool SleepAssayController::buzzing()
{
  return buzzing_;
}

void SleepAssayController::testWhiteLightPower(const long power)
{
  if (assayStarted() && !assayFinished())
  {
    return;
  }

  long channel;
  modular_server_.property(constants::white_light_channel_property_name).getValue(channel);

  setChannelOnAtPower(channel,power);
}

void SleepAssayController::testRedLightPower(const long power)
{
  if (assayStarted() && !assayFinished())
  {
    return;
  }

  long channel;
  modular_server_.property(constants::red_light_channel_property_name).getValue(channel);

  setChannelOnAtPower(channel,power);
}

void SleepAssayController::testBuzzerPower(const long power)
{
  if (assayStarted() && !assayFinished())
  {
    return;
  }

  long channel;
  modular_server_.property(constants::buzzer_channel_property_name).getValue(channel);

  setChannelOnAtPower(channel,power);
}

void SleepAssayController::stopAllPowerTests()
{
  if (assayStarted() && !assayFinished())
  {
    return;
  }

  setAllChannelsOff();
}

bool SleepAssayController::experimentDayExists(const size_t experiment_day)
{
  return (experiment_day < experiment_day_array_.size());
}

void SleepAssayController::getCameraTriggerPwmInfo(uint32_t & channels,
                                                   long & period,
                                                   long & on_duration)
{
  long channel;
  modular_server_.property(constants::camera_trigger_channel_property_name).getValue(channel);
  uint32_t bit = 1;
  channels = bit << channel;

  double frequency;
  modular_server_.property(constants::camera_trigger_frequency_property_name).getValue(frequency);
  period = (1.0/frequency)*constants::milliseconds_per_second;
  on_duration = period*constants::camera_trigger_duty_cycle/constants::camera_trigger_duty_cycle_max;
}

void SleepAssayController::getWhiteLightPwmInfo(uint32_t & channels,
                                                long & period,
                                                long & on_duration)
{
  long channel;
  modular_server_.property(constants::white_light_channel_property_name).getValue(channel);
  uint32_t bit = 1;
  channels = bit << channel;

  period = scaleDuration(constants::milliseconds_per_day);

  long on_duration_hours;
  modular_server_.property(constants::white_light_on_duration_property_name).getValue(on_duration_hours);
  on_duration = scaleDuration(on_duration_hours*constants::milliseconds_per_hour);
}

void SleepAssayController::getRedLightPwmInfo(const size_t experiment_day,
                                              uint32_t & channels,
                                              long & delay,
                                              HighPowerSwitchController::RecursivePwmValues & periods,
                                              HighPowerSwitchController::RecursivePwmValues & on_durations)
{
  long channel;
  modular_server_.property(constants::red_light_channel_property_name).getValue(channel);
  uint32_t bit = 1;
  channels = bit << channel;

  long frequency;
  modular_server_.property(constants::red_light_frequency_property_name).getValue(frequency);
  long period_0 = (1.0/(double)frequency)*constants::milliseconds_per_second;
  periods.push_back(period_0);

  long duty_cycle;
  modular_server_.property(constants::red_light_duty_cycle_property_name).getValue(duty_cycle);
  long on_duration_0 = period_0*(double)duty_cycle/(double)constants::red_light_duty_cycle_max;
  on_durations.push_back(on_duration_0);

  if (experimentDayExists(experiment_day))
  {
    constants::ExperimentDayInfo & experiment_day_info = experiment_day_array_[experiment_day];
    double red_light_delay_hours = experiment_day_info.red_light_delay_hours;
    delay = scaleDuration(red_light_delay_hours*constants::milliseconds_per_hour);

    double red_light_duration_hours = experiment_day_info.red_light_duration_hours;
    long on_duration_1 = scaleDuration(red_light_duration_hours*constants::milliseconds_per_hour);
    on_durations.push_back(on_duration_1);

    long period_1 = on_duration_1 + 1;
    periods.push_back(period_1);
  }

}

void SleepAssayController::getBuzzerPwmInfo(const size_t experiment_day,
                                            uint32_t & channels,
                                            long & delay,
                                            HighPowerSwitchController::RecursivePwmValues & periods,
                                            HighPowerSwitchController::RecursivePwmValues & on_durations)
{
  long channel;
  modular_server_.property(constants::buzzer_channel_property_name).getValue(channel);
  uint32_t bit = 1;
  channels = bit << channel;

  long on_duration_0;
  modular_server_.property(constants::buzzer_on_duration_property_name).getValue(on_duration_0);
  on_duration_0 *= constants::milliseconds_per_second;
  on_durations.push_back(on_duration_0);

  long buzzer_wait_min;
  modular_server_.property(constants::buzzer_wait_min_property_name).getValue(buzzer_wait_min);
  buzzer_wait_min *= constants::milliseconds_per_second;

  long buzzer_wait_max;
  modular_server_.property(constants::buzzer_wait_max_property_name).getValue(buzzer_wait_max);
  buzzer_wait_max *= constants::milliseconds_per_second;

  long off_duration_0 = random(buzzer_wait_min,buzzer_wait_max);

  long period_0 = on_duration_0 + off_duration_0;
  periods.push_back(period_0);

  if (experimentDayExists(experiment_day))
  {
    constants::ExperimentDayInfo & experiment_day_info = experiment_day_array_[experiment_day];
    double buzzer_delay_hours = experiment_day_info.buzzer_delay_hours;
    delay = scaleDuration(buzzer_delay_hours*constants::milliseconds_per_hour);

    double buzzer_duration_hours = experiment_day_info.buzzer_duration_hours;
    long on_duration_1 = scaleDuration(buzzer_duration_hours*constants::milliseconds_per_hour);
    on_durations.push_back(on_duration_1);

    long period_1 = on_duration_1 + 1;
    periods.push_back(period_1);
  }

}

void SleepAssayController::startCameraTrigger()
{
  uint32_t channels;
  long period;
  long on_duration;
  getCameraTriggerPwmInfo(channels,period,on_duration);

  long delay = 0;
  startPwm(channels,delay,period,on_duration);
}

void SleepAssayController::startAssay()
{
  stopAllPwm();
  setAllChannelsOff();
  enableAll();
  startCameraTrigger();

  assay_started_ = true;
  assay_finished_ = false;

  buzzer_enabled_ = false;
  buzzing_ = false;

  time_t time_now = SleepAssayController::now();
  time_assay_start_ = time_now;
  time_experiment_start_ = time_assay_start_;

  long entrainment_duration;
  modular_server_.property(constants::entrainment_duration_property_name).getValue(entrainment_duration);

  if (entrainment_duration > 0)
  {
    uint32_t channels;
    long period;
    long on_duration;
    getWhiteLightPwmInfo(channels,period,on_duration);

    long start_time;
    modular_server_.property(constants::white_light_start_time_property_name).getValue(start_time);

    long time_zone_offset;
    modular_server_.property(constants::time_zone_offset_property_name).getValue(time_zone_offset);

    start_time -= time_zone_offset;

    long offset = (hour(time_now) - start_time)*constants::milliseconds_per_hour;
    offset += minute(time_now)*constants::milliseconds_per_minute;
    offset += second(time_now)*constants::milliseconds_per_second;
    offset = scaleDuration(offset);

    if ((offset > 0) && (offset < on_duration))
    {
      period -= offset;
      on_duration -= offset;
      long delay = 0;
      long count = 1;
      int pwm_index = addPwm(channels,delay,period,on_duration,count);
      const int entrainment_duration2 = entrainment_duration - 1;
      addCountCompletedFunctor(pwm_index,
                               makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startEntrainment),
                               entrainment_duration2);
      time_experiment_start_ += scaleDuration(entrainment_duration2*constants::seconds_per_day);
      time_experiment_start_ += period/constants::milliseconds_per_second;
    }
    else if (offset >= on_duration)
    {
      long delay = period - offset;
      const int entrainment_duration2 = entrainment_duration - 1;
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startEntrainment),
                         delay,
                         entrainment_duration2);
      time_experiment_start_ += scaleDuration(entrainment_duration2*constants::seconds_per_day);
      time_experiment_start_ += delay/constants::milliseconds_per_second;
    }
    else if (offset <= 0)
    {
      long delay = abs(offset);
      const int entrainment_duration2 = entrainment_duration;
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startEntrainment),
                         delay,
                         entrainment_duration2);
      time_experiment_start_ += scaleDuration(entrainment_duration2*constants::seconds_per_day);
      time_experiment_start_ += delay/constants::milliseconds_per_second;
    }
  }
  else
  {
    // not necessary if minimum entrainment_duration is 1, not 0
  }
}

void SleepAssayController::startEntrainment(const int entrainment_duration)
{
  if (entrainment_duration > 0)
  {
    uint32_t channels;
    long period;
    long on_duration;
    getWhiteLightPwmInfo(channels,period,on_duration);

    int pwm_index = addPwm(channels,0,period,on_duration,entrainment_duration);
    addCountCompletedFunctor(pwm_index,
                             makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startExperimentDay),
                             0);
  }
  else
  {
    startExperimentDay(0);
  }
}

void SleepAssayController::startExperimentDay(const int experiment_day)
{
  if (experiment_day < experiment_day_array_.size())
  {
    uint32_t white_light_channels;
    long white_light_period;
    long white_light_on_duration;
    getWhiteLightPwmInfo(white_light_channels,white_light_period,white_light_on_duration);

    constants::ExperimentDayInfo & experiment_day_info = experiment_day_array_[experiment_day];

    const int next_experiment_day = experiment_day + 1;

    bool white_light = experiment_day_info.white_light;
    if (white_light)
    {
      int white_light_pwm_index = addPwm(white_light_channels,0,white_light_period,white_light_on_duration,1);
      addCountCompletedFunctor(white_light_pwm_index,
                               makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startExperimentDay),
                               next_experiment_day);
    }
    else
    {
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startExperimentDay),
                         white_light_period,
                         next_experiment_day);
    }

    bool red_light = experiment_day_info.red_light;
    if (red_light)
    {
      uint32_t red_light_channels;
      long red_light_delay;
      HighPowerSwitchController::RecursivePwmValues red_light_periods;
      HighPowerSwitchController::RecursivePwmValues red_light_on_durations;
      getRedLightPwmInfo(experiment_day,
                         red_light_channels,
                         red_light_delay,
                         red_light_periods,
                         red_light_on_durations);

      int red_light_pwm_index = addRecursivePwm(red_light_channels,
                                                red_light_delay,
                                                red_light_periods,
                                                red_light_on_durations,
                                                1);
    }

    bool buzzer = experiment_day_info.buzzer;
    if (buzzer)
    {
      uint32_t buzzer_channels;
      long buzzer_delay;
      HighPowerSwitchController::RecursivePwmValues buzzer_periods;
      HighPowerSwitchController::RecursivePwmValues buzzer_on_durations;
      getBuzzerPwmInfo(experiment_day,
                       buzzer_channels,
                       buzzer_delay,
                       buzzer_periods,
                       buzzer_on_durations);

      buzzer_enabled_ = true;
      long buzzer_start_delay = buzzer_delay;
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::buzz),
                         buzzer_start_delay,
                         experiment_day);

      long buzzer_end_delay = buzzer_start_delay + buzzer_on_durations.back();
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::disableBuzzer),
                         buzzer_end_delay,
                         -1);
    }
  }
  else
  {
    startRecovery();
  }
}

void SleepAssayController::startRecovery()
{
  long recovery_duration;
  modular_server_.property(constants::recovery_duration_property_name).getValue(recovery_duration);

  if (recovery_duration > 0)
  {
    uint32_t channels;
    long period;
    long on_duration;
    getWhiteLightPwmInfo(channels,period,on_duration);

    int pwm_index = addPwm(channels,0,period,on_duration,recovery_duration);
    addCountCompletedFunctor(pwm_index,
                             makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::endAssay),
                             -1);
  }
  else
  {
    endAssay(-1);
  }
}

void SleepAssayController::endAssay(const int arg)
{
  stopAllPwm();

  assay_finished_ = true;

  buzzer_enabled_ = false;
  buzzing_ = false;
}

void SleepAssayController::buzz(const int experiment_day)
{
  if (buzzer_enabled_)
  {
    buzzing_ = true;
    uint32_t buzzer_channels;
    long buzzer_delay;
    HighPowerSwitchController::RecursivePwmValues buzzer_periods;
    HighPowerSwitchController::RecursivePwmValues buzzer_on_durations;
    getBuzzerPwmInfo(experiment_day,
                     buzzer_channels,
                     buzzer_delay,
                     buzzer_periods,
                     buzzer_on_durations);

    int pwm_index = addPwm(buzzer_channels,
                           0,
                           buzzer_periods.front(),
                           buzzer_on_durations.front(),
                           1);
    addCountCompletedFunctor(pwm_index,
                             makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::buzz),
                             experiment_day);
  }
  else
  {
    buzzing_ = false;
  }
}

void SleepAssayController::disableBuzzer(const int arg)
{
  buzzer_enabled_ = false;
}

void SleepAssayController::writeDateTimeToResponse(const time_t time)
{
  time_t local_time = epochTimeToLocalTime(time);

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::year_string,year(local_time));
  modular_server_.response().write(constants::month_string,month(local_time));
  modular_server_.response().write(constants::day_string,day(local_time));
  modular_server_.response().write(constants::hour_string,hour(local_time));
  modular_server_.response().write(constants::minute_string,minute(local_time));
  modular_server_.response().write(constants::second_string,second(local_time));

  modular_server_.response().endObject();
}

void SleepAssayController::writeExperimentDayInfoToResponse(const size_t experiment_day)
{
  modular_server_.response().beginObject();

  if (experiment_day >= experiment_day_array_.size())
  {
    modular_server_.response().endObject();
    return;
  }

  constants::ExperimentDayInfo experiment_day_info = experiment_day_array_[experiment_day];

  modular_server_.response().write(constants::white_light_parameter_name,experiment_day_info.white_light);
  modular_server_.response().write(constants::red_light_parameter_name,experiment_day_info.red_light);
  modular_server_.response().write(constants::red_light_delay_parameter_name,experiment_day_info.red_light_delay_hours);
  modular_server_.response().write(constants::red_light_duration_parameter_name,experiment_day_info.red_light_duration_hours);
  modular_server_.response().write(constants::buzzer_parameter_name,experiment_day_info.buzzer);
  modular_server_.response().write(constants::buzzer_delay_parameter_name,experiment_day_info.buzzer_delay_hours);
  modular_server_.response().write(constants::buzzer_duration_parameter_name,experiment_day_info.buzzer_duration_hours);

  modular_server_.response().endObject();
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void SleepAssayController::updatePowersHandler()
{
  long channel;
  long power;
  modular_server::Property & power_max_property = modular_server_.property(high_power_switch_controller::constants::power_max_property_name);

  modular_server_.property(constants::white_light_channel_property_name).getValue(channel);
  modular_server_.property(constants::white_light_power_property_name).getValue(power);
  power_max_property.setElementValue(channel,power);

  modular_server_.property(constants::red_light_channel_property_name).getValue(channel);
  modular_server_.property(constants::red_light_power_property_name).getValue(power);
  power_max_property.setElementValue(channel,power);

  modular_server_.property(constants::buzzer_channel_property_name).getValue(channel);
  modular_server_.property(constants::buzzer_power_property_name).getValue(power);
  power_max_property.setElementValue(channel,power);
}

void SleepAssayController::setTimeHandler()
{
  long epoch_time;
  modular_server_.parameter(constants::epoch_time_parameter_name).getValue(epoch_time);
  SleepAssayController::setTime(epoch_time);
}

void SleepAssayController::getTimeHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t epoch_time = getTime();
  modular_server_.response().returnResult(epoch_time);
}

void SleepAssayController::adjustTimeHandler()
{
  long adjust_time;
  modular_server_.parameter(constants::adjust_time_parameter_name).getValue(adjust_time);
  SleepAssayController::adjustTime(adjust_time);
}

void SleepAssayController::nowHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t time_now = SleepAssayController::now();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_now);
}

void SleepAssayController::getAssayStartHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  bool assay_started = assayStarted();
  if (!assay_started)
  {
    modular_server_.response().returnError(constants::assay_not_started_error);
    return;
  }

  time_t time_assay_start = getAssayStart();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_assay_start);
}

void SleepAssayController::getAssayEndHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  bool assay_started = assayStarted();
  if (!assay_started)
  {
    modular_server_.response().returnError(constants::assay_not_started_error);
    return;
  }

  time_t time_assay_end = getAssayEnd();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_assay_end);
}

void SleepAssayController::getAssayDurationHandler()
{
  uint8_t assay_duration = getAssayDuration();
  modular_server_.response().returnResult(assay_duration);
}

void SleepAssayController::getExperimentStartHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  bool assay_started = assayStarted();
  if (!assay_started)
  {
    modular_server_.response().returnError(constants::assay_not_started_error);
    return;
  }

  time_t time_experiment_start = getExperimentStart();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_experiment_start);
}

void SleepAssayController::getExperimentEndHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  bool assay_started = assayStarted();
  if (!assay_started)
  {
    modular_server_.response().returnError(constants::assay_not_started_error);
    return;
  }

  time_t time_experiment_end = getExperimentEnd();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_experiment_end);
}

void SleepAssayController::getExperimentDurationHandler()
{
  uint8_t experiment_duration = getExperimentDuration();
  modular_server_.response().returnResult(experiment_duration);
}

void SleepAssayController::getEntrainmentStartHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  bool assay_started = assayStarted();
  if (!assay_started)
  {
    modular_server_.response().returnError(constants::assay_not_started_error);
    return;
  }

  time_t time_entrainment_start = getEntrainmentStart();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_entrainment_start);
}

void SleepAssayController::getExperimentInfoHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t day=0; day<experiment_day_array_.size(); ++day)
  {
    writeExperimentDayInfoToResponse(day);
  }

  modular_server_.response().endArray();
}

void SleepAssayController::getExperimentDayInfoHandler()
{
  long experiment_day;
  modular_server_.parameter(constants::experiment_day_parameter_name).getValue(experiment_day);

  if (!experimentDayExists(experiment_day))
  {
    modular_server_.response().returnError(constants::experiment_day_does_not_exist_error);
    return;
  }

  modular_server_.response().writeResultKey();
  writeExperimentDayInfoToResponse(experiment_day);
}

void SleepAssayController::addExperimentDayHandler()
{
  size_t experiment_day = addExperimentDay();
  modular_server_.response().returnResult(experiment_day);
}

void SleepAssayController::addExperimentDaysHandler()
{
  long day_count;
  modular_server_.parameter(constants::day_count_parameter_name).getValue(day_count);

  experiment_day_array_t days_added = addExperimentDays(day_count);

  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t day=0; day<days_added.size(); ++day)
  {
    modular_server_.response().write(days_added[day]);
  }

  modular_server_.response().endArray();
}

void SleepAssayController::addExperimentDayCopyHandler()
{
  long experiment_day;
  modular_server_.parameter(constants::experiment_day_parameter_name).getValue(experiment_day);

  experiment_day = addExperimentDayCopy(experiment_day);
  modular_server_.response().returnResult(experiment_day);
}

void SleepAssayController::addExperimentDayCopiesHandler()
{
  long experiment_day;
  modular_server_.parameter(constants::experiment_day_parameter_name).getValue(experiment_day);

  long day_count;
  modular_server_.parameter(constants::day_count_parameter_name).getValue(day_count);

  experiment_day_array_t days_added = addExperimentDayCopies(experiment_day,
                                                             day_count);

  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t day=0; day<days_added.size(); ++day)
  {
    modular_server_.response().write(days_added[day]);
  }

  modular_server_.response().endArray();
}

void SleepAssayController::removeLastExperimentDayHandler()
{
  removeLastExperimentDay();
}

void SleepAssayController::removeAllExperimentDaysHandler()
{
  removeAllExperimentDays();
}

void SleepAssayController::setExperimentDayWhiteLightHandler()
{
  long experiment_day;
  modular_server_.parameter(constants::experiment_day_parameter_name).getValue(experiment_day);

  if (!experimentDayExists(experiment_day))
  {
    modular_server_.response().returnError(constants::experiment_day_does_not_exist_error);
    return;
  }

  bool white_light;
  modular_server_.parameter(constants::white_light_parameter_name).getValue(white_light);

  setExperimentDayWhiteLight(experiment_day,white_light);

  modular_server_.response().writeResultKey();
  writeExperimentDayInfoToResponse(experiment_day);
}

void SleepAssayController::setExperimentDayRedLightHandler()
{
  long experiment_day;
  modular_server_.parameter(constants::experiment_day_parameter_name).getValue(experiment_day);

  if (!experimentDayExists(experiment_day))
  {
    modular_server_.response().returnError(constants::experiment_day_does_not_exist_error);
    return;
  }

  bool red_light;
  modular_server_.parameter(constants::red_light_parameter_name).getValue(red_light);

  double red_light_delay;
  modular_server_.parameter(constants::red_light_delay_parameter_name).getValue(red_light_delay);

  double red_light_duration;
  modular_server_.parameter(constants::red_light_duration_parameter_name).getValue(red_light_duration);

  setExperimentDayRedLight(experiment_day,red_light,red_light_delay,red_light_duration);

  modular_server_.response().writeResultKey();
  writeExperimentDayInfoToResponse(experiment_day);
}

void SleepAssayController::setExperimentDayBuzzerHandler()
{
  long experiment_day;
  modular_server_.parameter(constants::experiment_day_parameter_name).getValue(experiment_day);

  if (!experimentDayExists(experiment_day))
  {
    modular_server_.response().returnError(constants::experiment_day_does_not_exist_error);
    return;
  }

  bool buzzer;
  modular_server_.parameter(constants::buzzer_parameter_name).getValue(buzzer);

  double buzzer_delay;
  modular_server_.parameter(constants::buzzer_delay_parameter_name).getValue(buzzer_delay);

  double buzzer_duration;
  modular_server_.parameter(constants::buzzer_duration_parameter_name).getValue(buzzer_duration);

  setExperimentDayBuzzer(experiment_day,buzzer,buzzer_delay,buzzer_duration);

  modular_server_.response().writeResultKey();
  writeExperimentDayInfoToResponse(experiment_day);
}

void SleepAssayController::getAssayStatusHandler()
{
  constants::AssayStatus assay_status = getAssayStatus();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  // modular_server_.response().write(constants::time_entrainment_start_string,getEntrainmentStart());

  // modular_server_.response().write(constants::time_assay_start_string,getAssayStart());

  // modular_server_.response().write(constants::time_experiment_start_string,getExperimentStart());

  // modular_server_.response().write(constants::time_experiment_end_string,getExperimentEnd());

  // modular_server_.response().write(constants::time_assay_end_string,getAssayEnd());

  modular_server_.response().write(constants::time_now_string,assay_status.time);

  modular_server_.response().writeKey(constants::date_time_now_string);
  if (timeIsSet())
  {
    writeDateTimeToResponse(assay_status.time);
  }
  else
  {
    modular_server_.response().beginObject();
    modular_server_.response().endObject();
  }

  modular_server_.response().write(constants::assay_day_string,assay_status.assay_day);

  modular_server_.response().write(constants::phase_string,assay_status.phase_ptr);

  modular_server_.response().write(constants::phase_day_string,assay_status.phase_day);

  modular_server_.response().write(constants::white_light_on_string,assay_status.white_light_on);

  modular_server_.response().write(constants::red_light_pulsing_string,assay_status.red_light_pulsing);

  modular_server_.response().write(constants::buzzing_string,assay_status.buzzing);

  modular_server_.response().write(constants::testing_string,assay_status.testing);

  modular_server_.response().endObject();
}

void SleepAssayController::testWhiteLightPowerHandler()
{
  size_t power;
  modular_server_.parameter(high_power_switch_controller::constants::power_parameter_name).getValue(power);

  testWhiteLightPower(power);
}

void SleepAssayController::testRedLightPowerHandler()
{
  size_t power;
  modular_server_.parameter(high_power_switch_controller::constants::power_parameter_name).getValue(power);

  testRedLightPower(power);
}

void SleepAssayController::testBuzzerPowerHandler()
{
  size_t power;
  modular_server_.parameter(high_power_switch_controller::constants::power_parameter_name).getValue(power);

  testBuzzerPower(power);
}

void SleepAssayController::stopAllPowerTestsHandler()
{
  stopAllPowerTests();
}

void SleepAssayController::runAssayHandler(modular_server::Interrupt * interrupt_ptr)
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  runAssay();
}

void SleepAssayController::testAssayHandler(modular_server::Interrupt * interrupt_ptr)
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  testAssay();
}

void SleepAssayController::stopAssayHandler(modular_server::Interrupt * interrupt_ptr)
{
  stopAssay();
}
