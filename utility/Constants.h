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
enum{PROPERTY_COUNT_MAX=4};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const long channel_min;
extern const long channel_max;

extern const long milliseconds_per_second;
extern const long seconds_per_minute;
extern const long minutes_per_hour;
extern const long hours_per_day;
extern const long milliseconds_per_hour;
extern const long milliseconds_per_day;

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString indicator_channel_property_name;
extern const long indicator_channel_default;

extern ConstantString camera_trigger_channel_property_name;
extern const long camera_trigger_channel_default;

extern ConstantString white_light_channel_property_name;
extern const long white_light_channel_default;

extern ConstantString red_light_channel_property_name;
extern const long red_light_channel_default;

// Parameters

// Functions

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
