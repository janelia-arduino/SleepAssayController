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
  epoch_time_parameter.setTypeLong();
  epoch_time_parameter.setUnits(constants::seconds_unit);

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

  // Functions
  modular_server::Function & set_time_function = modular_server_.createFunction(constants::set_time_function_name);
  set_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::setTimeHandler));
  set_time_function.addParameter(epoch_time_parameter);

  modular_server::Function & get_time_function = modular_server_.createFunction(constants::get_time_function_name);
  get_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getTimeHandler));
  get_time_function.setReturnTypeLong();

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

bool SleepAssayController::timeIsSet()
{
  timeStatus_t time_status = timeStatus();
  return (time_status != timeNotSet);
}

void SleepAssayController::runAssay()
{
  if (!timeIsSet())
  {
    return;
  }
  testing_ = false;
  startAssay();
}

void SleepAssayController::testAssay()
{
  if (!timeIsSet())
  {
    return;
  }
  testing_ = true;
  startAssay();
}

void SleepAssayController::stopAssay()
{
  stopAllPwm();
  testing_ = false;
  date_time_assay_start_ = 0;
  date_time_experiment_start_ = 0;
}

bool SleepAssayController::assayStarted()
{
  time_t date_time_assay_start = getAssayStart();
  return (date_time_assay_start != 0);
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
  long time_zone_offset;
  modular_server_.property(constants::time_zone_offset_property_name).getValue(time_zone_offset);
  return ::now() + time_zone_offset*constants::minutes_per_hour*constants::seconds_per_minute;
}

time_t SleepAssayController::getAssayStart()
{
  return date_time_assay_start_;
}

time_t SleepAssayController::getAssayEnd()
{
  long recovery_duration;
  modular_server_.property(constants::recovery_duration_property_name).getValue(recovery_duration);

  time_t date_time_assay_end = getExperimentEnd();
  date_time_assay_end += scaleDuration(recovery_duration*constants::seconds_per_day);
  return date_time_assay_end;
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
  return date_time_experiment_start_;
}

time_t SleepAssayController::getExperimentEnd()
{
  time_t date_time_experiment_end = getExperimentStart();
  date_time_experiment_end += scaleDuration(experiment_day_array_.size()*constants::seconds_per_day);
  return date_time_experiment_end;
}

uint8_t SleepAssayController::getExperimentDuration()
{
  return experiment_day_array_.size();
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

  period = constants::milliseconds_per_day;

  long on_duration_hours;
  modular_server_.property(constants::white_light_on_duration_property_name).getValue(on_duration_hours);
  on_duration = on_duration_hours*constants::milliseconds_per_hour;
}

void SleepAssayController::getRedLightPwmInfo(const size_t experiment_day,
                                              uint32_t & channels,
                                              long & delay,
                                              HighPowerSwitchController::RecursivePwmValues & periods,
                                              HighPowerSwitchController::RecursivePwmValues & on_durations)
{
  if (experimentDayExists(experiment_day))
  {
    
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
  enableAll();
  startCameraTrigger();

  time_t date_time_now = SleepAssayController::now();
  date_time_assay_start_ = date_time_now;
  date_time_experiment_start_ = date_time_assay_start_;

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

    long offset = (hour(date_time_now) - start_time)*constants::milliseconds_per_hour;
    offset += minute(date_time_now)*constants::milliseconds_per_minute;
    offset += second(date_time_now)*constants::milliseconds_per_second;

    if ((offset > 0) && (offset < on_duration))
    {
      period -= offset;
      on_duration -= offset;
      long delay = 0;
      long count = 1;
      int pwm_index = addPwm(channels,delay,scaleDuration(period),scaleDuration(on_duration),count);
      const int entrainment_duration2 = entrainment_duration - 1;
      addCountCompletedFunctor(pwm_index,
                               makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startEntrainment),
                               entrainment_duration2);
      date_time_experiment_start_ += scaleDuration(entrainment_duration2*constants::seconds_per_day);
      date_time_experiment_start_ += scaleDuration(period/constants::milliseconds_per_second);
    }
    else if (offset >= on_duration)
    {
      long delay = period - offset;
      const int entrainment_duration2 = entrainment_duration - 1;
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startEntrainment),
                         delay,
                         entrainment_duration2);
      date_time_experiment_start_ += scaleDuration(entrainment_duration2*constants::seconds_per_day);
      date_time_experiment_start_ += scaleDuration(delay/constants::milliseconds_per_second);
    }
    else if (offset <= 0)
    {
      long delay = abs(offset);
      const int entrainment_duration2 = entrainment_duration;
      addEventUsingDelay(makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startEntrainment),
                         delay,
                         entrainment_duration2);
      date_time_experiment_start_ += scaleDuration(entrainment_duration2*constants::seconds_per_day);
      date_time_experiment_start_ += scaleDuration(delay/constants::milliseconds_per_second);
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

    int pwm_index = addPwm(channels,0,scaleDuration(period),scaleDuration(on_duration),entrainment_duration);
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

    int pwm_index = addPwm(white_light_channels,0,scaleDuration(white_light_period),scaleDuration(white_light_on_duration),1);
    const int next_experiment_day = experiment_day + 1;
    addCountCompletedFunctor(pwm_index,
                             makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::startExperimentDay),
                             next_experiment_day);

    constants::ExperimentDayInfo & experiment_day_info = experiment_day_array_[experiment_day];
    bool red_light = experiment_day_info.red_light;
    if (red_light)
    {
      
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

    int pwm_index = addPwm(channels,0,scaleDuration(period),scaleDuration(on_duration),recovery_duration);
    addCountCompletedFunctor(pwm_index,
                             makeFunctor((Functor1<int> *)0,*this,&SleepAssayController::stopAssay),
                             -1);
  }
  else
  {
    stopAssay(-1);
  }
}

void SleepAssayController::stopAssay(const int arg)
{
  stopAssay();
}

void SleepAssayController::writeDateTimeToResponse(const time_t date_time)
{
  modular_server_.response().beginObject();

  modular_server_.response().write(constants::year_string,year(date_time));
  modular_server_.response().write(constants::month_string,month(date_time));
  modular_server_.response().write(constants::day_string,day(date_time));
  modular_server_.response().write(constants::hour_string,hour(date_time));
  modular_server_.response().write(constants::minute_string,minute(date_time));
  modular_server_.response().write(constants::second_string,second(date_time));

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
// modular_server_.property(property_name).getElementValue(value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(value) value type must match the property array element default type

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

void SleepAssayController::nowHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t date_time_now = SleepAssayController::now();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(date_time_now);
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

  time_t date_time_assay_start = getAssayStart();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(date_time_assay_start);
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

  time_t date_time_assay_end = getAssayEnd();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(date_time_assay_end);
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

  time_t date_time_experiment_start = getExperimentStart();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(date_time_experiment_start);
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

  time_t date_time_experiment_end = getExperimentEnd();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(date_time_experiment_end);
}

void SleepAssayController::getExperimentDurationHandler()
{
  uint8_t experiment_duration = getExperimentDuration();
  modular_server_.response().returnResult(experiment_duration);
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
