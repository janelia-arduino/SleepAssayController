// ----------------------------------------------------------------------------
// SleepAssayController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SLEEP_ASSAY_CONTROLLER_H
#define SLEEP_ASSAY_CONTROLLER_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "EventController.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "HighPowerSwitchController.h"

#include "utility/Constants.h"


class SleepAssayController : public HighPowerSwitchController
{
public:
  SleepAssayController();
  virtual void setup();

private:
  modular_server::Property properties_[sleep_assay_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[sleep_assay_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[sleep_assay_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[sleep_assay_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
