# arduino-advanced-bike-computer
Advanced DIY Bike computer with color TFT screen

It is based on Atmega328 (Arduino Pro Mini). The intent was to use bunch of sensors like temperature, 3axis accelerometer, then have control of servo motors, Altimeter, LiPo charger. Also included MicroSD slot and of course TFT LCD.

Lots of work in programming is already done but seems that chosen microcontroller is becoming too weak for such amount of functions. Every task requires decent amount of flash and SRAM – especially Color LCD library and FAT file system. I think, second version of bike computer will be equipped with more powerful STM32 microcontroller.

It uses direct external sensor (reed switch) and magnet fixed on wheel.

Features:
- Bicycle gear indicator
- Speed | Distance | Max Speed | Avg. speed | Today Max Speed | Today Avg. speed | Today Avg. distance
- Elevation