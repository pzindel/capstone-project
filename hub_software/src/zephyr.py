################################################################################
# File Name         : zephyr.py
# Description       : Contains Zephyr Python program is designed to run on a
#                     Raspberry PI as central hub software.
#
# Author            : Pierino Zindel
# Date              : November 01, 2022
# Last Revision     : N/A
# Version           : 0.1.0
################################################################################


# LIBRARIES
# Standard Libraries
import asyncio
import csv
import json
import logging
from logging.handlers import TimedRotatingFileHandler
import os
import struct
from time import time, localtime

# 3rd Party Libraries
from bleak import BleakScanner, BleakClient

# Custom Libraries
from version import __version__


# GLOBAL VARIABLES
# Set paths to all the config and data files
CURRENT_DIR = os.getcwd()
# Logging configuration filepath
LOG_CONFIG_FP = os.path.join(CURRENT_DIR, "config", "logging_config.json")
# BLE configuration filepath
BLE_CONFIG_FP = os.path.join(CURRENT_DIR, "config", "ble_config.json")
# Vents statuses and configurations filepath
VENT_CONFIG_FP = os.path.join(CURRENT_DIR, "config", "vent_status_config.json")
# CSV data log configuration filepath
CSV_CONFIG_FP = os.path.join(CURRENT_DIR, "config", "csv_config.json")
# CSV data log filepath
VENT_DATA_FP = os.path.join(CURRENT_DIR, "data", "vent_status_log.csv")


# FUNCTIONS
async def ble_read(address: str, uuid: str) -> bytearray:
    """
    Performs a read operation of the specified characteristic (UUID)
    of the specified device. Returns a bytearray of read data.

    Parameters
    ----------
    address : str
        The MAC address of the device to read from.
    uuid : str
        The UUID of the characteristic that should be read.

    Returns
    -------
    bytearray
        A
    """
    async with BleakClient(address) as client:
        data = await client.read_gatt_char(uuid)
    return data


async def ble_scan() -> list:
    """
    Returns a list of BLE devices detected.
    The list members are bleak.backends.device.BLEDevice objects which
    store the BLE device's MAC address, name, rssi, and other details.

    Returns
    -------
    list[BLEDevice]
        A list of bleak BLEDevices
    """
    return await BleakScanner.discover()


async def ble_write(address: str, uuid: str, data: bytearray) -> None:
    """
    Performs a write operation of the specified characteristic (UUID)
    of the specified device.

    Parameters
    ----------
    address : str
        The MAC address of the device to write to.
    uuid : str
        The UUID of the characteristic that should be written to.
    data : bytearray
        An array of data that should be written to the characteristic.
    """
    async with BleakClient(address) as client:
        response = await client.write_gatt_char(uuid, data)
    return


def csv_append_data(data_entry: list, delim: str) -> None:
    """
    A wrapper function for appending a row of data to a CSV file using
    the CSV writer.

    Parameters
    ----------
    data_entry : list
        The row of data to be appended where each member is an attribute.
    delim : str
        The delimiter character used by the CSV file.
    """
    with open(VENT_DATA_FP, "a", newline="", encoding="utf-8") as file:
        writer = csv.writer(file, delimiter=delim)
        writer.writerow(data_entry)
    return


def discover_vents(ble_config: dict, vent_config: dict) -> tuple:
    """
    Scans the area for active BLE devices and adds new vent devices
    to the list of known devices (in the config data). New config
    data is written to the JSON files.
    Returns updated versions of the configuration data.

    Parameters
    ----------
    ble_config : dict
        The configuration data for the BLE connection.
    vent_config : dict
        The configuration data for the vent network.

    Returns
    -------
    tuple(ble_config, vent_config)
        Updated versions of the config data.
    """
    # Get a list of all the discoverable devices
    detected_devices = asyncio.run(ble_scan())

    # Get a timestamp for the time of connection
    timestamp = int(time())

    # Set a variable to track new devices added
    new_devices = []

    # Process all discovered BLE devices
    for device in detected_devices:
        # Check if the device is a vent unit (has a whitelisted name)
        if device.name in ble_config["WHITELISTED_DEVICE_NAMES"]:
            # Check if it is a new device
            if device.name not in ble_config["WHITELISTED_DEVICE_ADDRESSES"]:
                # Add the device to list of know devices
                ble_config["WHITELISTED_DEVICE_ADDRESSES"].append(device.address)

            # Check if there is an existing config record for the device
            if device.address not in vent_config:
                # No existing config; add one
                vent_config[device.address] = {
                    "device_name": device.name,
                    "last_discover_utc": timestamp,
                    "last_data_exchange_utc": 0,
                    "last_read_rssi": device.rssi,
                    "vent_description": "UNINITIALIZED",
                    "vent_closed": True,
                    "last_temperature": 0,
                    "last_humidity": 0,
                    "last_battery_level": 0,
                    "last_led_state": 0,
                    "last_button_state": 0,
                    "last_temp_upper_threshold": 0,
                    "last_temp_lower_threshold": 0,
                }
            else:
                # Config exists; update the discovery time and rssi
                vent_config[device.address]["last_discover_utc"] = timestamp
                vent_config[device.address]["last_read_rssi"] = device.rssi

    # Save the new configuration data to the files
    save_config_file(ble_config, BLE_CONFIG_FP)
    save_config_file(vent_config, VENT_CONFIG_FP)

    return ble_config, vent_config


