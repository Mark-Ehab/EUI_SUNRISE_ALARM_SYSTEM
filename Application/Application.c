/*================================================================================
			   _____                          _
			  / ____|                        (_)
			 | (___    _   _   _ __    _ __   _   ___    ___
			  \___ \  | | | | | '_ \  | '__| | | / __|  / _ \
			  ____) | | |_| | | | | | | |    | | \__ \ |  __/
			 |_____/   \__,_| |_| |_| |_|    |_| |___/  \___|

             _                                 _____   _                  _
     /\     | |                               / ____| | |                | |
    /  \    | |   __ _   _ __   _ __ ___     | |      | |   ___     ___  | | __
   / /\ \   | |  / _` | | '__| | '_ ` _ \    | |      | |  / _ \   / __| | |/ /
  / ____ \  | | | (_| | | |    | | | | | |   | |____  | | | (_) | | (__  |   <
 /_/    \_\ |_|  \__,_| |_|    |_| |_| |_|    \_____| |_|  \___/   \___| |_|\_\

					 __  __      _     __          __
					|  \/  |    | |    \ \        / /
					| \  / | ___| |_ __ \ \  /\  / /_ _ _ __ ___
					| |\/| |/ _ \ __/ _` \ \/  \/ / _` | '__/ _ \
					| |  | |  __/ || (_| |\  /\  / (_| | | |  __/
					|_|  |_|\___|\__\__,_| \/  \/ \__,_|_|  \___|
/*=================================================================================
	SWC : Application.c
	Date: 8/28/2023
	Authors: MetaWare LLC
			Mahmoud Sayed Mahmoud Helmy (1285)
			Mohamed Mahmoud Masoud (200)
			Mark Ehab Tawfik (201)
			Hazzem Mohamed Ezzeldin (1297)
			Yousef Khaled Ahmed (558)
/*==============================================================================================*/
/*	 Description: This file contains the main application logic and
/*	 functions for controlling alarmsBuffer and user interactions.
/*==============================================================================================*/
/*								FILE NAME: Application.c
/*==============================================================================================*/

#include "Application.h"       /* Include the header file for this application */
#include <stdlib.h>			   /* Include the standard library for various functions */

/*==============================================================================================*/
/*									Global Variables
/*==============================================================================================*/
/*
 * @details
 * This section defines global variables used throughout the Sunrise Alarm Clock
 * application. These variables store information such as alarm counts, timer overflows,
 * readings from LDR, alarm status, LED dimming states,
 *
 * These variables are accessible and modifiable from various parts of the code and
 * play a crucial role in the functionality of the application.
 */
uint8 g_alarm_cnt = 1;						/**< Counter for how many alarmsBuffer are being used */
uint8 g_timer0Overflow_cnt = 0;				/**< Counter for Timer0 overflows */
volatile uint16 g_readingLDR = 0;			/**< Store the reading from an LDR (Light Dependent Resistor) */
volatile uint8 g_alarmHasFired = FALSE;     /**< Flag to indicate a fired alarm */
uint8 numOfDigits = 0;                      /**< Number of digits used for displaying numbers */
uint8 Decreasing = 0;                       /**< Flag indicating decreasing state in LED dimming */
uint8 Increasing = 1;                       /**< Flag indicating increasing state in LED dimming */
uint8 digitsArray[4];                       /**< Array to hold set time of alarm */
volatile uint8 g_NowFiredAlarm;             /**< Variable to indicate which alarm has fired */


/*==============================================================================================*/
/*                         Alarm Configuration and Messages
/*==============================================================================================*/
/* @Description:
 * This section of code defines the configuration for multiple alarmsBuffer and
 * associates messages with each alarm.
 * The 'alarmsBuffer' Array:
 * - 'alarmsBuffer' is an array of 'Alarm_config' structures, where each structure
 *   represents an alarm with its specific settings.
 * - The array size is defined as 'MAXIMUM_ALARMS,' allowing configuration for a
 *   maximum number of alarmsBuffer.
 *
 * The 'alarmMessages' Array:
 * - 'alarmMessages' is an array of constant strings, where each string
 *   corresponds to a specific alarm (index-based).
 * - These messages describe the notification or action associated with each
 *   alarm when it triggers.
/*==============================================================================================*/
Alarm_config alarmsBuffer[MAXIMUM_ALARMS] =
{
 {0 , {ALARM_INTIAL_VALUE}, 0}, /* alarm 0 */
 {0 , {ALARM_INTIAL_VALUE}, 0}, /* alarm 1 */
 {0 , {ALARM_INTIAL_VALUE}, 0}, /* alarm 2 */
 {0 , {ALARM_INTIAL_VALUE}, 0}  /* alarm 3 */
};

/* Array of alarm messages for each alarm */
const char* alarmMessages[] = {
                               "alarm 0 time is out",
                               "alarm 1 time is out",
                               "alarm 2 time is out",
                               "alarm 3 time is out"
};


