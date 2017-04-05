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

  // Functions
  modular_server::Function & set_epoch_time_function = modular_server_.createFunction(constants::set_epoch_time_function_name);
  set_epoch_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::setEpochTimeHandler));
  set_epoch_time_function.addParameter(epoch_time_parameter);

  modular_server::Function & get_epoch_time_function = modular_server_.createFunction(constants::get_epoch_time_function_name);
  get_epoch_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getEpochTimeHandler));
  get_epoch_time_function.setReturnTypeLong();

  modular_server::Function & get_date_time_now_function = modular_server_.createFunction(constants::get_date_time_now_function_name);
  get_date_time_now_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getDateTimeNowHandler));
  get_date_time_now_function.setReturnTypeObject();

  modular_server::Function & get_date_time_assay_start_function = modular_server_.createFunction(constants::get_date_time_assay_start_function_name);
  get_date_time_assay_start_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getDateTimeAssayStartHandler));
  get_date_time_assay_start_function.setReturnTypeObject();

  modular_server::Function & get_date_time_assay_end_function = modular_server_.createFunction(constants::get_date_time_assay_end_function_name);
  get_date_time_assay_end_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getDateTimeAssayEndHandler));
  get_date_time_assay_end_function.setReturnTypeObject();

  // Callbacks
  modular_server::Callback & run_assay_callback = modular_server_.createCallback(constants::run_assay_callback_name);
  run_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&SleepAssayController::runAssayHandler));

  modular_server::Callback & test_assay_callback = modular_server_.createCallback(constants::test_assay_callback_name);
  test_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&SleepAssayController::testAssayHandler));

  modular_server::Callback & stop_assay_callback = modular_server_.createCallback(constants::stop_assay_callback_name);
  stop_assay_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&SleepAssayController::stopAssayHandler));

}

void SleepAssayController::setEpochTime(const time_t epoch_time)
{
  setTime(epoch_time);
}

time_t SleepAssayController::getEpochTime()
{
  return now();
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
  time_t date_time_assay_start = getDateTimeAssayStart();
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

time_t SleepAssayController::getDateTimeNow()
{
  long time_zone_offset;
  modular_server_.property(constants::time_zone_offset_property_name).getValue(time_zone_offset);
  return now() + time_zone_offset*constants::minutes_per_hour*constants::seconds_per_minute;
}

time_t SleepAssayController::getDateTimeAssayStart()
{
  return date_time_assay_start_;
}

time_t SleepAssayController::getDateTimeAssayEnd()
{
  long entrainment_duration;
  modular_server_.property(constants::entrainment_duration_property_name).getValue(entrainment_duration);

  long recovery_duration;
  modular_server_.property(constants::recovery_duration_property_name).getValue(recovery_duration);

  time_t date_time_assay_end = getDateTimeAssayStart();
  date_time_assay_end += entrainment_duration*constants::seconds_per_day;
  date_time_assay_end += recovery_duration*constants::seconds_per_day;
  return date_time_assay_end;
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

  time_t date_time_now = getDateTimeNow();
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
    // addCountCompletedFunctor(pwm_index,
    //                          makeFunctor((Functor0 *)0,*this,&SleepAssayController::startEntrainment));
  }
  else
  {
    
  }
}

void SleepAssayController::writeDateTimeToResponse(const time_t date_time)
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::year_string,year(date_time));
  modular_server_.response().write(constants::month_string,month(date_time));
  modular_server_.response().write(constants::day_string,day(date_time));
  modular_server_.response().write(constants::hour_string,hour(date_time));
  modular_server_.response().write(constants::minute_string,minute(date_time));
  modular_server_.response().write(constants::second_string,second(date_time));

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

void SleepAssayController::setEpochTimeHandler()
{
  long epoch_time;
  modular_server_.parameter(constants::epoch_time_parameter_name).getValue(epoch_time);
  setEpochTime(epoch_time);
}

void SleepAssayController::getEpochTimeHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t epoch_time = getEpochTime();
  modular_server_.response().returnResult(epoch_time);
}

void SleepAssayController::getDateTimeNowHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t date_time_now = getDateTimeNow();
  writeDateTimeToResponse(date_time_now);
}

void SleepAssayController::getDateTimeAssayStartHandler()
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

  time_t date_time_assay_start = getDateTimeAssayStart();
  writeDateTimeToResponse(date_time_assay_start);
}

void SleepAssayController::getDateTimeAssayEndHandler()
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

  time_t date_time_assay_end = getDateTimeAssayEnd();
  writeDateTimeToResponse(date_time_assay_end);
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
