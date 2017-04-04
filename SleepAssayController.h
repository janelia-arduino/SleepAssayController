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
#include "Time.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "HighPowerSwitchController.h"

#include "utility/Constants.h"


class SleepAssayController : public HighPowerSwitchController
{
public:
  SleepAssayController();
  virtual void setup();

  void setEpochTime(const time_t epoch_time);
  time_t getEpochTime();
  bool timeIsSet();

  void runAssay();
  void testAssay();

  time_t getDateTimeNow();
  time_t getDateTimeAssayStart();
  time_t getDateTimeAssayEnd();

private:
  modular_server::Property properties_[sleep_assay_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[sleep_assay_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[sleep_assay_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[sleep_assay_controller::constants::CALLBACK_COUNT_MAX];

  bool testing_;

  time_t date_time_assay_start_;

  void getCameraTriggerInfo(uint32_t & channels,
                            long & period,
                            long & on_duration);
  void getWhiteLightInfo(uint32_t & channels,
                         long & period,
                         long & on_duration,
                         long & start_time);

  void startCameraTrigger();
  void setupAssay();
  void startEntrainment();

  void writeDateTimeToResponse(const time_t date_time);

  // Handlers
  void updatePowersHandler();
  void setEpochTimeHandler();
  void getEpochTimeHandler();
  void getDateTimeNowHandler();
  void getDateTimeAssayStartHandler();
  void getDateTimeAssayEndHandler();
  void runAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void testAssayHandler(modular_server::Interrupt * interrupt_ptr);

};

#endif
