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

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["SleepAssayController"],
    "functions":[
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
    "parameters":[
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
    "properties":[
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
    "callbacks":[
      "runAssay",
      "testAssay",
      "stopAssay"
    ]
  }
}
```

## API Verbose

[API Verbose](./api.json)

## Example Usage

### Command Line

Open terminal, set baud rate to 115200 and set to append newline to
each request sent to the device.

First, set all properties to defaults.

request:

```shell
setAllPropertiesToDefaults
```

Then get epoch time on the client computer using one of any number of
ways.

Web Page:

<https://www.epochconverter.com/>

Bash:

```shell
date +%s
```

Example: epoch_time = 1496156562

Set the time on the device:

request:

```shell
setTime 1496156562
```

Check the date and time make sure this matches the local date and
time.

request:

```shell
now
```

response:

```json
{
  "id":"now",
  "result":{
    "year":2017,
    "month":5,
    "day":30,
    "hour":11,
    "minute":3,
    "second":4
  }
}
```

If it is off by a few hours, the time zone may need to be adjusted.

request:

```shell
getPropertyValues
```

response:

```json
{
  "id":"getpropertyvalues",
  "result":{
    "cameraTriggerChannel":0,
    "cameraTriggerFrequency":0.500000,
    "whiteLightChannel":1,
    "whiteLightIndicatorChannel":5,
    "whiteLightPower":50,
    "whiteLightStartTime":9,
    "whiteLightOnDuration":12,
    "redLightChannel":2,
    "redLightIndicatorChannel":6,
    "redLightPower":50,
    "redLightFrequency":10,
    "redLightDutyCycle":50,
    "buzzerChannel":3,
    "buzzerIndicatorChannel":7,
    "buzzerPower":50,
    "buzzerOnDurationMin":1,
    "buzzerOnDurationMax":4,
    "buzzerWaitMin":1,
    "buzzerWaitMax":3,
    "timeZoneOffset":-4,
    "entrainmentDuration":2,
    "recoveryDuration":2,
    "testingDayDuration":24
  }
}
```

request:

```shell
getAssayDuration
```

response:

```json
{
  "id":"getAssayDuration",
  "result":4
}
```

request:

```shell
entrainmentDuration setValue 1
```

response:

```json
{
  "id":"entrainmentDuration",
  "result":1
}
```

request:

```shell
recoveryDuration setValue 1
```

response:

```json
{
  "id":"recoveryDuration",
  "result":1
}
```

request:

```shell
getAssayDuration
```

response:

```json
{
  "id":"getAssayDuration",
  "result":2
}
```

request:

```shell
getExperimentInfo
```

response:

```json
{
  "id":"getExperimentInfo",
  "result":[]
}
```

request:

```shell
addExperimentDay
```

response:

```json
{
  "id":"addExperimentDay",
  "result":0
}
```

request:

```shell
getExperimentInfo
```

response:

```json
{
  "id":"getExperimentInfo",
  "result":[
    {
      "white_light":true,
      "red_light":false,
      "red_light_delay":0.000000,
      "red_light_duration":0.000000,
      "buzzer":false,
      "buzzer_delay":0.000000,
      "buzzer_duration":0.000000
    }
  ]
}
```

request:

```shell
setExperimentDayRedLight 0 true 0 12
```

response:

```json
{
  "id":"setExperimentDayRedLight",
  "result":{
    "white_light":true,
    "red_light":true,
    "red_light_delay":0.000000,
    "red_light_duration":12.000000,
    "buzzer":false,
    "buzzer_delay":0.000000,
    "buzzer_duration":0.000000
  }
}
```

request:

```shell
addExperimentDayCopy 0
```

response:

```json
{
  "id":"addExperimentDayCopy",
  "result":1
}
```

request:

```shell
setExperimentDayWhiteLight 1 false
```

response:

```json
{
  "id":"setExperimentDayWhiteLight",
  "result":{
    "white_light":false,
    "red_light":false,
    "red_light_delay":0.000000,
    "red_light_duration":0.000000,
    "buzzer":false,
    "buzzer_delay":0.000000,
    "buzzer_duration":0.000000
  }
}
```

request:

```shell
setExperimentDayBuzzer 1 true 3 12
```

response:

```json
{
  "id":"setExperimentDayBuzzer",
  "result":{
    "white_light":false,
    "red_light":true,
    "red_light_delay":0.000000,
    "red_light_duration":12.000000,
    "buzzer":true,
    "buzzer_delay":3.000000,
    "buzzer_duration":12.000000
  }
}
```

request:

```shell
getExperimentInfo
```

response:

```json
{
  "id":"getExperimentInfo",
  "result":[
    {
      "white_light":true,
      "red_light":true,
      "red_light_delay":0.000000,
      "red_light_duration":12.000000,
      "buzzer":false,
      "buzzer_delay":0.000000,
      "buzzer_duration":0.000000
    },
    {
      "white_light":false,
      "red_light":true,
      "red_light_delay":0.000000,
      "red_light_duration":12.000000,
      "buzzer":true,
      "buzzer_delay":3.000000,
      "buzzer_duration":12.000000
    }
  ]
}
```

request:

```shell
getExperimentDuration
```

response:

```json
{
  "id":"getExperimentDuration",
  "result":2
}
```

request:

```shell
getAssayDuration
```

response:

```json
{
  "id":"getAssayDuration",
  "result":4
}
```

request:

```shell
testAssay
```

response:

```json
{
  "id":"testAssay",
  "result":null
}
```

request:

```shell
getAssayStatus
```

response:

```json
{
  "id":"getAssayStatus",
  "result":{
    "time_now":1496156712,
    "date_time_now":{
      "year":2017,
      "month":5,
      "day":30,
      "hour":11,
      "minute":5,
      "second":12
    },
    "assay_day":0.500000,
    "phase":"ENTRAINMENT",
    "phase_day":0.500000,
    "white_light_on":true,
    "red_light_pulsing":false,
    "buzzing_possible":false,
    "buzzing":false,
    "testing":true
  }
}
```

request:

```shell
runAssay
```

response:

```json
{
  "id":"runAssay",
  "result":null
}
```

request:

```shell
getAssayEnd
```

response:

```json
{
  "id":"getAssayEnd",
  "result":{
    "year":2017,
    "month":6,
    "day":3,
    "hour":9,
    "minute":0,
    "second":0
  }
}
```

### Python

```python
from modular_client import ModularClient
import time

dev = ModularClient()
dev.set_all_properties_to_defaults()
dev.set_time(int(time.time()))
time_zone_offset = -time.timezone/(60*60)
t = time.time()
if time.localtime(t).tm_isdst and time.daylight:
    time_zone_offset = -time.altzone/(60*60)
dev.time_zone_offset('setValue',time_zone_offset)
-4
dev.now()
{'day': 31, 'hour': 13, 'minute': 51, 'month': 5, 'second': 11, 'year': 2017}
# check to make sure this matches the local date and time
dev.get_property_values()
{'buzzerChannel': 3,
 'buzzerIndicatorChannel': 7,
 'buzzerOnDurationMax': 4,
 'buzzerOnDurationMin': 1,
 'buzzerPower': 50,
 'buzzerWaitMax': 3,
 'buzzerWaitMin': 1,
 'cameraTriggerChannel': 0,
 'cameraTriggerFrequency': 0.5,
 'entrainmentDuration': 2,
 'recoveryDuration': 2,
 'redLightChannel': 2,
 'redLightDutyCycle': 50,
 'redLightFrequency': 10,
 'redLightIndicatorChannel': 6,
 'redLightPower': 50,
 'testingDayDuration': 24,
 'timeZoneOffset': -4,
 'whiteLightChannel': 1,
 'whiteLightIndicatorChannel': 5,
 'whiteLightOnDuration': 12,
 'whiteLightPower': 50,
 'whiteLightStartTime': 9}
dev.get_assay_duration()
4
dev.entrainment_duration('setValue',1)
1
dev.recovery_duration('setValue',1)
1
dev.get_assay_duration()
2
dev.get_experiment_info()
[]
dev.add_experiment_day()
0
dev.get_experiment_info()
[{'buzzer': False,
  'buzzer_delay': 0.0,
  'buzzer_duration': 0.0,
  'red_light': False,
  'red_light_delay': 0.0,
  'red_light_duration': 0.0,
  'white_light': True}]
dev.set_experiment_day_red_light(0,True,0,12)
{'buzzer': False,
 'buzzer_delay': 0.0,
 'buzzer_duration': 0.0,
 'red_light': True,
 'red_light_delay': 0.0,
 'red_light_duration': 12.0,
 'white_light': True}
dev.add_experiment_day_copy(0)
1
dev.set_experiment_day_white_light(1,False)
{'buzzer': False,
 'buzzer_delay': 0.0,
 'buzzer_duration': 0.0,
 'red_light': True,
 'red_light_delay': 0.0,
 'red_light_duration': 12.0,
 'white_light': False}
dev.set_experiment_day_buzzer(1,True,3,12)
{'buzzer': True,
 'buzzer_delay': 3.0,
 'buzzer_duration': 12.0,
 'red_light': True,
 'red_light_delay': 0.0,
 'red_light_duration': 12.0,
 'white_light': False}
dev.get_experiment_info()
[{'buzzer': False,
  'buzzer_delay': 0.0,
  'buzzer_duration': 0.0,
  'red_light': True,
  'red_light_delay': 0.0,
  'red_light_duration': 12.0,
  'white_light': True},
 {'buzzer': True,
  'buzzer_delay': 3.0,
  'buzzer_duration': 12.0,
  'red_light': True,
  'red_light_delay': 0.0,
  'red_light_duration': 12.0,
  'white_light': False}]
dev.get_experiment_duration()
2
dev.get_assay_duration()
4
dev.test_assay()
dev.get_assay_status()
{'assay_day': 0.458333,
 'buzzing': False,
 'buzzing_possible': False,
 'date_time_now': {'day': 31,
  'hour': 13,
  'minute': 53,
  'month': 5,
  'second': 48,
  'year': 2017},
 'phase': 'ENTRAINMENT',
 'phase_day': 0.458333,
 'red_light_pulsing': False,
 'testing': True,
 'time_now': 1496253228,
 'white_light_on': True}
dev.run_assay()
dev.get_assay_end()
{'day': 4, 'hour': 9, 'minute': 0, 'month': 6, 'second': 0, 'year': 2017}
```


### Matlab

```matlab
getAvailableComPorts()
serial_port = 'COM9' % example
dev = ModularClient(serial_port);
dev.open();
dev.setAllPropertiesToDefaults();
% look up time zone offset for your location
% taking into account daylight savings time
% if necessary
% e.g.
% U.S. Eastern = -5
% U.S. Eastern daylight savings = -4
time_zone_offset = -4;
dev.timeZoneOffset('setValue',time_zone_offset);
dev.setTime(etime(clock,[1970,1,1,0,0,0]));
n = dev.now();
t = clock;
dev.adjustTime((t(4) - n.hour)*60*60);
dev.now()
% check to make sure this matches the local date and time
dev.getPropertyValues()
dev.getAssayDuration()
    4
dev.entrainmentDuration('setValue',1);
dev.recoveryDuration('setValue',1);
dev.getAssayDuration()
     2
dev.getExperimentInfo()
   Empty cell array: 0-by-1
dev.addExperimentDay()
     0
info = dev.getExperimentInfo();
info{1}
dev.setExperimentDayRedLight(0,1,0,12)
dev.addExperimentDayCopy(0)
dev.setExperimentDayWhiteLight(1,0)
dev.setExperimentDayBuzzer(1,1,3,12)
info = dev.getExperimentInfo();
info{2}
dev.getExperimentDuration();
dev.getAssayDuration();
dev.testAssay();
dev.getAssayStatus()
dev.runAssay();
dev.getAssayEnd();
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