def load_config_files(*args: str) -> list:
    """
    Reads the list of provided config (JSON) files and returns a list of
    their contents (with preserved order).

    Parameters
    ----------
    *args : str
        A list of filepaths to json files to be loaded.

    Returns
    -------
    list[dict]
        A list of dictionaries containing configuration data.
    """
    files = []
    for filepath in args:
        with open(filepath, "r") as file:
            files.append(json.load(file))

    return files


def initialize_data_csv(config: dict) -> int:
    """
    Returns the ID value of the latest entry in the CSV data file. If the file doesn't exist,
    creates a file using the configuration data provided.

    Parameters
    ----------
    config : dict
        The configuration data for the CSV file storing the vent data.

    Returns
    -------
    int
        The entry ID of the latest entry in the CSV file (-1 if there are no existing entries).
    """
    # Track the ID of the last entry in the file
    last_id = -1
    id_attribute_name = "id"

    # Check if the file already exists
    if not os.path.isfile(VENT_DATA_FP):
        # The file doesn't exist, create a new open with appropriate header info
        with open(VENT_DATA_FP, "w", newline="", encoding="utf-8") as file:
            writer = csv.writer(file, delimiter=config["DELIMITER"])
            writer.writerow(config["HEADER"])

        # Update the last ID
        last_id = -1
    else:
        # The file does exist, retrieve the latest ID
        # Read the data on the file
        with open(VENT_DATA_FP, "r", newline="", encoding="utf-8") as file:
            reader = csv.reader(file, delimiter=config["DELIMITER"])
            file_contents = list(reader)

        # Check the header for the ID column
        header = [attribute.lower() for attribute in file_contents[0]]
        id_index = header.index(id_attribute_name)

        # Check the ID attribute of the last row
        if len(file_contents) == 1:
            last_id = -1
        else:
            last_id = int(file_contents[-1][id_index])

    return last_id


