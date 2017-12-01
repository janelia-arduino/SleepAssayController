# SleepAssayController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

[HighPowerSwitchController](https://github.com/janelia-arduino/HighPowerSwitchController)

## Clients

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

[high_power_switch_controller](https://github.com/janelia-modular-devices/high_power_switch_controller.git)

## API NAMES

```json
{
  "id": "getApi",
  "result": {
    "firmware": [
      "SleepAssayController"
    ],
    "verbosity": "NAMES",
    "functions": [
      "setTime",
      "getTime",
      "adjustTime",
      "now",
      "getAssayStart",
      "getAssayEnd",
      "getAssayDuration",
      "getExperimentStart",
      "getExperimentEnd",
      "getExperimentDuration",
      "getEntrainmentStart",
      "getExperimentInfo",
      "getExperimentDayInfo",
      "addExperimentDay",
      "addExperimentDays",
      "addExperimentDayCopy",
      "addExperimentDayCopies",
      "removeLastExperimentDay",
      "removeAllExperimentDays",
      "setExperimentDayWhiteLight",
      "setExperimentDayRedLight",
      "setExperimentDayBuzzer",
      "getAssayStatus",
      "testWhiteLightPower",
      "testRedLightPower",
      "testBuzzerPower",
      "stopAllPowerTests"
    ],
    "parameters": [
      "epoch_time",
      "adjust_time",
      "experiment_day",
      "white_light",
      "red_light",
      "red_light_delay",
      "red_light_duration",
      "buzzer",
      "buzzer_delay",
      "buzzer_duration",
      "day_count"
    ],
    "properties": [
      "cameraTriggerChannel",
      "cameraTriggerFrequency",
      "whiteLightChannel",
      "whiteLightIndicatorChannel",
      "whiteLightPower",
      "whiteLightStartTime",
      "whiteLightOnDuration",
      "redLightChannel",
      "redLightIndicatorChannel",
      "redLightPower",
      "redLightFrequency",
      "redLightDutyCycle",
      "buzzerChannel",
      "buzzerIndicatorChannel",
      "buzzerPower",
      "buzzerOnDurationMin",
      "buzzerOnDurationMax",
      "buzzerWaitMin",
      "buzzerWaitMax",
      "timeZoneOffset",
      "entrainmentDuration",
      "recoveryDuration",
      "testingDayDuration"
    ],
    "callbacks": [
      "runAssay",
      "testAssay",
      "stopAssay"
    ]
  }
}
```

## API GENERAL

[API GENERAL](./api/)

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