/**
/*==============================================================================================
 *				                    System Initialization
/*==============================================================================================
/**
 * @brief Initialize the Sunrise Alarm Clock application.
 *
 * @details
 * The `App_Init` function is responsible for initializing various components and
 * resources required for the proper functioning of the Sunrise Alarm Clock application.
 * This includes initializing the LCD, keypad, LDR (Light Dependent Resistor), buzzer,
 * LED, and timers (Timer0 and Timer1).
 *
 * Additionally, this function sets up timer behaviors, such as preload values and
 * callback functions for Timer0 and Timer1, enabling global interrupts, and displaying
 * the welcome screen to provide a pleasant user experience upon application startup.
 *
/*==============================================================================================*/
void App_Init(void)
{   
/* Initialize LCD */
RTE_LCD_init();

/* Initialize Keypad */
RTE_KEYPAD_init();

/* Initialize LDR */
RTE_LDR_vidLDRInit();

/* Initialize Buzzer */
RTE_Buzzer_Init();

/* Initialize LED */
RTE_LED_Init_All();

/* Initialize Timer0 */
RTE_TIMER0_vidInit();

/* Timer0 Behavior Functions */

/* Set the preload value for Timer0 */
RTE_TIMER0_vidSetPreloadValue(TIMER0_PRELOADED_VALUE);

/* Set the callback function for Timer0 Compare Match */
RTE_TIMER0_u8SetCompareMatchCallback(LEDdimmingCompareMatch);

/* Set the callback function for Timer0 Overflow */
RTE_TIMER0_u8SetOverflowCallback(LEDdimmingOverFlow);

/* Initialize Timer1 */
RTE_TIMER1_vidInit();

/* Set Timer1 Compare Match Value for Channel A */
RTE_TIMER1_vidSetCompareMatchAValue(TIMER1_COMPARE_MATCH_VALUE);

/* Set Timer1 Compare Match Callback Function for Channel A */
RTE_TIMER1_uint8SetCompareMatchACallback(ISRcallBackFunction);

/* Enable Global Interrupt Enable */
RTE_GlobalInterrupt_enable();

/* Start Timer1 */
RTE_TIMER1_vidStart();

/* Display the welcome screen */
App_welcomeScreen();
}
/*==============================================================================================*/
/*==============================================================================================
									Main Application Loop
/*==============================================================================================*/
/**
 * @brief Main loop of the Sunrise Alarm Clock application.
 *
 * @details
 * The `mainApplication` function serves as the heart of the Sunrise Alarm Clock application.
 * Below is a detailed breakdown of its functionality:
 *
 * 1. **Alarm Display**: When an active alarm is present (as indicated by the `g_alarmHasFired`
 *    flag), this function displays the remaining time for the alarm to trigger. It does so by
 *    decrementing the alarm time and updating the LCD screen in real-time. This visual countdown
 *    enhances user awareness of the impending alarm event.
 *
 * 2. **Alarm Activation Handling**: The function continuously monitors the `g_alarmHasFired` flag.
 *    When an alarm is activated (the flag becomes `TRUE`), it triggers the `alarmAction` function,
 *    which executes actions associated with alarm events. These actions may include activating
 *    external devices, playing sounds, or displaying specific messages.
 *
 * 3. **Main Menu Display**: The main menu of the Sunrise Alarm Clock application is presented on
 *    the LCD screen. It offers three user options: setting an alarm, canceling an existing alarm,
 *    or viewing the list of configured alarms. This menu is continuously displayed to allow
 *    user interaction.
 *
 * 4. **User Input Handling**: The function uses the `RTE_KEYPAD_getPressedKey` function to detect
 *    user input from the keypad. It waits for valid input corresponding to the available menu
 *    options (Set Alarm, Cancel Alarm, or Alarm List) before proceeding.
 *
 * 5. **Action Execution**: Based on the user's choice, the function calls the appropriate sub-functions
 *    to perform specific actions:
 *    - `App_setAlarm`: Initiates the process of setting a new alarm.
 *    - `App_cancelAlarm`: Allows the user to cancel an active alarm.
 *    - `App_listAlarm`: Displays a list of configured alarms.
 *
 * This continuous loop ensures that the application consistently updates the LCD screen, responds
 * to alarm events and user input, and seamlessly guides the user through various functionalities.
 * It forms the core of the Sunrise Alarm Clock application, providing an intuitive and efficient
 * user experience.
 *
 * @see g_alarmHasFired
 * @see alarmAction
 * @see RTE_KEYPAD_getPressedKey
 * @see App_setAlarm
 * @see App_cancelAlarm
 * @see App_listAlarm
 */
