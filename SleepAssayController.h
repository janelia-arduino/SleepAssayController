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

  void setTime(const time_t epoch_time);
  time_t getTime();
  bool timeIsSet();

  void runAssay();
  void testAssay();
  void stopAssay();
  bool assayStarted();
  bool testing();

  long scaleDuration(const long duration);

  time_t now();
  time_t assayStart();
  time_t assayEnd();
  time_t experimentStart();
  time_t experimentEnd();

  Array<sleep_assay_controller::constants::ExperimentDayInfo,
        sleep_assay_controller::constants::EXPERIMENT_DAY_COUNT_MAX> getExperimentInfo();
  bool experimentDayExists(const size_t experiment_day);
  size_t addDefaultExperimentDay();
  void setExperimentDayWhiteLightInfo(const size_t experiment_day);

private:
  modular_server::Property properties_[sleep_assay_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[sleep_assay_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[sleep_assay_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[sleep_assay_controller::constants::CALLBACK_COUNT_MAX];

  bool testing_;

  time_t date_time_assay_start_;
  time_t date_time_experiment_start_;

  Array<sleep_assay_controller::constants::ExperimentDayInfo,
        sleep_assay_controller::constants::EXPERIMENT_DAY_COUNT_MAX> experiment_day_array_;

  void getCameraTriggerPwmInfo(uint32_t & channels,
                               long & period,
                               long & on_duration);
  void getWhiteLightPwmInfo(uint32_t & channels,
                            long & period,
                            long & on_duration);

  void startCameraTrigger();
  void startAssay();
  void startEntrainment(const int entrainment_duration);

  void writeDateTimeToResponse(const time_t date_time);
  void writeExperimentDayInfoToResponse(const size_t experiment_day);

  // Handlers
  void updatePowersHandler();
  void setTimeHandler();
  void getTimeHandler();
  void nowHandler();
  void assayStartHandler();
  void assayEndHandler();
  void experimentStartHandler();
  void experimentEndHandler();
  void getExperimentInfoHandler();
  void getExperimentDayInfoHandler();
  void addDefaultExperimentDayHandler();
  void setExperimentDayWhiteLightInfoHandler();
  void setExperimentDayRedLightInfoHandler();
  void setExperimentDayBuzzerInfoHandler();
  void runAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void testAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void stopAssayHandler(modular_server::Interrupt * interrupt_ptr);

};

#endif
