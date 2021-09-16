// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace sleep_assay_controller
{
namespace constants
{

const size_t ir_backlight = 0;

const size_t visible_backlight = 0;

const size_t fan_high_voltage = 0;

const size_t white_light_high_voltage = 1;

const size_t buzzer_high_voltage = 2;

const size_t camera_trigger_low_voltage = 0;

const size_t visible_backlight_indicator_low_voltage = 1;

const size_t white_light_indicator_low_voltage = 2;

const size_t buzzer_indicator_low_voltage = 3;

// Pins

// Units

// Properties
const double ir_backlight_power_to_intensity_ratio_default[backlight_controller::constants::IR_BACKLIGHT_COUNT] =
{
  ir_backlight_power_to_intensity_ratio_element_default,
  ir_backlight_power_to_intensity_ratio_element_default,
  ir_backlight_power_to_intensity_ratio_element_default,
  ir_backlight_power_to_intensity_ratio_element_default,
};

const double ir_backlight_intensity_max_default[backlight_controller::constants::IR_BACKLIGHT_COUNT] =
{
  ir_backlight_intensity_max_element_default,
  ir_backlight_intensity_max_element_default,
  ir_backlight_intensity_max_element_default,
  ir_backlight_intensity_max_element_default,
};

const double visible_backlight_power_to_intensity_ratio_default[backlight_controller::constants::VISIBLE_BACKLIGHT_COUNT] =
{
  visible_backlight_power_to_intensity_ratio_element_default,
  visible_backlight_power_to_intensity_ratio_element_default,
  visible_backlight_power_to_intensity_ratio_element_default,
  visible_backlight_power_to_intensity_ratio_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
