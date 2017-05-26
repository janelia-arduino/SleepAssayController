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

Example: epoch_time = 1493391042

Set the time on the device:

request:

```shell
setTime 1493391042
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
    "month":4,
    "day":28,
    "hour":10,
    "minute":50,
    "second":46
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
  "id":"getPropertyValues",
  "result":{
    "serialNumber":0,
    "powerMax":[
      100,
      50,
      50,
      50,
      100,
      100,
      100,
      100
    ],
    "cameraTriggerChannel":0,
    "cameraTriggerFrequency":0.500000,
    "whiteLightChannel":1,
    "whiteLightPower":50,
    "whiteLightStartTime":9,
    "whiteLightOnDuration":12,
    "redLightChannel":2,
    "redLightPower":50,
    "redLightFrequency":10,
    "redLightDutyCycle":50,
    "buzzerChannel":3,
    "buzzerPower":50,
    "buzzerOnDuration":1,
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
setExperimentDayWhiteLight 0 false
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
setExperimentDayRedLight 0 true 0 12
```

response:

```json
{
  "id":"setExperimentDayRedLight",
  "result":{
    "white_light":false,
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
getExperimentDuration
```

response:

```json
{
  "id":"getExperimentDuration",
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
  "result":3
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
    "time_now":1493392140,
    "date_time_now":{
      "year":2017,
      "month":4,
      "day":28,
      "hour":11,
      "minute":9,
      "second":0
    },
    "assay_day":1.208333,
    "phase":"EXPERIMENT",
    "phase_day":0.208333,
    "white_light_on":false,
    "red_light_pulsing":true,
    "buzzing":false,
    "testing":true
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
{'day': 12, 'hour': 11, 'minute': 30, 'month': 4, 'second': 43, 'year': 2017}
# check to make sure this matches the local date and time
dev.get_property_values()
{'buzzerChannel': 3,
 'buzzerOnDuration': 1,
 'buzzerPower': 50,
 'buzzerWaitMax': 3,
 'buzzerWaitMin': 1,
 'cameraTriggerChannel': 0,
 'cameraTriggerFrequency': 0.5,
 'entrainmentDuration': 2,
 'powerMax': [100, 50, 50, 50, 100, 100, 100, 100],
 'recoveryDuration': 2,
 'redLightChannel': 2,
 'redLightDutyCycle': 50,
 'redLightFrequency': 10,
 'redLightPower': 50,
 'serialNumber': 0,
 'testingDayDuration': 24,
 'timeZoneOffset': -4,
 'whiteLightChannel': 1,
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
dev.set_experiment_day_red_light(0,True,12,4)
{'buzzer': False,
 'buzzer_delay': 0.0,
 'buzzer_duration': 0.0,
 'red_light': True,
 'red_light_delay': 12.0,
 'red_light_duration': 4.0,
 'white_light': True}
dev.get_experiment_duration()
1
dev.get_assay_duration()
3
dev.add_experiment_day_copies(0,2)
[1, 2]
dev.get_experiment_duration()
3
dev.get_assay_duration()
5
dev.set_experiment_day_buzzer(1,True,4,3)
{'buzzer': True,
 'buzzer_delay': 4.0,
 'buzzer_duration': 3.0,
 'red_light': True,
 'red_light_delay': 12.0,
 'red_light_duration': 4.0,
 'white_light': True}
dev.get_experiment_info()
[{'buzzer': False,
  'buzzer_delay': 0.0,
  'buzzer_duration': 0.0,
  'red_light': True,
  'red_light_delay': 12.0,
  'red_light_duration': 4.0,
  'white_light': True},
 {'buzzer': True,
  'buzzer_delay': 4.0,
  'buzzer_duration': 3.0,
  'red_light': True,
  'red_light_delay': 12.0,
  'red_light_duration': 4.0,
  'white_light': True},
 {'buzzer': False,
  'buzzer_delay': 0.0,
  'buzzer_duration': 0.0,
  'red_light': True,
  'red_light_delay': 12.0,
  'red_light_duration': 4.0,
  'white_light': True}]
dev.test_assay()
dev.get_assay_status()
{'assay_day': 0.583333,
 'buzzing': False,
 'date_time_now': {'day': 12,
  'hour': 13,
  'minute': 45,
  'month': 4,
  'second': 50,
  'year': 2017},
 'phase': 'ENTRAINMENT',
 'phase_day': 0.583333,
 'red_light_pulsing': False,
 'testing': True,
 'time_now': 1492019150,
 'white_light_on': False}
dev.get_assay_status()
{'assay_day': 1.541667,
 'buzzing': False,
 'date_time_now': {'day': 12,
  'hour': 13,
  'minute': 46,
  'month': 4,
  'second': 13,
  'year': 2017},
 'phase': 'EXPERIMENT',
 'phase_day': 0.541667,
 'red_light_pulsing': True,
 'testing': True,
 'time_now': 1492019173,
 'white_light_on': False}
dev.get_assay_status()
{'assay_day': 5.0,
 'buzzing': False,
 'date_time_now': {'day': 12,
  'hour': 13,
  'minute': 47,
  'month': 4,
  'second': 54,
  'year': 2017},
 'phase': 'ASSAY_FINISHED',
 'phase_day': 1.0,
 'red_light_pulsing': False,
 'testing': True,
 'time_now': 1492019274,
 'white_light_on': False}
dev.run_assay()
dev.get_assay_end()
{'day': 17, 'hour': 9, 'minute': 0, 'month': 4, 'second': 0, 'year': 2017}
dev.get_assay_status()
{'assay_day': 0.367361,
 'buzzing': False,
 'date_time_now': {'day': 12,
  'hour': 13,
  'minute': 49,
  'month': 4,
  'second': 0,
  'year': 2017},
 'phase': 'ENTRAINMENT',
 'phase_day': 0.367361,
 'red_light_pulsing': False,
 'testing': False,
 'time_now': 1492019340,
 'white_light_on': True}
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
      year: 2017
     month: 4
       day: 12
      hour: 10
    minute: 44
    second: 27
% check to make sure this matches the local date and time
dev.getPropertyValues()
              serialNumber: 0
                  powerMax: [100 50 50 50 100 100 100 100]
      cameraTriggerChannel: 0
    cameraTriggerFrequency: 0.5000
         whiteLightChannel: 1
           whiteLightPower: 50
       whiteLightStartTime: 9
      whiteLightOnDuration: 12
           redLightChannel: 2
             redLightPower: 50
         redLightFrequency: 10
         redLightDutyCycle: 50
             buzzerChannel: 3
               buzzerPower: 50
          buzzerOnDuration: 1
             buzzerWaitMin: 1
             buzzerWaitMax: 3
            timeZoneOffset: -4
       entrainmentDuration: 2
          recoveryDuration: 2
        testingDayDuration: 24
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
           white_light: 1
             red_light: 0
       red_light_delay: 0
    red_light_duration: 0
                buzzer: 0
          buzzer_delay: 0
       buzzer_duration: 0
dev.setExperimentDayRedLight(0,1,12,4)
           white_light: 1
             red_light: 1
       red_light_delay: 12.0000
    red_light_duration: 4
                buzzer: 0
          buzzer_delay: 0
       buzzer_duration: 0
dev.getExperimentDuration()
     1
dev.getAssayDuration()
     3
dev.addExperimentDayCopies(0,2)
     1     2
dev.getExperimentDuration()
     3
dev.getAssayDuration()
     5
dev.setExperimentDayBuzzer(1,1,4,3)
           white_light: 1
             red_light: 1
       red_light_delay: 12.0000
    red_light_duration: 4
                buzzer: 1
          buzzer_delay: 4
       buzzer_duration: 3
info = dev.getExperimentInfo();
info{2}
           white_light: 1
             red_light: 1
       red_light_delay: 12.0000
    red_light_duration: 4
                buzzer: 1
          buzzer_delay: 4
       buzzer_duration: 3
dev.testAssay();
dev.getAssayStatus()
             time_now: 1.4920e+09
        date_time_now: [1x1 struct]
            assay_day: 0.7500
                phase: 'ENTRAINMENT'
            phase_day: 0.7500
       white_light_on: 0
    red_light_pulsing: 0
              buzzing: 0
              testing: 1
dev.getAssayStatus()
             time_now: 1.4920e+09
        date_time_now: [1x1 struct]
            assay_day: 1.5417
                phase: 'EXPERIMENT'
            phase_day: 0.5417
       white_light_on: 0
    red_light_pulsing: 1
              buzzing: 0
              testing: 1
dev.getAssayStatus()
             time_now: 1.4920e+09
        date_time_now: [1x1 struct]
            assay_day: 5
                phase: 'ASSAY_FINISHED'
            phase_day: 1
       white_light_on: 0
    red_light_pulsing: 0
              buzzing: 0
              testing: 1
dev.runAssay();
dev.getAssayEnd()
      year: 2017
     month: 4
       day: 17
      hour: 9
    minute: 0
    second: 0
dev.getAssayStatus()
             time_now: 1.4920e+09
        date_time_now: [1x1 struct]
            assay_day: 0.4853
                phase: 'ENTRAINMENT'
            phase_day: 0.4853
       white_light_on: 1
    red_light_pulsing: 0
              buzzing: 0
              testing: 0
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
