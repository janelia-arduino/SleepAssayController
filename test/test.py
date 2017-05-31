# coding: utf-8
from modular_client import ModularClient
import time
dev = ModularClient()
dev.set_all_properties_to_defaults()
dev.set_time(int(time.time()))
dev.entrainment_duration('setValue',1)
dev.recovery_duration('setValue',1)
dev.add_experiment_day()
dev.set_experiment_day_red_light(0,True,0,12)
dev.add_experiment_day_copy(0)
dev.set_experiment_day_white_light(1,False)
dev.set_experiment_day_buzzer(1,True,3,12)
