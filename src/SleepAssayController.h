// ----------------------------------------------------------------------------
// SleepAssayController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SLEEP_ASSAY_CONTROLLER_H
#define SLEEP_ASSAY_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <HighPowerSwitchController.h>

#include "SleepAssayController/Constants.h"


class SleepAssayController : public HighPowerSwitchController
{
public:
  SleepAssayController();
  virtual void setup();

  void runAssay();
  void testAssay();
  void stopAssay();
  bool assayStarted();
  bool assayFinished();
  bool testing();

  long scaleDuration(const long duration);

  time_t getAssayStart();
  time_t getAssayEnd();
  uint8_t getAssayDuration();
  time_t getExperimentStart();
  time_t getExperimentEnd();
  uint8_t getExperimentDuration();
  time_t getEntrainmentStart();

  typedef Array<sleep_assay_controller::constants::ExperimentDayInfo,
                sleep_assay_controller::constants::EXPERIMENT_DAY_COUNT_MAX> experiment_day_info_array_t;
  typedef Array<size_t,
                sleep_assay_controller::constants::EXPERIMENT_DAY_COUNT_MAX> experiment_day_array_t;

  experiment_day_info_array_t getExperimentInfo();
  bool experimentDayExists(const size_t experiment_day);

  size_t addExperimentDay();
  experiment_day_array_t addExperimentDays(const size_t experiment_day_count);
  size_t addExperimentDayCopy(const size_t experiment_day);
  experiment_day_array_t addExperimentDayCopies(const size_t experiment_day,
                                                const size_t experiment_day_count);
  void removeLastExperimentDay();
  void removeAllExperimentDays();

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

  sleep_assay_controller::constants::AssayStatus getAssayStatus();

  bool whiteLightOn();
  bool redLightPulsing();
  bool buzzingPossible();
  bool buzzing();

  void testWhiteLightPower(const long power);
  void testRedLightPower(const long power);
  void testBuzzerPower(const long power);
  void stopAllPowerTests();

private:
  modular_server::Property properties_[sleep_assay_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[sleep_assay_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[sleep_assay_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[sleep_assay_controller::constants::CALLBACK_COUNT_MAX];

  bool assay_started_;
  bool assay_finished_;
  bool testing_;

  time_t time_assay_start_;
  time_t time_experiment_start_;

  bool buzzer_enabled_;
  bool buzzing_possible_;
  int buzzer_pwm_index_;

  bool camera_trigger_running_;
  int camera_trigger_pwm_index_;

  experiment_day_info_array_t experiment_day_array_;

  void getCameraTriggerPwmInfo(uint32_t & channels,
                               long & period,
                               long & on_duration);
  void getWhiteLightPwmInfo(uint32_t & channels,
                            long & period,
                            long & on_duration);
  void getRedLightPwmInfo(const size_t experiment_day,
                          uint32_t & channels,
                          long & delay,
                          HighPowerSwitchController::RecursivePwmValues & periods,
                          HighPowerSwitchController::RecursivePwmValues & on_durations);
  void getBuzzerPwmInfo(const size_t experiment_day,
                        uint32_t & channels,
                        long & delay,
                        HighPowerSwitchController::RecursivePwmValues & periods,
                        HighPowerSwitchController::RecursivePwmValues & on_durations);

  void initializeVariables();
  void initializeChannels();
  void stopAllAssayPwm();
  void startCameraTrigger();
  void stopCameraTrigger();
  void startAssay();
  void startEntrainment(const int entrainment_duration);
  void startExperimentDay(const int experiment_day);
  void startRecovery();
  void endAssay(const int arg);
  void buzz(const int experiment_day);
  void disableBuzzer(const int arg);

  void writeExperimentDayInfoToResponse(const size_t experiment_day);

  // Handlers
  void updateCameraTriggerHandler();
  void updatePowersHandler();
  void getAssayStartHandler();
  void getAssayEndHandler();
  void getAssayDurationHandler();
  void getExperimentStartHandler();
  void getExperimentEndHandler();
  void getExperimentDurationHandler();
  void getEntrainmentStartHandler();
  void getExperimentInfoHandler();
  void getExperimentDayInfoHandler();
  void addExperimentDayHandler();
  void addExperimentDaysHandler();
  void addExperimentDayCopyHandler();
  void addExperimentDayCopiesHandler();
  void removeLastExperimentDayHandler();
  void removeAllExperimentDaysHandler();
  void setExperimentDayWhiteLightHandler();
  void setExperimentDayRedLightHandler();
  void setExperimentDayBuzzerHandler();
  void getAssayStatusHandler();
  void testWhiteLightPowerHandler();
  void testRedLightPowerHandler();
  void testBuzzerPowerHandler();
  void stopAllPowerTestsHandler();
  void runAssayHandler(modular_server::Pin * pin_ptr);
  void testAssayHandler(modular_server::Pin * pin_ptr);
  void stopAssayHandler(modular_server::Pin * pin_ptr);

};

#endif
