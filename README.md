# SleepAssayController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

[Examples](./examples)

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["SleepAssayController"],
    "functions":[
      "setTime",
      "getTime",
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
      "getAssayStatus"
    ],
    "parameters":[
      "epoch_time",
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
    "properties":[
      "cameraTriggerChannel",
      "cameraTriggerFrequency",
      "whiteLightChannel",
      "whiteLightPower",
      "whiteLightStartTime",
      "whiteLightOnDuration",
      "redLightChannel",
      "redLightPower",
      "redLightFrequency",
      "redLightDutyCycle",
      "buzzerChannel",
      "buzzerPower",
      "buzzerOnDuration",
      "buzzerWaitMin",
      "buzzerWaitMax",
      "timeZoneOffset",
      "entrainmentDuration",
      "recoveryDuration",
      "testingDayDuration"
    ],
    "callbacks":[
      "runAssay",
      "testAssay",
      "stopAssay"
    ]
  }
}
```

## Example Usage

### Command Line

First get epoch time on the client computer using one of any number of
ways:

#### Web Page

<https://www.epochconverter.com/>

#### Bash

```shell
date +%s
```

Example: epoch_time = 1491943626

Set the time on the device:

```shell
setTime 1491943626
```

### Python

```python
import ModularClient

dev = ModularClient()

import time
epoch_time = int(time.time())

dev.setTime(epoch_time)
```

### Matlab

```matlab

```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
