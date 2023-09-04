/*==================================================================
 *     __  __      _     __          __
 *    |  \/  |    | |    \ \        / /
 *    | \  / | ___| |_ __ \ \  /\  / /_ _ _ __ ___
 *    | |\/| |/ _ \ __/ _` \ \/  \/ / _` | '__/ _ \
 *    | |  | |  __/ || (_| |\  /\  / (_| | | |  __/
 *    |_|  |_|\___|\__\__,_| \/  \/ \__,_|_|  \___|
 *==================================================================
SWC: mainApplication.h
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
  FILE NAME: mainApplication.h
================================================================*/


#ifndef APP_H_
#define APP_H_


#include <util/delay.h>
#include "Application_Cfg.h"
#include "../RTE/rte.h"


/* Initial value for alarms */
#define ALARM_INTIAL_VALUE 0

/* Maximum number of alarms that can be set */
#define MAXIMUM_ALARMS 4

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
#define SET_ALARM_CHOICE '+'   /* Symbol to set an alarm */

/* Choice character for canceling an alarm */
#define CANCEL_ALARM_CHOICE '-'   /* Symbol to cancel an alarm */

/* Choice character for listing alarms */
#define ALARM_LIST_CHOICE '*'   /* Symbol to list alarms */

/* Choice character for closing/exiting */
#define CLOSE '/'   /* Symbol to close or exit */

/* Return value indicating continuation */
#define CONTINUE 0

/* Return values for alarm actions */
#define CANCELLED 0   /* Alarm action: Cancelled */
#define CONFIRMED 1   /* Alarm action: Confirmed */

/* Define macros for alarm setting options */
#define CONFIRM_ALARM_SETTING  1   /* Alarm setting option: Confirm */
#define GO_BACK                0   /* Alarm setting option: Go back */
#define EXIT_ALARM_SETTING     2   /* Alarm setting option: Exit alarm setting */
#define MAX_ALARMS             MAXIMUM_ALARMS   /* Maximum number of alarms */
#define ALARM_ERROR			   8   /* Alarm error status */

/* Alarm equation IDs */
#define ALARM_EQUATION_1 0
#define ALARM_EQUATION_2 1
#define ALARM_EQUATION_3 2
#define ALARM_EQUATION_4 3

/* Alarm puzzle equations */
#define CALC_PUZZLE_1 (10 + 2 * 4)
#define CALC_PUZZLE_2 (21 - 5 * 4)
#define CALC_PUZZLE_3 (80 + 1 * 4 - 5)
#define CALC_PUZZLE_4 (10 - 4 * 2)

/* Number of digits in alarm puzzle answers */
#define NUM_OF_DIGITS_1 1
#define NUM_OF_DIGITS_2 2

/* Display strings for alarm equations */
#define DISPLAY_EQUATION_1 " 10 + 2 * 4 ="
#define DISPLAY_EQUATION_2 " 21 - 5 * 4 ="
#define DISPLAY_EQUATION_3 " 80 + 1 * 4 - 5 ="
#define DISPLAY_EQUATION_4 " 10 - 4 * 2 ="

/* Keypad value boundaries */
#define MAX_KEYPAD_VALUE 9
#define MIN_KEYPAD_VALUE 0

/* Enumeration of alarm IDs */
typedef enum {
	ALARM_0, ALARM_1, ALARM_2, ALARM_3
} alarms_id;

/* Structure for alarm configuration */
typedef struct {
	uint8 flag;
	int alarmDigits[4];
	int secondsCounter;
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
void mainApplication(void);

/*==================================================================*/
/**
 * @brief Displays a welcome screen with team and project information.
 *
 * This function displays a welcome screen with team names, class information, and a welcome message.
 */
void App_welcomeScreen(void);

/*==================================================================*/
/**
 * @brief Performs LED dimming using overflow counts.
 *
 * This function incrementally increases and decreases the LED duty cycle by
 * modifying the Timer0 settings.
 */
void LEDdimmingOverFlow(void);

/*==================================================================*/
/**
 * @brief Performs LED dimming using compare match.
 *
 * This function toggles the state of multiple LEDs for LED dimming using compare match.
 */
void LEDdimmingCompareMatch(void);

/*==================================================================*/
/**
 * @brief Callback function for the interrupt service routine.
 *
 * This function is a callback for the interrupt service routine.
 */
void ISRcallBackFunction(void);

/*==================================================================*/
/**
 * @brief Executes the action when an alarm fires.
 *
 * This function handles the action to be taken when an alarm fires,
 * including displaying messages and turning off the alarm.
 *
 * @return The status of the alarm action.
 */
STATUS alarmAction(void);

/*==================================================================*/
/**
 * @brief Manages the wake-up calculator and puzzle solving.
 *
 * This function guides the user to solve a puzzle as part of the wake-up process.
 *
 * @return The status of the wake-up calculator.
 */
STATUS WakeUpCalculator(void);

void displayCountdown(uint8 alarmId);

#endif /* APP_H_ */
