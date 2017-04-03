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
  testing_ = false;

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

  modular_server::Function & get_local_date_time_function = modular_server_.createFunction(constants::get_local_date_time_function_name);
  get_local_date_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getLocalDateTimeHandler));
  get_local_date_time_function.setReturnTypeObject();

  modular_server::Function & run_assay_function = modular_server_.createFunction(constants::run_assay_function_name);
  run_assay_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::runAssayHandler));

}

void SleepAssayController::setEpochTime(const time_t epoch_time)
{
  setTime(epoch_time);
}

time_t SleepAssayController::getEpochTime()
{
  return now();
}

time_t SleepAssayController::getLocalTime()
{
  long time_zone_offset;
  modular_server_.property(constants::time_zone_offset_property_name).getValue(time_zone_offset);
  return now() + time_zone_offset*constants::minutes_per_hour*constants::seconds_per_minute;
}

bool SleepAssayController::timeIsSet()
{
  timeStatus_t time_status = timeStatus();
  return (time_status != timeNotSet);
}

void SleepAssayController::runAssay()
{
  testing_ = false;
  startEntrainment();
}

void SleepAssayController::testAssay()
{
  testing_ = true;
  startEntrainment();
}

void SleepAssayController::startEntrainment()
{
  startCameraTrigger();

  long entrainment_duration;
  modular_server_.property(constants::entrainment_duration_property_name).getValue(entrainment_duration);

  if (entrainment_duration > 0)
  {
    
  }
}

void SleepAssayController::startCameraTrigger()
{
  long channel;
  modular_server_.property(constants::camera_trigger_channel_property_name).getValue(channel);
  uint32_t bit = 1;
  uint32_t channels = bit << channel;

  double frequency;
  modular_server_.property(constants::camera_trigger_frequency_property_name).getValue(frequency);
  long period = 1/frequency;
  long on_duration = period*constants::camera_trigger_duty_cycle/constants::camera_trigger_duty_cycle_max;

  startPwm(channels,0,period,on_duration);
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

void SleepAssayController::getLocalDateTimeHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t local_time = getLocalTime();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::year_string,year(local_time));
  modular_server_.response().write(constants::month_string,month(local_time));
  modular_server_.response().write(constants::day_string,day(local_time));
  modular_server_.response().write(constants::hour_string,hour(local_time));
  modular_server_.response().write(constants::minute_string,minute(local_time));
  modular_server_.response().write(constants::second_string,second(local_time));

  modular_server_.response().endObject();
}

void SleepAssayController::runAssayHandler()
{
}
