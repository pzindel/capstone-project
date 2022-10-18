I2C CMSIS-Driver Sample Code
============================

NOTE: If you use this sample application for your own purposes, follow the
licensing agreement specified in `Software Use Agreement - use and` 
`accept (ONIPLAW 08142020).pdf` in the root directory of the installed CMSIS-Pack.

Overview
--------
This sample project demonstrates how to send and receive data via the I2C interface
using interrupts. Since each device only has the I2C interface, two devices are 
required to run this application. 

1)  By default, the I2C interface is set to a clock of 100kHz. This can be changed
    via the `I2C_SPEED` define in `app.h`    

2)  Initially, both devices start in slave receive mode, waiting for data.
    When the `BUTTON_GPIO` is pulled low, that device aborts the slave 
    receive mode, switches to master mode and begins a transmission. The message 
    by default is `onsemi I2C`. The master then waits for 
    a message from the slave.
   
3)  The second device will receive the message in slave mode. When it receives 
    the message correctly, it will toggle the `APP_I2C_EVENT_GPIO` 6 times 
    with a period of 250ms. The slave will then send the same message back to 
    the master.

4)  When the master receives the message correctly, it also toggle its 
    `APP_I2C_EVENT_GPIO`. The master will then revert to slave mode and 
    wait for the next button press or message. 

5)  If either master or slave detect an error in transmission on the bus, 
    the `APP_I2C_EVENT_GPIO` will toggle 10 times with a period of 50ms. 
    If the message sent was corrupted, the `APP_I2C_EVENT_GPIO` will toggle 
    20 times with a period of 50ms. All toggling of the `APP_I2C_EVENT_GPIO` 
    can be configured by the user to suit their purposes. 

6)  If no LEDs and pushbutton are available for the `APP_I2C_EVENT_GPIO` 
    and the `BUTTON_GPIO`, an oscilloscope can measure the switching of 
    the `APP_I2C_EVENT_GPIO` and a jumper can be used to short 
    the `BUTTON_GPIO` to ground. The I2C exchange will trigger on a falling 
    edge on the `BUTTON_GPIO`.  The value of `GREEN_LED` 
    is defined in RTE\Device\{device_name}\RTE_Device.h

Hardware Requirements
---------------------
Connect like pins on each device to allow I2C communication between devices. 
Below is the default configuration. The I2C pins can be configured in 
`RTE_Device.h`. The `APP_I2C_EVENT_GPIO` and the `BUTTON_GPIO` can 
be configured in `app.h`.

       Master        Slave
        SCL    <->    SCL
        SDA    <->    SDA

Importing a Project
-------------------
To import the sample code into your IDE workspace, refer to the 
*Getting Started Guide* for your IDE for more information.

Verification
------------
To verify that the application is working correctly, load the sample code on 
the devices and connect the I2C interface, as detailed in the 
*Hardware Requirements* section. 

Before running the program, place an LED on the `APP_I2C_EVENT_GPIO` on 
one or both of the devices or connect an oscilloscope to that pin. Now, the 
application can be run on both devices.

Pull the `BUTTON_GPIO` to ground, this should result in toggling of the 
`APP_I2C_EVENT_GPIO` pin on both devices. 

Alternatively, the application can be verified via a debug session. If a 
breakpoint is placed where the received data is compared to I2C\_TX\_DATA in 
`app.c` (which is preceded by the comment: 
`/* Toggle GPIO if received data matches I2C_TX_DATA */`) and 
the program is run normally and the `BUTTON_GPIO` is pulled to ground, this
breakpoint should be hit on both devices.
 
The source code exists in `app.c` and `app.h`. 

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