void mainApplication()
{
	/* Enter the main application loop. */
	while (TRUE)
	{
		/* Check if an alarm has been triggered. */
		if (TRUE == g_alarmHasFired)
		{
			/* Reset the alarm flag. */
			g_alarmHasFired = FALSE;

			/* Perform actions associated with alarm activation. */
			alarmAction();
		}

		/* Variable to store the user's main menu choice. */
		uint8 mainMenuChoice = FALSE;

		/* State variable for menu navigation. */
		uint8 state = 0;

		/* Clear the LCD screen to prepare for new content. */
		RTE_LCD_clearScreen();

		/* Display the first menu option: Set Alarm. */
		RTE_LCD_moveCursor(LCD_ROW_0, LCD_COLUMN_0);
		RTE_LCD_displayString("+ Set Alarm   |");

		/* Display the second menu option: Cancel Alarm. */
		RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
		RTE_LCD_displayString("- Cancel Alarm|");

		/* Display the third menu option: Alarm List. */
		RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_0);
		RTE_LCD_displayString("* Alarm List  |");

		/* Create a blank line at the bottom of the screen. */
		RTE_LCD_moveCursor(LCD_ROW_3, LCD_COLUMN_0);
		RTE_LCD_displayString("              |");

		/* Check if an alarm has been triggered again. */
		if (TRUE == g_alarmHasFired)
		{
			/* Reset the alarm flag. */
			g_alarmHasFired = FALSE;

			/* Perform actions associated with alarm activation. */
			alarmAction();
		}

		/* Continuously check for user input until a valid choice is made. */
		do
		{
			/* Check if an alarm has been triggered during menu navigation. */
			if (TRUE == g_alarmHasFired)
			{
				/* Reset the alarm flag. */
				g_alarmHasFired = FALSE;

				/* Perform actions associated with alarm activation. */
				alarmAction();
			}

			/* Get the user's choice from the keypad. */
			mainMenuChoice = RTE_KEYPAD_getPressedKey();

		} while (!(mainMenuChoice == SET_ALARM_CHOICE || mainMenuChoice == CANCEL_ALARM_CHOICE || mainMenuChoice == ALARM_LIST_CHOICE));

		/* Check the user's choice and take appropriate action. */
		if (mainMenuChoice == SET_ALARM_CHOICE)
		{
			/* Enter the state for setting a new alarm. */
			state = App_setAlarm();
		}
		else if (mainMenuChoice == CANCEL_ALARM_CHOICE)
		{
			/* Enter the state for canceling an existing alarm. */
			App_cancelAlarm();
		}
		else if (mainMenuChoice == ALARM_LIST_CHOICE)
		{
			/* Enter the state for displaying the alarm list. */
			App_listAlarm();
		}
		else
		{
			/* Invalid choice; do nothing. */
		}

		/* Check if an alarm has been triggered after user interaction. */
		if (TRUE == g_alarmHasFired)
		{
			/* Reset the alarm flag. */
			g_alarmHasFired = FALSE;

			/* Perform actions associated with alarm activation. */
			alarmAction();
		}
	}
}

