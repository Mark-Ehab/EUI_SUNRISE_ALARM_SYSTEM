<font color="#012061">**Sunrise Alarm Clock Project**</font>

This repository contains the source code and documentation for the Sunrise Alarm Clock project developed by MetaWare LLC.

## Introduction

The Sunrise Alarm Clock is a microcontroller-based project that simulates a natural sunrise to wake you up gradually and gently. The project utilizes various components, including an LCD display, a keypad for user interaction, an alarm functionality, a buzzer for alarm sounds, and an LDR (Light Dependent Resistor) to detect ambient light levels. The project was developed by the team at MetaWare LLC, consisting of:

![image](https://github.com/Mark-Ehab/EUI_SUNRISE_ALARM_SYSTEM/assets/52659572/a2179bbe-338e-414f-b08c-673b5cdf9644)

## Layer Architecture 
![image](https://github.com/Mark-Ehab/EUI_SUNRISE_ALARM_SYSTEM/assets/52659572/3acb0392-6fdc-4d2b-9a77-4360b85bc207)

## Features

- **Gradual Sunrise Simulation:** The alarm clock uses a gradual increase in light intensity (LED) to mimic a natural sunrise, allowing for a more peaceful and gentle wake-up experience.
- **Customizable Alarms:** Users can set alarms with personalized wake-up times and alarm sounds (buzzer) to suit their preferences.
- **Alarm Cancellation:** Unwanted alarms can be easily canceled using the intuitive keypad interface.
- **Ambient Light Detection:** The LDR detects ambient light levels, allowing the system to adjust the sunrise simulation and alarm behavior based on the environment.
- **Buzzer Activation:** The buzzer is activated when an alarm times out, providing an audible alert to the user.
- 
## Additional Feature: Solve Math Equation to Close Alarm

In this alarm, an interesting feature has been implemented that requires users to solve a math equation before they can close the alarm. This feature adds an element of cognitive engagement, ensuring that users are fully awake and alert when turning off the alarm.

### How It Works

1. When the alarm rings, users are prompted to solve a math equation displayed on the screen.
2. Users need to enter the correct answer using the keypad to successfully turn off the alarm.
3. If the entered answer is correct, the alarm is silenced, and the application returns to the main menu.
4. If the entered answer is incorrect, the alarm continues to ring until the correct answer is provided.

### Note

we make sure to keep the math equations relatively simple and solvable within a short time frame.

## Code Overview

### Global Variables

- `g_alarm_cnt`: Keeps track of the number of alarms used.
- `g_fired_alarm`: Represents the alarm that has fired.
- `alarms`: An array of `Alarm_config` structures containing alarm configurations.

### Functions

- `actionToBeTaken()`: Displays a message corresponding to the fired alarm.
- `interrupt_function()`: Handles alarm firing based on the configured time.
- `App_init()`: Initializes LCD and keypad.
- `App_mainMenu()`: Displays the main menu options.
- `App_firstAvailableAlarm()`: Identifies the first available alarm for setting.
- `App_setAlarm()`: Sets a new alarm by accepting user input.
- `App_listAlarm()`: Lists all active alarms.
- `App_cancelAlarm()`: Cancels a selected alarm.
- `App_main()`: Implements the main logic of the application.

## Functionalities

### Main Menu

The main menu provides three options:

- **Set Alarm:** Allows users to set a new alarm.
- **Cancel Alarm:** Lets users cancel an existing alarm.
- **Alarm List:** Displays a list of all active alarms.

### Set Alarm

Users can set a new alarm with minutes and seconds:

1. Users choose whether to continue or return to the main menu.
2. If continued, users input minutes and seconds.
3. The application searches for an available alarm slot.
4. The alarm is set with the specified time.

### Cancel Alarm

Users can cancel an existing alarm:

1. Users choose whether to continue or return to the main menu.
2. If continued, a list of active alarms is displayed.
3. Users select the alarm to cancel.
4. The chosen alarm is removed from the list.

### Alarm List

Displays a list of active alarms:

1. Users choose whether to view the list or return to the main menu.
2. If viewed, all active alarms are listed.
## Simple Simulation 
![image](https://github.com/Mark-Ehab/EUI_SUNRISE_ALARM_SYSTEM/assets/52659572/55b653bb-4a3b-480b-8a14-547906814fc0)


Developed with ❤️ by the MetaWare LLC team.
