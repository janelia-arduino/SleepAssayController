// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SLEEP_ASSAY_CONTROLLER_3X2_CONSTANTS_H
#define SLEEP_ASSAY_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace sleep_assay_controller
{
namespace constants
{
enum{EXPERIMENT_DAY_COUNT_MAX=20};

extern const size_t ir_backlight;

extern const size_t visible_backlight;

extern const size_t fan_high_voltage;

extern const size_t white_light_high_voltage;

extern const size_t buzzer_high_voltage;

extern const size_t camera_trigger_low_voltage;

extern const size_t visible_backlight_indicator_low_voltage;

extern const size_t white_light_indicator_low_voltage;

extern const size_t buzzer_indicator_low_voltage;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
