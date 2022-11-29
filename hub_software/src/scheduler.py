#!/usr/bin/env python3

import schedule
import time
import json
import os
import zephyr


# GLOBAL VARIABLES
# Set paths to all the config and data files
CURRENT_DIR = os.getcwd()
# BLE configuration filepath
BLE_CONFIG_FP = os.path.join(CURRENT_DIR, "config", "ble_config.json")
# Vents statuses and configurations filepath
VENT_CONFIG_FP = os.path.join(CURRENT_DIR, "config", "vent_status_config.json")

def vent_control():
    address = ble_config['WHITELISTED_DEVICE_ADDRESSES']

    # Can check some conditions to control the state of the vent,
    # Let's say too hot or cold
    last_temp = vent_config[address[0]]['last_temperature']
    print(last_temp)
    if (last_temp >= 30):
        vent_config[address[0]]['vent_closed'] = True
    else:
        vent_config[address[0]]['vent_closed'] = False

    zephyr.save_config_file(vent_config, VENT_CONFIG_FP)

    zephyr.main()
    
# def job():
    # print("I'm working...")


if __name__ == "__main__":
    # Load the config data
    f_vent_config = open(VENT_CONFIG_FP)
    f_ble_config = open(BLE_CONFIG_FP)

    vent_config = json.load(f_vent_config)
    ble_config = json.load(f_ble_config)

    # vent_control()

    # with open(VENT_CONFIG_FP, 'w') as file:
    #     json.dump(vent_config, file, indent=4)

    # job()
    schedule.every(5).minute.do(vent_control)

    while True:
        schedule.run_pending()
        time.sleep(10)

    f_vent_config.close()
    f_ble_config.close()

