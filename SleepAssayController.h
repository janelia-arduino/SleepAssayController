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
  time_t getAssayStart();
  time_t getAssayEnd();
  time_t getExperimentStart();
  time_t getExperimentEnd();

  Array<sleep_assay_controller::constants::ExperimentDayInfo,
        sleep_assay_controller::constants::EXPERIMENT_DAY_COUNT_MAX> getExperimentInfo();
  bool experimentDayExists(const size_t experiment_day);
  size_t addExperimentDayDefault();
  void setExperimentDayWhiteLight(const size_t experiment_day,
                                  const bool white_light);
  void setExperimentDayRedLight(const size_t experiment_day,
                                const bool red_light,
                                const double red_light_delay_hours,
                                const double red_light_duration_hours);
  void setExperimentDayBuzzer(const size_t experiment_day,
                              const bool buzzer,
                              const double buzzer_delay_hours,
                              const double buzzer_duration_hours);

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
  void getAssayStartHandler();
  void getAssayEndHandler();
  void getExperimentStartHandler();
  void getExperimentEndHandler();
  void getExperimentInfoHandler();
  void getExperimentDayInfoHandler();
  void addExperimentDayDefaultHandler();
  void setExperimentDayWhiteLightHandler();
  void setExperimentDayRedLightHandler();
  void setExperimentDayBuzzerHandler();
  void runAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void testAssayHandler(modular_server::Interrupt * interrupt_ptr);
  void stopAssayHandler(modular_server::Interrupt * interrupt_ptr);

};

#endif
