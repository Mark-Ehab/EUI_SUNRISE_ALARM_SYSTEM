/*==================================================================
 *     __  __      _     __          __
 *    |  \/  |    | |    \ \        / /
 *    | \  / | ___| |_ __ \ \  /\  / /_ _ _ __ ___
 *    | |\/| |/ _ \ __/ _` \ \/  \/ / _` | '__/ _ \
 *    | |  | |  __/ || (_| |\  /\  / (_| | | |  __/
 *    |_|  |_|\___|\__\__,_| \/  \/ \__,_|_|  \___|
 *==================================================================
SWC: App.h
Date: 8/28/2023
Authors: MetaWare LLC
         Mahmoud Sayed Mahmoud Helmy (1285)
         Mohamed Mahmoud Masoud (200)
         Mark Ehab Tawfik (201)
         Hazzem Mohamed Ezzeldin (1297)
         Yousef Khaled Ahmed (558)
================================================================
 Description: This header file contains the declarations and
 function prototypes for the main application logic and functions
 responsible for controlling alarms and user interactions.
================================================================
  FILE NAME: App.h
================================================================*/


#ifndef APP_H_
#define APP_H_


#include <util/delay.h>
#include "App_Cfg.h"
#include "../RTE/rte.h"

/* Initial value for alarms */
#define AlarmInitialValue 0

/* Maximum number of alarms that can be set */
#define MaximumAlarms 4

/* Position of tens digit for minutes */
#define MINUTES_TENS 4

/* Position of ones digit for minutes */
#define MINUTES_ONES 3

/* Position of tens digit for seconds */
#define SECONDS_TENS 2

/* Position of ones digit for seconds */
#define SECONDS_ONES 1

/* Preloaded value for Timer0 */
#define TIMER0_PRELOADED_VALUE 0

/* Compare match value for Timer1 */
#define TIMER1_COMPARE_MATCH_VALUE 15625

/* Maximum value for tens digit of minutes */
#define MAX_MINUTES_TENS 6

/* Maximum duty cycle for LED dimming */
#define MAX_DUTY_CYCLE 99

/* Minimum duty cycle for LED dimming */
#define MIN_DUTY_CYCLE 1

/* Maximum overflow count for dimming control */
#define MAX_OVERFLOW_COUNT 10

/* Choice character for setting an alarm */
#define SET_ALARM_CHOICE '+'

/* Choice character for canceling an alarm */
#define CANCEL_ALARM_CHOICE '-'

/* Choice character for listing alarms */
#define ALARM_LIST_CHOICE '*'

/* Choice character for closing/exiting */
#define CLOSE '/'

/* Return value indicating continuation */
#define CONTINUE 0

#define CANCELLED 0
#define CONFIRMED 1

/* Enumeration of alarm IDs */
typedef enum {
    ALARM_0, ALARM_1, ALARM_2, ALARM_3
} alarms_id;

/* Structure for alarm configuration */
typedef struct {
    uint8 flag;
    int alarmDigits[4];
    int secCnt;
} Alarm_config;

/*==================================================================*/
/**
 * @brief Initializes the application by initializing various drivers and components.
 *
 * This function initializes the LCD, keypad, LDR, buzzer, LED, and timers.
 */
void App_Init(void);

/*==================================================================*/
/**
 * @brief Displays the main menu options on the LCD.
 *
 * This function displays the main menu options on the LCD screen.
 */
void App_mainMenu(void);

/*==================================================================*/
/**
 * @brief Searches for the first available alarm slot to set the time.
 *
 * @param[out] availableAlarmBuffer A pointer to store the available alarm slot.
 *
 * This function searches for the first available alarm slot and stores its ID in the provided buffer.
 */
void App_firstAvailableAlarm(uint8* availableAlarmBuffer);

/*==================================================================*/
/**
 * @brief Sets the time for a new alarm.
 *
 * This function guides the user to set the desired time for a new alarm.
 */
STATUS App_setAlarm(void);

/*==================================================================*/
/**
 * @brief Lists the set alarms on the LCD.
 *
 * This function displays the list of set alarms on the LCD screen.
 */
STATUS App_listAlarm(void);

/*==================================================================*/
/**
 * @brief Cancels a specific alarm.
 *
 * This function allows the user to cancel a specific alarm and clears its settings.
 */
STATUS App_cancelAlarm(void);

/*==================================================================*/
/**
 * @brief Manages the main application flow.
 *
 * This function displays the main menu, handles user choices, and executes corresponding actions.
 */
void App(void);

/*==================================================================*/
/**
 * @brief Displays a welcome screen with team and project information.
 *
 * This function displays a welcome screen with team names, class information, and a welcome message.
 */
void App_welcomeScreen(void);

/*==================================================================*/
void LEDdimmingOverFlow(void);
void LEDdimmingCompareMatch(void);
void Interrupt_function(void);
STATUS alarmAction(void);
STATUS WakeUpCalculator(void);

#endif /* APP_H_ */
