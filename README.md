# Sunrise Alarm Clock Project

This repository contains the source code and documentation for the Sunrise Alarm Clock project developed by MetaWare LLC.

## Introduction

The Sunrise Alarm Clock is a microcontroller-based project that simulates a natural sunrise to wake you up gradually and gently. The project utilizes various components, including an LCD display, a keypad for user interaction, an alarm functionality, a buzzer for alarm sounds, and an LDR (Light Dependent Resistor) to detect ambient light levels. The project was developed by the team at MetaWare LLC, consisting of:

| Name                           | ID    |
|--------------------------------|-------|
| Mahmoud Sayed Mahmoud Helmy    | 1285  |
| Mohamed Mahmoud Masoud         | 200   |
| Mark Ehab Tawfik               | 201   |
| Hazzem Mohamed Ezzeldin        | 1297  |
| Yousef Khaled Ahmed            | 558   |


## Features

- **Gradual Sunrise Simulation:** The alarm clock uses a gradual increase in light intensity (LED) to mimic a natural sunrise, allowing for a more peaceful and gentle wake-up experience.
- **Customizable Alarms:** Users can set alarms with personalized wake-up times and alarm sounds (buzzer) to suit their preferences.
- **Alarm Cancellation:** Unwanted alarms can be easily canceled using the intuitive keypad interface.
- **Ambient Light Detection:** The LDR detects ambient light levels, allowing the system to adjust the sunrise simulation and alarm behavior based on the environment.
- **Buzzer Activation:** The buzzer is activated when an alarm times out, providing an audible alert to the user.

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


Developed with ❤️ by the MetaWare LLC team.