def manage_vents(ble_config: dict, vent_config: dict, csv_config: dict) -> None:
    """
    Processes each vent unit listed in the vent configuration record.
    Current state values are read from the vent unit and updated with values
    found in the config file.
    Values are then recorded in a CSV data file.

    Parameters
    ----------
    ble_config : dict
        The configuration data for the BLE connection.
    vent_config : dict
        The configuration data for the vent network.
    csv_config : dict
        The configuration data for the CSV file storing the vent data.
    """
    # Initialize the CSV file for saving vent data
    last_entry_id = initialize_data_csv(csv_config)

    # Process each vent device
    for device_address, device_data in vent_config.items():
        # Get the device's current open/close state
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_VENT_STATE"]))
        vent_closed_state = int.from_bytes(response, "big")

        # Get the device's current temperature
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_TEMPERATURE"]))
        temperature = struct.unpack("f", response)

        # Get the device's current humidity
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_HUMIDITY"]))
        humidity = struct.unpack("f", response)
        
        # Get the device's current temperature upper threshold
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_TEMP_UPPER_THRESHOLD"]))
        temp_upper_threshold = struct.unpack("f", response)
        
        # Get the device's current temperature lower threshold
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_TEMP_LOWER_THRESHOLD"]))
        temp_lower_threshold = struct.unpack("f", response)

        # Get the device's current Battery level
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_BATTERY"]))
        battery_level = int.from_bytes(response, "big")
        
        # Get the device's current LED state
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_LED_STATE"]))
        led_state = int.from_bytes(response, "big")
        
        # Get the device's current Button state
        response = asyncio.run(ble_read(device_address, ble_config["UUIDS"]["UUID_BUTTON_STATE"]))
        button_state = int.from_bytes(response, "big")

        # Set the new vent state based on current state and config data
        new_vent_closed_state = device_data["vent_closed"]
        vent_state_bytearray = bytearray(int(new_vent_closed_state))
        asyncio.run(
            ble_write(device_address, ble_config["UUIDS"]["UUID_VENT_STATE"], vent_state_bytearray)
        )
        
        # Set the new vent thresholds based on the current config data
        new_upper_threshold = device_data["temp_upper_threshold"]
        upper_threshold_bytearray = bytearray(struct.pack("f", new_upper_threshold))
        asyncio.run(
            ble_write(device_address, ble_config["UUIDS"]["UUID_TEMP_UPPER_THRESHOLD"], upper_threshold_bytearray)
        )
        
        new_lower_threshold = device_data["temp_lower_threshold"]
        lower_threshold_bytearray = bytearray(struct.pack("f", new_lower_threshold))
        asyncio.run(
            ble_write(device_address, ble_config["UUIDS"]["UUID_TEMP_LOWER_THRESHOLD"], lower_threshold_bytearray)
        )

        # Record the data in the CSV
        last_entry_id += 1
        timestamp = int(time())
        tz_offset = localtime().tm_gmtoff / 3600
        data_entry = [
            last_entry_id,
            timestamp,
            tz_offset,
            device_data["device_name"],
            device_address,
            device_data["last_read_rssi"],
            new_vent_closed_state,
            temperature,
            humidity,
            battery_level,
            led_state,
            button_state,
            temp_upper_threshold,
            temp_lower_threshold,
        ]
        csv_append_data(data_entry, csv_config["DELIMITER"])

        # Update the vent config data
        device_data["last_data_exchange_utc"] = timestamp
        device_data["vent_closed"] = new_vent_closed_state
        device_data["last_temperature"] = temperature
        device_data["last_humidity"] = humidity
        device_data["last_battery_level"] = battery_level
        device_data["last_led_state"] = led_state
        device_data["last_button_state"] = button_state
        device_data["temp_upper_threshold"] = new_upper_threshold
        device_data["temp_lower_threshold"] = new_lower_threshold

        vent_config[device_address] = device_data
        save_config_file(vent_config, VENT_CONFIG_FP)

    return


def save_config_file(config_data: dict, filepath: str) -> None:
    """
    Writes the provided config (JSON) data to the file at the
    specified filepath.

    Parameters
    ----------
    config_data : dict
        Configuration data to be saved.
    filepath : str
        The location and filename where the data should be written.
    """
    with open(filepath, "w") as file:
        json.dump(config_data, file, indent=4)
    return


def setup_logging(config: dict) -> logging.Logger:
    """
    Initializes, configures, and returns a Logger object that can be used
    to log the runtime progress of the program.

    Parameters
    ----------
    config : dict
        Configuration data for the TimedRotatingFileHandler and the Formatter.

    Returns
    -------
    logging.Logger
        A configured Logger object, from the standard logging module.
    """
    # Initialize the Logger
    logger = logging.getLogger(__name__)

    # Set the level of messages to be logged
    level = config["logging_level"]
    if level == "debug":
        logger.setLevel(logging.DEBUG)
    elif level == "info":
        logger.setLevel(logging.INFO)
    elif level == "warning":
        logger.setLevel(logging.WARNING)
    else:
        logger.setLevel(logging.ERROR)

    # Configure the logging file rotation
    handler = TimedRotatingFileHandler(
        filename=config["rotating_handler"].get("filename"),
        encoding=config["rotating_handler"].get("encoding"),
        when=config["rotating_handler"].get("rotation_time"),
        backupCount=config["rotating_handler"].get("num_of_backups"),
        utc=config["rotating_handler"].get("use_utc_time"),
    )

    # Configure the log format
    formatter = logging.Formatter(
        fmt=config["formatting"].get("message_format"),
        datefmt=config["formatting"].get("date_format"),
    )

    # Attach the configurations to the Logger
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    return logger


# MAIN FUNCTION
if __name__ == "__main__":
    # Load the config data
    log_config, ble_config, vent_config, csv_config = load_config_files(
        LOG_CONFIG_FP, BLE_CONFIG_FP, VENT_CONFIG_FP, CSV_CONFIG_FP
    )

    # Initialize the logger
    logger = setup_logging(log_config)

    # Discover new devices and add to list of existing
    ble_config, vent_config = discover_vents(ble_config, vent_config)

    # Connect to devices, RX statuses and TX updates
    manage_vents(ble_config, vent_config, csv_config)
