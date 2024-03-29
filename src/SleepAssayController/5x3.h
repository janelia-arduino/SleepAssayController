// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef SLEEP_ASSAY_CONTROLLER_5X3_CONSTANTS_H
#define SLEEP_ASSAY_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

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
extern const double ir_backlight_power_to_intensity_ratio_default[backlight_controller::constants::IR_BACKLIGHT_COUNT];

extern const double ir_backlight_intensity_max_default[backlight_controller::constants::IR_BACKLIGHT_COUNT];

extern const double visible_backlight_power_to_intensity_ratio_default[backlight_controller::constants::VISIBLE_BACKLIGHT_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