/*==============================================================================================
 *										Set Alarm Function
 *==============================================================================================
 * Function Name: App_setAlarm
 *
 * Description:
 *   The App_setAlarm function facilitates the process of setting a new alarm time within
 *   the Sunrise Alarm Clock application. This function actively engages with the user
 *   by utilizing the LCD display and keypad input to create a seamless experience.
 *
 * Function Workflow:
 *   1. If an alarm has fired (g_alarmHasFired == TRUE), this function will reset the alarm
 *      state and trigger the appropriate alarm action using the alarmAction function.
 *
 *   2. It initializes a temporary character array (tempalarmdigits) to store the four-digit
 *      alarm time that the user inputs.
 *
 *   3. The exit_Flag variable is used to control the loop, ensuring the function remains
 *      active until the alarm setting is complete or cancelled.
 *
 *   4. The function searches for an available slot in the alarmsBuffer (array of alarm
 *      information structures) to store the new alarm. If the maximum number of alarms
 *      (MAXIMUM_ALARMS) has been reached, it informs the user and exits the function.
 *
 *   5. The LCD display prompts the user to "Enter Desired Time." The user is required to
 *      input four digits representing hours and minutes in the HH:MM format. The input is
 *      validated to ensure that hours are between 00 and 23 and minutes are between 00 and 59.
 *      The user is prompted for each digit sequentially, ensuring proper formatting.
 *
 *   6. After the user inputs the time and confirms it, the function calculates the time in
 *      seconds for alarm triggering. It also sets the alarm flag in the alarmsBuffer,
 *      indicating that an alarm has been set.
 *
 *   7. The Timer1 is started to monitor the alarms.
 *
 *   8. The function returns the index of the newly set alarm in the alarmsBuffer if successful.
 *      If the user cancels the operation, it returns CANCELLED. If an unexpected error occurs,
 *      it returns 8.
 *
 * Global Variables:
 *   - g_alarmHasFired (volatile uint8): A flag indicating if an alarm has fired.
 *   - alarmsBuffer (array of structs): An array to store alarm information.
 *   - MAXIMUM_ALARMS (macro constant): Maximum number of alarms supported.
 *
 * Parameters:
 *   None.
 *
 * Returns:
 *     - STATUS: A status code indicating the result of the alarm setting operation.
 *     - INDEX: Index of the newly set alarm in the alarmsBuffer if successful.
 *     - CANCELLED: Returned if the user cancels the operation.
 *     - 8: Returned if an unexpected error occurs.
 *
 * Notes:
 *   - The function ensures that the user provides a valid four-digit time input.
 *   - Delays (e.g., _delay_ms) are used for user experience.
 *
 */
 STATUS App_setAlarm(void) {
	 /* Reset alarm if it has fired */
	 if (TRUE == g_alarmHasFired) {
		 g_alarmHasFired = FALSE;
		 alarmAction();
	 }

	 /* Temporary storage for alarm digits */
	 char tempAlarmDigits[4];

	 /* Flag to exit the alarm setting loop */
	 uint8 exitFlag = 0;

	 /* Keypad input buffer and alarm index */
	 uint8 keypadBuffer, indexOfFirstAvailableAlarm, digits;
	 indexOfFirstAvailableAlarm = MAX_ALARMS;

	 /* Clear the LCD screen */
	 RTE_LCD_clearScreen();

	 while (exitFlag == 0) {
		 /* Find the first available alarm slot */
		 for (digits = 0; digits < MAX_ALARMS; ++digits) {
			 if (alarmsBuffer[digits].flag == FALSE) {
				 indexOfFirstAvailableAlarm = digits;
				 break;
			 }
		 }

		 /* Check if maximum alarm limit is exceeded */
		 if (indexOfFirstAvailableAlarm == MAX_ALARMS) {
			 exitFlag = 1;
			 RTE_LCD_displayString("Number of Alarms limit exceeded");
			 continue;
		 }

		 /* Display prompt for entering alarm time */
		 RTE_LCD_moveCursor(LCD_ROW_0, LCD_COLUMN_0);
		 RTE_LCD_displayString("Enter Desired Time  ");

		 /* Retrieve alarm digits from the user */
		 for (digits = 0; digits < 4; ++digits) {
			 if (digits % 2 == 0) {
				 /* Handle even digits (0, 2) */
				 do {
					 if (TRUE == g_alarmHasFired) {
						 g_alarmHasFired = FALSE;
						 alarmAction();
					 }
					 keypadBuffer = RTE_KEYPAD_getPressedKey();

					 if (digits == 2) {
						 RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_10 - digits - 1);
						 } else {
						 RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_10 - digits);
					 }
				 } while ((keypadBuffer > 9) || (keypadBuffer < 0));

				 tempAlarmDigits[digits] = keypadBuffer;
				 RTE_LCD_integerToString(keypadBuffer);
				 } else {
				 /* Handle odd digits (1, 3) */
				 do {
					 keypadBuffer = RTE_KEYPAD_getPressedKey();
					 if (digits == 3) {
						 RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_10 - digits - 1);
						 } else {
						 RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_10 - digits);
					 }
				 } while (keypadBuffer > 5 || keypadBuffer < 0);

				 tempAlarmDigits[digits] = keypadBuffer;
				 RTE_LCD_integerToString(keypadBuffer);
			 }

			 /* Display ':' between hours and minutes */
			 if (digits == 1) {
				 RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_10 - digits - 1);
				 RTE_LCD_displayCharacter(':');
			 }
		 }

		 /* Add a delay for user readability */
		 _delay_ms(500);
		 /* Display confirmation options */
		 RTE_LCD_clearScreen();
		 RTE_LCD_displayString("To Confirm, Press 1");
		 RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
		 RTE_LCD_displayString("To go back, Press 0");
		 RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_0);
		 RTE_LCD_displayString("To Exit, Press 2");
		 RTE_LCD_moveCursor(LCD_ROW_3, LCD_COLUMN_7);
		 RTE_LCD_integerToString(tempAlarmDigits[3]);
		 RTE_LCD_integerToString(tempAlarmDigits[2]);
		 RTE_LCD_displayCharacter(':');
		 RTE_LCD_moveCursor(LCD_ROW_3, LCD_COLUMN_10);
		 RTE_LCD_integerToString(tempAlarmDigits[1]);
		 RTE_LCD_integerToString(tempAlarmDigits[0]);

		 do {
			 keypadBuffer = RTE_KEYPAD_getPressedKey();
		 } while (keypadBuffer > 2 || keypadBuffer < 0);

		 /* Process user input */
		 if (keypadBuffer == CONFIRM_ALARM_SETTING) {
			 /* Store the entered alarm time in alarmsBuffer */
			 for (digits = 0; digits < 4; digits++) {
				 alarmsBuffer[indexOfFirstAvailableAlarm].alarmDigits[digits] = tempAlarmDigits[digits];
			 }

			 /* Calculate and set the alarm's total seconds */
			 alarmsBuffer[indexOfFirstAvailableAlarm].secondsCounter =
			 ((tempAlarmDigits[3] * 10 + tempAlarmDigits[2]) * 60) + (tempAlarmDigits[1] * 10 + tempAlarmDigits[0]);

			 /* Set the alarm flag and start Timer1 */
			 alarmsBuffer[indexOfFirstAvailableAlarm].flag = TRUE;
			 RTE_TIMER1_vidStart();
			 exitFlag = 1;

			 /* Return the index of the newly set alarm */
			 return indexOfFirstAvailableAlarm;
			 } else if (keypadBuffer == GO_BACK) {
			 /* User chose to go back, continue input */
			 continue;
			 } else if (keypadBuffer == EXIT_ALARM_SETTING) {
			 /* User chose to exit without setting an alarm */
			 exitFlag = 1;
			 return CANCELLED;
			 } else {
			 /* Error condition, return ALARM_SETTING_ERROR */
			 return ALARM_ERROR;
		 }
	 }
	 /* Return ALARM_SETTING_ERROR for an unknown error condition */
	 return ALARM_ERROR;
 }

