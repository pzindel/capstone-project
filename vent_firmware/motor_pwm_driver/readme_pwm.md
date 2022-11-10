PWM Driver Sample Code
========================

NOTE: If you use this sample application for your own purposes, follow the
licensing agreement specified in `Software Use Agreement - use and` 
`accept (ONIPLAW 08142020).pdf` in the root directory of the installed CMSIS-Pack.

Overview
--------
This sample project demonstrates an application that:

1.  Uses PWM[0] to output an 80 kHz signal on GPIO2 and PWM[1] to output an 80 kHz signal on GPIO3.
	The start of PWM[1] is delayed by 50 clock cycles with respect to PWM[0], with use off the offset setting.
    The PWM block is clocked by a divided RFCLK by default (8 MHz).

Do note that all offsets are offset from channel 0, and the period of that channel must match channel 0
for the offset feature to work. 

Dithering requires channel 0 to be enabled to function correctly.

The source code exists in `app.c`, with additional `app.h` and `RTE_device.h`
header files included.

Hardware Requirements
---------------------
This application can be executed on an Evaluation and Development Board.

Importing a Project
-------------------
To import the sample code into your IDE workspace, refer to the 
*Getting Started Guide* for your IDE for more information.

Verification
------------
To verify that the application is working correctly, connect the board to the power supply. 
After the board is powered up, Build the sample and flash it on to the Evaluation and Development Board.
GPIO2 and GPIO3 will output an 80 kHz signal, and the signals will be offset by 50 clock cycles.

1.  The PWM channels can be configured and basic default settings can be altered in the "RTE_Device.h header file.
	Open the file with CMSIS Configuration Wizard to view the GUI.
2.  The API provides functions for offset, dithering, and clock configuration settings. 

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
