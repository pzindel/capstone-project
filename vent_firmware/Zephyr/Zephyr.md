Bluetooth Low Energy Peripheral Server Sample Code
===========

NOTE: If you use this sample application for your own purposes, follow the
licensing agreement specified in `Software Use Agreement - use and` 
`accept (ONIPLAW 08142020).pdf` in the root directory of the installed CMSIS-Pack.

Overview
--------
This Bluetooth Low Energy application demonstrates a peripheral device with two 
standard services (Battery Service server and Device Information Service server)
and two application-defined services (Customer Service 1 and Customer Service 2 servers).

The application allows you to configure the Bluetooth Low Energy address type (public or private) and the 
location from which to read the Bluetooth Low Energy address. 
*	By default, the private address type is selected (`GAPM_ADDRESS_TYPE` is configured as 
		`GAPM_CFG_ADDR_PRIVATE` in `app.h`), and the application uses `APP_BLE_PRIVATE_ADDR' 
		defined in `app.h` as the device private address.
*	The Bluetooth Low Energy address type can be re-configured to public by changing `GAPM_ADDRESS_TYPE`
		from `GAPM_CFG_ADDR_PRIVATE` to `GAPM_CFG_ADDR_PUBLIC` in `app.h`.
*	When the public address type is selected, the application reads the public address from a 
		location defined by `APP_BLE_PUBLIC_ADDR_LOC` in `app.h`. By default, `APP_BLE_PUBLIC_ADDR_LOC` 
		is configured to `BLE_PUBLIC_ADDR_LOC_MNVR`, which is a location in MNVR. However, any other valid 
		locations can be used as needed.
       
Key operations performed by the application:

1. Generates battery service, device information service, and custom services
2. Performs undirected connectable advertising
3. By default, up to four simultaneous connections are supported. This can be configured in 
`app.h` (the Bluetooth Low Energy stack currently supports 10 connections).
4. Any central device can:  
    * Scan, connect, pair/bond/encrypt (legacy or secure bond)
    * Perform service discovery
    * Read characteristic values from battery, device information and custom services
5. Host privacy can be enabled in the application by changing `GAPM_OWN_ADDR_TYPE` from 
   `GAPM_STATIC_ADDR` to `GAPM_GEN_RSLV_ADDR` in `app.h`.
6. The application sends periodic notifications of the battery level and custom service 
   characteristics to the connected peer devices (clients).
7. The Bluetooth Low Energy physical data rate is 1 Mbps by default. If different rates are
   desirable, enable physical data rate update by defining `APP_PHY_UPDATE_REQ` and define the
   desired rates in `APP_PREFERRED_PHY_RX` and `APP_PREFERRED_PHY_TX` in `app.h` 

**Custom Service 1:** This custom service on the peripheral includes four
                characteristics (i.e. `RX_VALUE`, `TX_VALUE`,`RX_VALUE_LONG`
                and `TX_VALUE_LONG`). The `TX_VALUE` characteristic can only be
                read after secure connection with encryption is successfully established.
                The `RX_VALUE` characteristic sends a notification with an 
                incremental value every 10 seconds, if the notification is enabled. 
                The value written on the attribute with the `TX_VALUE_LONG` 
                characteristic name is inverted and written back to `RX_VALUE_LONG` 
                by the custom service. This is handled by the `CUSTOMSS_MsgHandler` 
                function in `app_customss.c`. For example, if you write 0x01 to 
                the `TX_VALUE_LONG` characteristic, you can then read 
                the inverted value (i.e. 0xFE) using the `RX_VALUE_LONG` characteristic.

**Custom Service 2:** This custom service on the peripheral includes three 
                characteristics (i.e. `TEMPERATURE_VALUE`, `LED_STATE` and `BUTTON_STATE`).
                The `TEMPERATURE_VALUE` characteristic sends a notification with an encoded 
                IEEE-11073 32-bit float temperature value every 10 seconds.
                A value of 0x00 or 0x01 written on the attribute with the `LED_STATE` characteristic
                name turns the LED connected with `LED_STATE_GPIO` off or on, respectively. 
                In addition, each time a falling edge on GPIO0 is detected (i.e., a button press), 
                the `BUTTON_STATE` characteristic sends a notification with a value toggled
                between 0x00 and 0x01 to the peer connected device.

**Battery Service:** This service database is configured for a single battery 
                 instance. The application provides a callback function to read the battery level. 

The application notifies clients about the battery level on two occasions:

**Periodically:** The notification timeout is configured using the 
              `BASS_NotifyOnTimeout(TIMER_SETTING_S(BATT_UPDATE_TIMEOUT_S))` function
              in the `app_init.c`. The macro `TIMER_SETTING_S(value)` in `app.c` converts the value
              in seconds to milliseconds. It is used to indicate that the value has a unit of 
              seconds. The `BATT_UPDATE_TIMEOUT_S` is defined in `app_bass.h` and is set to a 
              value of 15 seconds.

**On battery level change:** The application monitors the battery level periodically and sends
                         a notification when a change is detected. The monitoring timeout is configured 
                         using the `BASS_NotifyOnBattLevelChange(TIMER_SETTING_S(BATT_CHANGE_TIMEOUT_S))` 
                         function in the `app_init.c`. The macro `TIMER_SETTING_S(value)` in `app.c` converts
                         the value in seconds to milliseconds. It is used to indicate that value has a unit of 
                         seconds. The `BATT_CHANGE_TIMEOUT_S` is defined in `app_bass.h` and is set to a 
                         value of 5 seconds.

The message subscription mechanism allows the application and services to 
subscribe and receive callback notifications based on the Kernel message ID 
or task ID. This allows each module of the application to be independently 
implemented in its own files. The subscription is performed using the 
`MsgHandler_Add()` function. The application subscribes to receive GAPM and 
GAPC events. The services subscribe to receive Kernel events in 
their initialization function (see `BASS_Initialize()` in `ble_bass.c` for an 
example). The application event handlers are implemented in `app_msg_handler.c`.

**Advertisement Extension:** The application demonstrates advertisement extension capability on Long Range (coded
                             PHY). This can be enabled by setting `ADV_EXTENSION` to 1 in `app.h`. If pairing 
							 this with a central device, also set `ADV_EXTENSION` to 1 in `app.h` of the
                             `ble_central_client` sample application.

**Read Permission with Secure Connection:**
In this sample application, Read Permission of the `TX_VALUE` characteristic in Custom Service 1 is set to Secure
Connection. In a central device, in order to read the value of the `TX_VALUE` characteristic, make sure that both
LESEC and MITM are enabled and IO Capabilities is set to `DISPLAY & YESNO`, then do pairing/bonding.

**Clearing Bond List:**
The bond list (stored in the data flash area) can be cleared by connecting GPIO0 to ground for at least five 
seconds (this can be achieved by pressing and holding SW1 pushbutton on the EVB). After five seconds, if the bond
list is successfully cleared, GPIO8 toggles with a 100-millisecond interval between each toggle (the green LED on
the EVB blinks). The toggling/blinking stops once GPIO0 is disconnected from the ground (SW1 pushbutton on the 
EVB is released).

Logging Capability
------------------
This application uses the swmTace library to log information over UART using the RX pin (GPIO5) and the TX pin 
(GPIO6).

Application Files
------------------
`app.h / app.c`: application definitions and the `main()` function  
`app_init.h / app_init.c`: device, libraries and application initialization   
`app_msg_handler.h / app_msg_handler.c`: Bluetooth Low Energy event handlers  
`app_customss.h / app_customss.c`: application-defined Bluetooth Low Energy 
                                   custom service server                    
`app_temperature_sensor.h / app_temperature_sensor.c`: Internal temperature
                                                     sensor utility class

Understanding the Source Code
-----------------------------
The source code is marked with comments. Some of them are numbered "Step 1", "Step 2", 
etc. Follow the sequence of numbered steps (and the log output over UART) to understand 
the application in detail.

The basic sequence of operations and event messages exchanged between the 
application and the Bluetooth stack is presented below: 

  APP <--> Bluetooth Low Energy Stack
  
  Startup
  
      step 1 --->  GAPM_ResetCmd() - app.c
      step 2 <---  GAPM_CMP_EVT / GAPM_RESET
      --->  GAPM_SetDevConfigCmd() - app_msg_handler.c
      step 3 <---  GAPM_CMP_EVT / GAPM_SET_DEV_CONFIG
      --->  BASS_ProfileTaskAddCmd() - app_msg_handler.c
      step 4.a <---  GAPM_PROFILE_ADDED_IND / TASK_ID_BASS
      ----> DISS_ProfileTaskAddCmd() - app_msg_handler.c
      step 4.b <---  GAPM_PROFILE_ADDED_IND / TASK_ID_DISS
      ----> GATTM_AddAttributeDatabase() / CUST_SVC0 - app_msg_handler.c
      step 5.a <---  GATTM_ADD_SVC_RSP / CUST_SVC0 
      --->  GATTM_AddAttributeDatabase() / CUST_SVC1 - app_msg_handler.c
      step 5.b <---  GATTM_ADD_SVC_RSP / CUST_SVC1
      --->  GAPM_ActivityCreateAdvCmd() - app_msg_handler.c
      step 6 <---  GAPM_ACTIVITY_CREATED_IND
      --->  GAPM_SetAdvDataCmd() - app_msg_handler.c
      step 7 <---  GAPM_CMP_EVT / GAPM_SET_ADV_DATA 
      --->  GAPM_AdvActivityStart() - app_msg_handler.c

  Connection request / parameters update request / device info request
  
      step 8 <--- GAPC_CONNECTION_REQ_IND
      ---> GAPM_ResolvAddrCmd() - app_msg_handler.c
      ---> GAPC_ConnectionCfm() - app_msg_handler.c
      <--- GAPC_PARAM_UPDATE_REQ_IND
      ---> GAPC_ParamUpdateCfm() - app_msg_handler.c
      <--- GAPC_GET_DEV_INFO_REQ_IND
      ---> GAPC_GetDevInfoCfm() - app_msg_handler.c

  Pairing / Bonding request
  
      <--- GAPC_BOND_REQ_IND / GAPC_PAIRING_REQ
      ----> GAPC_BondCfm() - app_msg_handler.c
      <--- GAPC_BOND_REQ_IND / GAPC_LTK_EXCH
      ----> GAPC_BondCfm() - app_msg_handler.c
      <--- GAPC_BOND_REQ_IND / GAPC_IRK_EXCH
      ----> GAPC_BondCfm() - app_msg_handler.c
      <--- GAPC_BOND_REQ_IND / GAPC_CSRK_EXCH
      ----> GAPC_BondCfm() - app_msg_handler.c
      <--- GAPC_BOND_IND 
      ----> 

  Encrypt request
  
      <--- GAPC_ENCRYPT_REQ_IND
      ---> GAPC_EncryptCfm() - app_msg_handler.c
      <--- GAPC_ENCRYPT_IND 
      ---->

  Disconnection
  
      <--- GAPC_DISCONNECT_IND
      ---> GAPM_StartAdvertiseCmd() - app_msg_handler.c

Bluetooth Low Energy Abstraction
----------------
This application takes advantage of the Bluetooth Low Energy Abstraction layer, on top of 
the Bluetooth Low Energy stack. This provides an extra layer of simplicity and 
modularization to your firmware design, so that you can focus on your specific application.


Hardware Requirements
---------------------
This application can be executed on any RSL15 Evaluation and Development Board 
with no external connections required.

Importing a Project
-------------------
To import the sample code into your IDE workspace, refer to the 
*Getting Started Guide* for your IDE for more information.

Verification
------------
To verify that this application is functioning correctly, use RSL15 or another 
third-party central device application to establish a connection and execute 
pairing and bonding functionality. In addition to establishing a connection, 
this application can be used to read/write characteristics and receive 
notifications.

To show how an application can send notifications, the battery service is 
configured to send the battery level every 6 seconds or less (if a battery level 
change is detected in VBAT). The custom service also sends an incrementing 
value of the first attribute every 6 seconds.

Alternatively, you can observe the behavior of the LED on the RSL15 Evaluation 
and Development Board (DIO10). The LED behavior is controlled by the 
`APP_LED_Timeout_Handler` function (in `app_msg_handler.c`) and can be one of the 
following:

    - If the device has not started advertising, the LED is off.
    - If the device is advertising but it has not connected to any peer, the 
      LED blinks every 200 ms.
    - If the device is connected to fewer than `APP_NB_PEERS` peers, the LED 
      blinks every 2 seconds according to the number of connected peers (i.e., 
      once if one peer is connected, twice if two peers are connected, etc.).
    - If the device is connected to `APP_NB_PEERS` peers, the LED stays on steadily 
      and the application is no longer advertising.


Debug Catch Mode 
---------------- 

If the device goes into Low Power Mode or resets quickly, it might be difficult to connect 
the device to a debugger. You can hold the `DEBUG_CATCH_GPIO` low to enter Debug Catch Mode, 
which holds the program execution in a `while` loop to make it easier to connect to the debugger. 

To make use of Debug Catch Mode: 

1. Connect the `DEBUG_CATCH_GPIO` to ground (press and hold the SW1 pushbutton on the 
   evaluation board). 
2. Press the RESET button (this restarts the application, then enters Debug Catch Mode, 
   which holds program execution in a `while` loop). 
3. Connect the debugger so that you can re-program or erase the flash. Disconnect `DEBUG_CATCH_GPIO` 
   from ground (releasing SW1 pushbutton on the evaluation board).

***
  Copyright (c) 2022 Semiconductor Components Industries, LLC (d/b/a
  onsemi), All Rights Reserved