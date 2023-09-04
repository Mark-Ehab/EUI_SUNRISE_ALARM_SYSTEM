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
#define ALARM_INITIAL_VALUE 0

/* Maximum number of alarms that can be set */
#define MAXIMUM_ALARMS 4

/* Position of tens digit for minutes */
#define TENS_OF_SEC_OR_MIN 5

/* Position of ones digit for minutes */
#define ONES_OF_SEC_OR_MIN  9

/* Pre-loaded value for Timer0 */
#define TIMER0_PRELOADED_VALUE 0

/* Compare match value for Timer1 */
#define TIMER1_COMPARE_MATCH_VALUE 15625

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

/* Return value indicating cancelled operation*/
#define CANCELLED 0

/* Return value indicating exit operation*/
#define EXIT       2

/* Return value indicating confirmed operation*/
#define CONFIRMED 1

/* Return value indicating error in operation*/
#define ERR_STATE   8

/*The minimum value to read from LDR*/
#define LDR_MIN     0

/* Return value indicating return to main menu operation*/
#define RETURN_TO_MAIN_MENU 0

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

/* Display strings for alarm equations */
#define DISPLAY_EQUATION_1 " 10 + 2 * 4 ="
#define DISPLAY_EQUATION_2 " 21 - 5 * 4 ="
#define DISPLAY_EQUATION_3 " 80 + 1 * 4 - 5 ="
#define DISPLAY_EQUATION_4 " 10 - 4 * 2 ="

/* Number of digits in alarm puzzle answers */
#define NUM_OF_DIGITS_1 1
#define NUM_OF_DIGITS_2 2

/* Enumeration of alarm IDs */
typedef enum
{
    ALARM_0, ALARM_1, ALARM_2, ALARM_3
} alarms_id;

/* Structure for alarm configuration */
typedef struct
{
    uint8 flag;
    int alarmDigits[4];
    int secCnt;
} Alarm_config;

/*==================================================================*/
/**
 * @brief Initializes the application by initializing various drivers
 *  and components.
 *
 * This function initializes the LCD, keypad, LDR, buzzer, LED, and timers.
 */
void App_Init(void);

/*==================================================================*/
/**
 * @brief Manages the main application flow.
 *
 * This function displays the main menu, handles user choices, and executes
 * corresponding actions.
 */
void MainApp(void);

/*==================================================================*/
/**
 * @brief Sets the time for a new alarm.
 *
 * This function guides the user to set the desired time for a new alarm.
 */
uint8 App_setAlarm(void);

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
 * @brief Displays a welcome screen with team and project information.
 *
 * This function displays a welcome screen with team names, class information,
 * and a welcome message.
 */
void App_welcomeScreen(void);

/*==================================================================*/
/**
 * @brief Contains the logic to be executed in Timer0 overflow routine .
 *
 * This function controls the duty cycle of a software PWM that changes every Timer0
 * overflow interrupt.
 */
void LEDdimmingOverFlow(void);

/*==================================================================*/
/**
 * @brief Contains the logic to be executed in Timer0 compare match routine .
 *
 * This function toggles multiple LEDs every Timer0 compare match interrupt.
 */
void LEDdimmingCompareMatch(void);

/*==================================================================*/
/**
 * @brief Contains the routine for
 Timer1 compare match callback function for channel A.
 *
 * This function checks for alarm seconds count and sets multiple flags
 * associated with firing the alarms when the seconds count reaches zero.
 */
void ISRcallBackFunction(void);

/*==================================================================*/
/**
 * @brief Contains all of the logic to be executed in the event of a fired alarm
 * and its execution depends on the flags set by the Interrupt_function.
 *
 * This function turns on the buzzer, dims multiple LEDS and interacts with the
 * user through LDR and a puzzle. It turns off the alarm and associated components
 * in the case of correct input from the user.
 */
STATUS alarmAction(void);

/*==================================================================*/
/**
 * @brief Contains the logic of a puzzle required to be solved
 * in the event of a fired alarm.
 *
 * This function contains the puzzle to be solved when the associated alarm
 * fires in the form of a mathematical equation to make sure the
 * person is fully awake.
 */
STATUS WakeUpCalculator(void);

/*==================================================================*/

#endif /* APP_H_ */