/**
/*==============================================================================================
 *										Cancel Alarm Function
 *==============================================================================================
 * @brief Cancel an existing alarm.
 *
 * This function allows the user to cancel an existing alarm by selecting it from a list
 * displayed on the LCD screen. It displays the list of currently set alarms and waits for
 * the user to choose which alarm to cancel. After selecting an alarm, it cancels the alarm,
 * clears its settings, and updates the LCD to reflect the cancellation.
 *
 * @details
 * The `App_cancelAlarm` function provides the following functionality:
 *
 * 1. Clears the LCD screen to prepare for displaying alarm information.
 * 2. Iterates through the list of alarms and displays each alarm's details if it is set.
 *    If an alarm is not set, it displays that the alarm isn't set.
 * 3. Waits for the user to select an alarm to cancel using the keypad.
 * 4. Cancels the selected alarm, clears its settings, and updates the LCD to confirm the cancellation.
 * 5. Returns a status code indicating the result of the cancellation.
 *
 * @note The function assumes that alarmsBuffer is an array of alarm structures.
 *
 * @return STATUS:
 *  - CANCELLED: The user canceled the operation.
 *  - CONFIRMED: The alarm was successfully canceled.
 */
STATUS App_cancelAlarm()
{
	/* Clear the LCD screen */
	RTE_LCD_clearScreen();

	uint8 alarmId, keypadBuffer;

	/* Iterate through alarms and display information */
	for (alarmId = 0; alarmId < MAXIMUM_ALARMS; alarmId++)
	{
		if (alarmsBuffer[alarmId].flag == TRUE)
		{
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_0);
			RTE_LCD_displayString("Alarm ");
			RTE_LCD_integerToString(alarmId);
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_6);
			RTE_LCD_displayString("-> ");
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_13);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[3]);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[2]);
			RTE_LCD_displayCharacter(':');
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_16);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[1]);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[0]);
		}
		else
		{
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_0);
			RTE_LCD_displayString("Alarm ");
			RTE_LCD_integerToString(alarmId);
			RTE_LCD_displayString(" isn't set");
		}
	}

	/* Wait for user input to select an alarm to cancel */
	do
	{
		keypadBuffer = RTE_KEYPAD_getPressedKey();
	} while ((keypadBuffer > 4) || (keypadBuffer < 0));

	if (keypadBuffer == 4)
	{
		/* User canceled the operation */
		return CANCELLED;
	}

	/* Cancel the selected alarm */
	for (alarmId = 0; alarmId < MAXIMUM_ALARMS; alarmId++)
	{
		if (keypadBuffer == alarmId)
		{
			if (alarmsBuffer[alarmId].flag == FALSE)
			{
				/* Display a message for an unset alarm */
				RTE_LCD_clearScreen();
				RTE_LCD_displayString("Alarm ");
				RTE_LCD_integerToString(alarmId);
				RTE_LCD_displayString(" is not set");
				_delay_ms(1000);
			}
			else
			{
				/* Cancel the alarm and clear its settings */
				alarmsBuffer[alarmId].flag = FALSE;
				alarmsBuffer[alarmId].alarmDigits[0] = ALARM_INTIAL_VALUE;
				alarmsBuffer[alarmId].alarmDigits[1] = ALARM_INTIAL_VALUE;
				alarmsBuffer[alarmId].alarmDigits[2] = ALARM_INTIAL_VALUE;
				alarmsBuffer[alarmId].alarmDigits[3] = ALARM_INTIAL_VALUE;
				alarmsBuffer[alarmId].secondsCounter = 0;

				/* Update the LCD to confirm the cancellation */
				RTE_LCD_clearScreen();
				RTE_LCD_moveCursor(LCD_ROW_0, LCD_COLUMN_0);
				RTE_LCD_displayString("Alarm ");
				RTE_LCD_integerToString(alarmId);
				RTE_LCD_displayString(" cancelled");
				_delay_ms(2000);
			}
		}
	}

	/* Return a status code to indicate the result */
	return CONFIRMED;
}
/*==============================================================================================
/*												ISR Body                              
 *==============================================================================================
/**
 * @brief Interrupt service routine for handling alarms.
 *
 * This ISR checks the status of each alarm and, if an alarm is active and its
 * countdown reaches zero seconds, it sets the alarmHasFired flag and records
 * the index of the fired alarm. Additionally, it decrements the countdown for
 * active alarms.
 *
 * @details
 * This ISR is responsible for monitoring the status of alarms and responding
 * when an alarm's countdown reaches zero. It iterates through all available
 * alarms and checks their status. If an alarm is active (flag is set) and its
 * countdown (`secondsCounter`) reaches zero, it sets the `g_alarmHasFired` flag to
 * indicate that an alarm has fired. It also records the index of the fired alarm
 * in the `g_NowFiredAlarm` variable.
 *
 * @note
 * - This ISR should be triggered at regular intervals by the timer interrupt.
 * - The `alarmsBuffer` array should be properly initialized with alarm settings.
 *
 * @see g_alarmHasFired
 * @see g_NowFiredAlarm
 * @see alarmsBuffer
 */
