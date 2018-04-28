### Description
This repository contains various basic examples for some of the concepts of
embedded software developing. The device is TM4C123GXL.

### How to Compile
#### Keil U-Vision 5.x
1. Create a new project
2. Choose TM4CGH6PM as the device
3. From **Manage Run-Time Environment** menu, choose **CMSIS->Core** and 
**Device->Startup"** software components.
4. Move the source file into the new project directory
5. From Keil U-Vision **Project Explorer**, add source file to project by double
clicking **Source Group 1** and choosing the source file in popup window.
6. Adding startup code will add device specific file named **"system_TM4C123.c".
** Under this file, change **CLOCK_SETUP** definition to **0** to prevent clock 
configuration done by startup code.
7. Build the source code and load the executable to the device.
