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

  modular_server::Property & white_light_channel_property = modular_server_.createProperty(constants::white_light_channel_property_name,constants::white_light_channel_default);
  white_light_channel_property.setRange(constants::channel_min,constants::channel_max);

  modular_server::Property & red_light_channel_property = modular_server_.createProperty(constants::red_light_channel_property_name,constants::red_light_channel_default);
  red_light_channel_property.setRange(constants::channel_min,constants::channel_max);

  modular_server::Property & camera_trigger_frequency_property = modular_server_.createProperty(constants::camera_trigger_frequency_property_name,constants::camera_trigger_frequency_default);
  camera_trigger_frequency_property.setRange(constants::camera_trigger_frequency_min,constants::camera_trigger_frequency_max);

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

  modular_server::Function & get_date_time_function = modular_server_.createFunction(constants::get_date_time_function_name);
  get_date_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::getDateTimeHandler));
  get_date_time_function.setReturnTypeObject();

  modular_server::Function & run_experiment_function = modular_server_.createFunction(constants::run_experiment_function_name);
  run_experiment_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&SleepAssayController::runExperimentHandler));

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

void SleepAssayController::getDateTimeHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t epoch_time = getEpochTime();

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::year_string,year(epoch_time));
  modular_server_.response().write(constants::month_string,month(epoch_time));
  modular_server_.response().write(constants::day_string,day(epoch_time));
  modular_server_.response().write(constants::hour_string,hour(epoch_time));
  modular_server_.response().write(constants::minute_string,minute(epoch_time));
  modular_server_.response().write(constants::second_string,second(epoch_time));

  modular_server_.response().endObject();
}

void SleepAssayController::runExperimentHandler()
{
}