void ISRcallBackFunction(void)
{
	for (uint8 alarmId = 0; alarmId < MAXIMUM_ALARMS; alarmId++)
	{
		if (alarmsBuffer[alarmId].flag)
		{
			/* Check if the alarm countdown has reached zero */
			if (alarmsBuffer[alarmId].secondsCounter == 0)
			{
				g_alarmHasFired = TRUE;             /* Set alarm fired flag */
				g_NowFiredAlarm = alarmId;          /* Store the index of the fired alarm */
				alarmsBuffer[alarmId].flag = FALSE; /* Reset the alarm flag */
			}

			alarmsBuffer[alarmId].secondsCounter--;  /* Decrement the alarm seconds counter */
			displayCountdown(alarmId);
		}
	}
}

/*==============================================================================================
/*									Alarm Action                              
 *==============================================================================================
/**
 * @brief Perform actions when an alarm is triggered.
 *
 * This function is called when an alarm is triggered. It turns on the buzzer, displays
 * an alarm message on the LCD, waits for the user to solve a puzzle (in this case,
 * it simulates waiting for the light level to increase), and turns off the alarm and
 * buzzer once the user action is confirmed.
 *
 * @details
 * When called, this function performs the following steps:
 *
 * 1. Initializes local variables, including `UserIn`, which stores user input.
 * 2. Resets the light level reading to zero and starts Timer0.
 * 3. Turns on the buzzer.
 * 4. Clears the LCD screen and displays an alarm message.
 * 5. Continuously checks the light level reading (simulated user action).
 * 6. Calls the `WakeUpCalculator` function to simulate the user's action.
 * 7. If the user action is confirmed (`UserIn == CONFIRMED`), it displays a "Good Morning"
 *    message on the LCD, turns off the buzzer, and indicates that the alarm is closed.
 * 8. Stops Timer0, turns off all LEDs, and returns to the main application loop.
 *
 * @note
 * - The function simulates a user action by monitoring the light level (`g_readingLDR`)
 *   to increase above a threshold (`LDR_THRESHOLD`).
 * - The `WakeUpCalculator` function simulates the user's action to confirm the alarm.
 *
 * @see g_readingLDR
 * @see LDR_THRESHOLD
 * @see WakeUpCalculator
 *
 * @param None.
 * @return The status `CONFIRMED` to indicate that the alarm action is confirmed.
 */
STATUS alarmAction()
{
    STATUS UserIn;

    g_readingLDR = 0;             /* Reset light level reading */
    RTE_TIMER0_vidStart();        /* Start Timer0 for timing */
    RTE_Buzzer_TurnOnOff(TRUE);   /* Turn on the buzzer */
    RTE_LCD_clearScreen();        /* Clear the LCD screen */

    RTE_LCD_moveCursor(LCD_ROW_0, LCD_COLUMN_0);
    RTE_LCD_displayString("Alarm ");
    RTE_LCD_integerToString(g_NowFiredAlarm);
    RTE_LCD_displayString(" is Off");
    _delay_ms(1);                /* Delay for display */

    /* Simulate user action: Wait for light level to increase */
    while (g_readingLDR < LDR_THRESHOLD)
    {
        g_readingLDR = LDR_u16GetLDRReadingSync(ADC_CHANNEL_0);
        _delay_ms(100);
    }

    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
    RTE_LCD_displayString("Solve to close Alarm");
    RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_0);

    /* Simulate user action with the WakeUpCalculator function */
    UserIn = WakeUpCalculator();

    if (UserIn == CONFIRMED)
    {
        RTE_LCD_clearScreen();
        RTE_LCD_displayString("Good Morning");
        _delay_ms(900);
        RTE_LCD_clearScreen();
        RTE_Buzzer_TurnOnOff(FALSE); /* Turn off the buzzer */
        RTE_LCD_displayString("Alarm closed!");
        _delay_ms(800);
        RTE_Buzzer_TurnOnOff(FALSE); /* Turn off the buzzer */
    }

    RTE_TIMER0_vidStop();	  /* Stop Timer0 */
    RTE_LED_All_Off();        /* Turn off all LEDs */
    mainApplication();        /* Return to the main application */
    return CONFIRMED;         /* Return CONFIRMED status */
}


/*==============================================================================================
/*							   Solve Equation to Stop Alarm                              
 *==============================================================================================
/*
 * @brief Simulate a user action to solve a puzzle and confirm the alarm.
 *
 * This function simulates a user action where the user is presented with a mathematical
 * puzzle based on the current alarm and must provide the correct answer to confirm the alarm.
 *
 * @details
 * When called, this function performs the following steps:
 *
 * 1. Initializes local variables, including `result` (the correct answer), `userAnswer`
 *    (the user's input), and `answerCorrect` (a flag indicating if the answer is correct).
 * 2. Selects a mathematical puzzle based on the current alarm (`g_NowFiredAlarm`) using a
 *    `switch` statement.
 * 3. Displays the puzzle on the LCD screen and determines the number of digits in the answer.
 * 4. Enters a loop to simulate user input:
 *    - Reads each digit of the user's input from the keypad.
 *    - Displays the entered digit on the LCD screen.
 *    - Constructs the user's answer as they enter digits.
 *    - Checks if the user's answer matches the correct result.
 * 5. If the user's answer is correct, it sets `answerCorrect` to `TRUE`, displays the correct
 *    answer on the LCD, and returns `CONFIRMED` to indicate that the alarm action is confirmed.
 * 6. If the user's answer is incorrect, it displays an error message on the LCD and continues
 *    to prompt for input until the user provides the correct answer.
 *
 * @note
 * - The `switch` statement selects a puzzle based on the current alarm (`g_NowFiredAlarm`).
 * - The number of digits in the answer is determined by `numOfDigits`.
 *
 * @param None.
 * @return The status `CONFIRMED` if the user provides the correct answer; otherwise, it returns `8`.
 */
STATUS WakeUpCalculator()
{
	/* Initialize variables */
	uint32 result = 0;          /* The correct answer to the puzzle */
	uint32 userAnswer = 0;      /* User's input for the puzzle answer */
	uint8 answerCorrect = FALSE; /* Flag to indicate if the answer is correct */
	uint8 keyPadBuffer;         /* Stores keypad input */
	uint8 cases = g_NowFiredAlarm; /* The current alarm case (used for selecting the puzzle) */

	/* Select the puzzle based on the current alarm case */
	switch (cases)
	{
		case ALARM_EQUATION_1:
		result = CALC_PUZZLE_1;
		RTE_LCD_displayString(DISPLAY_EQUATION_1);
		numOfDigits = NUM_OF_DIGITS_2; /* Number of digits in the answer */
		break;

		case ALARM_EQUATION_2:
		result = CALC_PUZZLE_2;
		RTE_LCD_displayString(DISPLAY_EQUATION_2);
		numOfDigits = NUM_OF_DIGITS_1;
		break;

		case ALARM_EQUATION_3:
		result = CALC_PUZZLE_3;
		RTE_LCD_displayString(DISPLAY_EQUATION_3);
		numOfDigits = NUM_OF_DIGITS_2;
		break;

		case ALARM_EQUATION_4:
		result = CALC_PUZZLE_4;
		RTE_LCD_displayString(DISPLAY_EQUATION_4);
		break;

		default:
		/* Invalid alarm case */
		break;
	}

	do
	{
		userAnswer = 0;

		/* Loop to read each digit of the user's input */
		for (uint8 digits = 0; digits < numOfDigits; ++digits)
		{
			keyPadBuffer = RTE_KEYPAD_getPressedKey();
			RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_17 + digits);
			RTE_LCD_integerToString(keyPadBuffer);
			_delay_ms(80); /* Delay for display */
			userAnswer = userAnswer * 10 + keyPadBuffer;
		}

		if (userAnswer == result)
		{
			answerCorrect = TRUE;
			RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_17);
			RTE_LCD_integerToString(userAnswer);
			_delay_ms(150); /* Delay for display */
			return CONFIRMED; /* User's answer is correct */
		}
		else
		{
			RTE_LCD_moveCursor(LCD_ROW_3, LCD_COLUMN_0);
			RTE_LCD_displayString("Wrong !");
			RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_17);
			RTE_LCD_displayString("  "); /* Clear the incorrect input */
		}

	} while (keyPadBuffer > MAX_KEYPAD_VALUE || keyPadBuffer < MIN_KEYPAD_VALUE || (answerCorrect == FALSE));

	/* User didn't provide the correct answer */
	return ALARM_ERROR;
}

/*==============================================================================================
/*										Show Alarms                              
 *==============================================================================================
/* This function displays a list of set alarms on an LCD screen and
/* allows the user to cancel alarms if desired.
/*
/* Parameters: None
/*
/* Returns:
/* - CONFIRMED: If the user confirms or if no alarms are set.
/* - CANCELLED: If the user cancels an alarm.
 *==============================================================================================*/

STATUS App_listAlarm()
{
	/* Clear the LCD screen */
	RTE_LCD_clearScreen();

	uint8 alarmId, keypadBuffer;

	/* Display alarms and their details */
	for (alarmId = 0; alarmId < MAXIMUM_ALARMS; ++alarmId)
	{
		if (alarmsBuffer[alarmId].flag == TRUE)
		{
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_0);
			RTE_LCD_displayString("Alarm");
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_6);
			RTE_LCD_integerToString(alarmId);
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_8);
			RTE_LCD_displayString("-> ");
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_13);

			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[3]);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[2]);
			RTE_LCD_displayCharacter(':');

			/* LCD display "  :  " in coordinates in the middle of the screen */
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_16);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[1]);
			RTE_LCD_integerToString(alarmsBuffer[alarmId].alarmDigits[0]);
		}
		else
		{
			RTE_LCD_moveCursor(alarmId, LCD_COLUMN_0);
			RTE_LCD_displayString("Alarm ");
			RTE_LCD_integerToString(alarmId);
			RTE_LCD_displayString(" isn't set");
		}
	}

	/* Wait for user input to cancel an alarm or confirm */
	do
	{
		keypadBuffer = RTE_KEYPAD_getPressedKey();
	} while ((keypadBuffer > 5) || (keypadBuffer < 4));

	if (keypadBuffer == 1)
	{
		return CANCELLED; /* User cancelled an alarm */
	}

	return CONFIRMED; /* User confirmed or no alarms set */
}



/*==================================================================
 * Function: LEDdimmingOverFlow
 *
 * Description:
 *   This function performs LED dimming using overflow counts. It
 *   incrementally increases and decreases the LED duty cycle by
 *   modifying the Timer0 settings.
 *
 * Inputs:
 *   None.
 *
 * Returns:
 *   None.
 *
 *==================================================================*/
/* Function to perform LED dimming using overflow counts */
void LEDdimmingOverFlow(void)
{
    /* Static variable to hold the duty cycle value */
    static uint8 DUTY = MIN_DUTY_CYCLE;

    /* Check if duty cycle has reached maximum */
    if (DUTY >= MAX_DUTY_CYCLE) {
        /* Set flags for decreasing and stop increasing */
        Decreasing = TRUE;
        Increasing = FALSE;
    }

    /* Check if duty cycle has reached minimum */
    if (DUTY <= MIN_DUTY_CYCLE) {
        /* Set flags for increasing and stop decreasing */
        Decreasing = FALSE;
        Increasing = TRUE;
    }

    /* Increase duty cycle */
    if (Increasing) {
        /* Delay the duty cycle change by maximum overflow count */
        if (g_timer0Overflow_cnt < MAX_OVERFLOW_COUNT) {
            g_timer0Overflow_cnt++;
        } else {
            g_timer0Overflow_cnt = 0;
            DUTY++;
            /* Update the Timer0 duty cycle */
            TIMER0_u8SetDutyCycle(DUTY);
        }
    }

    /* Decrease duty cycle */
    if (Decreasing) {
        /* Delay the duty cycle change by maximum overflow count */
        if (g_timer0Overflow_cnt < MAX_OVERFLOW_COUNT) {
            g_timer0Overflow_cnt++;
        } else {
            g_timer0Overflow_cnt = 0;
            DUTY--;
            /* Update the Timer0 duty cycle */
            TIMER0_u8SetDutyCycle(DUTY);
        }
    }
}

/*==================================================================
 * Function: LEDdimmingCompareMatch
 *
 * Description:
 *   This function performs LED dimming using compare match. It toggles
 *   the state of multiple LEDs.
 *
 * Inputs:
 *   None.
 *
 * Returns:
 *   None.
 *
 *==================================================================*/
void LEDdimmingCompareMatch(){

    LED_Toggle(LED_BLUE);
    LED_Toggle(LED_RED);
    LED_Toggle(LED_GREEN);
    LED_Toggle(LED_YELLOW);
}

/*==================================================================*/
/*                 Welcome Screen Display                           */
/*==================================================================*/
/*==================================================================
 * Function: App_welcomeScreen
 *
 * Description:
 *   This function displays a welcome screen on an LCD. It shows team
 *   information, names, class, company info, a welcome message, and
 *   a start project message.
 *
 * Inputs:
 *   None.
 *
 * Returns:
 *   None.
 *
 *==================================================================*/
void App_welcomeScreen()
{
    /* Initialize LCD */
    RTE_LCD_clearScreen();

    /* Display Team Information */
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);

    RTE_LCD_displayString(TEAM);
    _delay_ms(50);          /* Delay for 50 milli seconds */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
    RTE_LCD_displayString(TEAM_REVERSE);
    _delay_ms(50);          /* Delay for 50 milli seconds */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
    RTE_LCD_displayString(TEAM);
    _delay_ms(2000);        /* Delay for 2 seconds */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_0, LCD_COLUMN_0);
    RTE_LCD_displayString(NAME_1);
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
    RTE_LCD_displayString(NAME_2);
    RTE_LCD_moveCursor(LCD_ROW_2, LCD_COLUMN_0);
    RTE_LCD_displayString(NAME_3);
    RTE_LCD_moveCursor(LCD_ROW_3, LCD_COLUMN_0);
    RTE_LCD_displayString(NAME_4);
    _delay_ms(700);     /* Delay for 1 second */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
    RTE_LCD_displayString(NAME_5);
    _delay_ms(700);         /* Delay for 3 seconds */

    /* Display class and company info */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_0, LCD_COLUMN_0);
    RTE_LCD_displayString(COMPANY);
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_0);
    RTE_LCD_displayString(CLASS);
    _delay_ms(700);     /* Delay for 3 seconds */

    /* Display Welcome Message */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_3);
    RTE_LCD_displayString(WELCOME);
    _delay_ms(700);         /* Delay for 2 seconds */


    /* Display Start Engine Message */
    RTE_LCD_clearScreen();
    RTE_LCD_moveCursor(LCD_ROW_1, LCD_COLUMN_1);
    RTE_LCD_displayString(START_PROJ);
    _delay_ms(700);     /* Delay for 2 seconds */
}

/*Function to display a countdown timer on LCD*/
void displayCountdown(uint8 alarmId) {
	RTE_LCD_moveCursor(alarmId, LCD_COLUMN_15);
	uint32 minutes = alarmsBuffer[alarmId].secondsCounter / 60;
	uint32 seconds = alarmsBuffer[alarmId].secondsCounter % 60;

	RTE_LCD_integerToString(minutes);
	RTE_LCD_displayCharacter(':');

	if (seconds < 10) {
		RTE_LCD_displayCharacter('0'); /*Add leading zero for single-digit seconds*/
	}
	RTE_LCD_integerToString(seconds);
}
