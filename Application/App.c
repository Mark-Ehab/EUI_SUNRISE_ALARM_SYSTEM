/*================================================================
 __  __      _     __          __
 |  \/  |    | |    \ \        / /
 | \  / | ___| |_ __ \ \  /\  / /_ _ _ __ ___
 | |\/| |/ _ \ __/ _` \ \/  \/ / _` | '__/ _ \
              | |  | |  __/ || (_| |\  /\  / (_| | | |  __/
 |_|  |_|\___|\__\__,_| \/  \/ \__,_|_|  \___|
 ==================================================================
 SWC : App.c
 Date: 8/28/2023
 Authors: MetaWare LLC
 Mahmoud Sayed Mahmoud Helmy (1285)
 Mohamed Mahmoud Masoud (200)
 Mark Ehab Tawfik (201)
 Hazzem Mohamed Ezzeldin (1297)
 Yousef Khaled Ahmed (558)
 ================================================================
 Description: This file contains the main application logic and
 functions for controlling alarms and user interactions.
 ================================================================
 FILE NAME: App.c
 ================================================================*/

#include "App.h"       /* Include the header file for this application */
#include <stdlib.h>    /* Include the standard library for various functions */

/*============================================================================================
                                   Global Variables
 ==============================================================================================

 * @details
 * This section defines global variables used throughout the Sunrise Alarm Clock
 * application. These variables store information such as alarm counts, timer overflows,
 * readings from LDR, alarm status, LED dimming states,
 *
 * These variables are accessible and modifiable from various parts of the code and
 * play a crucial role in the functionality of the application.
 */

/* Counter for how many alarms are being used */
uint8 g_alarm_cnt = 1;
/* Counter for Timer0 overflows */
uint8 g_timer0Overflow_cnt = 0;
/* Store the reading from an LDR (Light Dependent Resistor) */
volatile uint16 readingLDR = 0;
/* Flag to indicate a fired alarm */
volatile uint8 g_alarmHasFired = FALSE;
/* Number of digits used for displaying numbers */
uint8 numOfDigits = 0;
/*Flag to indicate the state of the duty cycle in the LEDdimming functions*/
uint8 decreasing = 0;
/*Flag to indicate the state of the duty cycle in the LEDdimming functions*/
uint8 increasing = 1;
/*Array to hold set time of alarm*/
char digitsArray[MaximumAlarms];
/*Global flag that indicates which alarm is fired right now*/
volatile uint8 g_NowFiredAlarm;

Alarm_config alarms[MaximumAlarms] = { { 0, { AlarmInitialValue }, 0 }, /* alarm 0 */
                                       { 0, { AlarmInitialValue }, 0 }, /* alarm 1 */
                                       { 0, { AlarmInitialValue }, 0 }, /* alarm 2 */
                                       { 0, { AlarmInitialValue }, 0 } /* alarm 3 */
};

/*==================================================================
                          Initialization
 ==================================================================*/
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

    /*Timer0 Behavior Functions*/

    /*Setting Timer 0 pre-load if any*/
    RTE_TIMER0_vidSetPreloadValue(TIMER0_PRELOADED_VALUE);
    /*Setting Timer 0 callback function to the compare match routine*/
    TIMER0_u8SetCompareMatchCallback(LEDdimmingCompareMatch);
    /*Setting Timer 0 callback function to the overflow routine*/
    TIMER0_u8SetOverflowCallback(LEDdimmingOverFlow);

    /* Initialize Timer1 */
    RTE_TIMER1_vidInit();

    /* Set Timer1 Compare Match Value for Channel A */
    RTE_TIMER1_vidSetCompareMatchAValue(TIMER1_COMPARE_MATCH_VALUE);

    /* Set Timer1 Compare Match Callback Function for Channel A */
    RTE_TIMER1_uint8SetCompareMatchACallback(Interrupt_function);

    /* Enable Global Interrupt Enable */
    RTE_GlobalInterrupt_enable();

    /* Start Timer1 */
    RTE_TIMER1_vidStart();
    /*Graphical art at the beginning*/
    App_welcomeScreen();
}

/**===========================================================================================
                               Main Application Loop
 ==============================================================================================
 * @brief Main loop of the Sunrise Alarm Clock application.
 *
 * @details
 * The `MainApp` function serves as the heart of the Sunrise Alarm Clock application.
 * Below is a detailed breakdown of its functionality:

 * 1. **Alarm Activation Handling**: The function continuously monitors the `g_alarmHasFired` flag.
 *    When an alarm is activated (the flag becomes `TRUE`), it triggers the `alarmAction` function,
 *    which executes actions associated with alarm events. These actions may include activating
 *    external devices, playing sounds, or displaying specific messages.
 *
 * 2. **Main Menu Display**: The main menu of the Sunrise Alarm Clock application is presented on
 *    the LCD screen. It offers three user options: setting an alarm, canceling an existing alarm,
 *    or viewing the list of configured alarms. This menu is continuously displayed to allow
 *    user interaction.
 *
 * 3. **User Input Handling**: The function uses the `RTE_KEYPAD_getPressedKey` function to detect
 *    user input from the keypad. It waits for valid input corresponding to the available menu
 *    options (Set Alarm, Cancel Alarm, or Alarm List) before proceeding.
 *
 * 4. **Action Execution**: Based on the user's choice, the function calls the appropriate sub-functions
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

void MainApp()
{
    /* Enter the main application loop. */
    while (TRUE)
    {
        /*Checking for any fired alarms*/
        if (g_alarmHasFired == TRUE)
        {
            /* Reset the alarm flag. */
            g_alarmHasFired = FALSE;
            /* Perform actions associated with alarm activation. */
            alarmAction();
        }

        /* Variable to store the user's main menu choice. */
        uint8 mainMenuChoice = FALSE;
        uint8 state = 0;

        /* Clearing the LCD to start writing*/
        RTE_LCD_clearScreen();

        /* Moving the cursor to the first row and first column*/
        RTE_LCD_moveCursor(0, 0);
        RTE_LCD_displayString("+Set Alarm   |");

        /* Moving the cursor to the second row and first column*/
        RTE_LCD_moveCursor(1, 0);
        RTE_LCD_displayString("-Cancel Alarm|");

        /* Moving the cursor to the third row and first column*/
        RTE_LCD_moveCursor(2, 0);
        RTE_LCD_displayString("*Alarm List  |");

        /* Moving the cursor to the fourth row and first column*/
        RTE_LCD_moveCursor(3, 0);
        RTE_LCD_displayString("             |");

        /*Checking for any fired alarms*/
        if (g_alarmHasFired == TRUE)
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
            if (g_alarmHasFired == TRUE)
            {
                /* Reset the alarm flag. */
                g_alarmHasFired = FALSE;
                /* Perform actions associated with alarm activation. */
                alarmAction();
            }

            /* Get the user's choice from the keypad. */
            mainMenuChoice = RTE_KEYPAD_getPressedKey();

            /* Continuously loop until the user inputs a valid option from the keypad. */
        }
        while (!(mainMenuChoice == SET_ALARM_CHOICE
                || mainMenuChoice == CANCEL_ALARM_CHOICE
                || mainMenuChoice == ALARM_LIST_CHOICE));
        /* Check the user's choice and take appropriate action. */
        if (mainMenuChoice == SET_ALARM_CHOICE)
        {
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
            /*Do nothing*/
        }
        /*Checking for any fired alarms*/
        if (g_alarmHasFired == TRUE)
        {
            /* Reset the alarm flag. */
            g_alarmHasFired = FALSE;
            /* Perform actions associated with alarm activation. */
            alarmAction();
        }

    }

}

/**==============================================================================================
 *                                      Set Alarm Function
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
 *      alarm time that the user inputs to save at the end in the user confirmation case.
 *
 *   3. The exit_Flag variable is used to control the loop, ensuring the function remains
 *      active until the alarm setting is complete or cancelled.
 *
 *   4. The LCD display prompts the user to "Enter Desired Time." The user is required to
 *      input four digits representing minutes and seconds in the MM:SS format. The input is
 *      validated to ensure that minutes are between 00 and 59 and seconds are between 00 and 59.
 *      The user is prompted for each digit sequentially starting from the ones of seconds field, ensuring proper formatting.
 *
 *   5. After the user inputs the time and confirms it, tempalarmdigits are saved into the global alarmDigits array,
 *      the function calculates the time in seconds for alarm triggering. It also sets the alarm flag in the alarmsBuffer,
 *      indicating that an alarm has been set.
 *
 *   6. Timer1 is started to monitor the alarms.
 *
 *   7. The function returns the index of the newly set alarm in the alarmsBuffer if successful.
 *      If the user cancels the operation, it returns CANCELLED. If an unexpected error occurs,
 *      it returns ERR_STATE.
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
 *     - INDEX: Index of the newly set alarm in the alarmsBuffer if successful.
 *     - CANCELLED: Returned if the user cancels the operation.
 *     - ERR_STATE: Returned if an unexpected error occurs.
 *
 * Notes:
 *   - The function ensures that the user provides a valid four-digit time input.
 *   - Delays (e.g., _delay_ms) are used for user experience.
 *
 */

uint8 App_setAlarm()
{
    /*Checking for any fired alarms*/
    if (g_alarmHasFired == TRUE)
    {
        /* Reset the alarm flag. */
        g_alarmHasFired = FALSE;
        /* Perform actions associated with alarm activation. */
        alarmAction();
    }
    /* Temporary storage for alarm digits */
    char tempalarmdigits[MaximumAlarms];
    /* Flag to exit the alarm setting loop */
    uint8 exit_Flag = FALSE;
    /* Keypad input buffer and alarm indices */
    uint8 keypadBuffer, indexOfFirstavailablealarm, alarmindex;
    /*Setting the variable to ERR_STATE to check if it hadn't change i.e. there is no available alarms*/
    indexOfFirstavailablealarm = ERR_STATE;
    /* Clear the LCD screen */
    RTE_LCD_clearScreen();

    while (exit_Flag == FALSE)
    {
        /* Find the first available alarm slot */
        RTE_LCD_clearScreen();

        for (alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)
        {
            if (alarms[alarmindex].flag == FALSE)
            {
                indexOfFirstavailablealarm = alarmindex;
                /*First available alarm has been found, save its index and break*/
                break;
            }
        }

        /*Checking if the index previously initialized at the beginning of the function
         * have changed by the for loop, if not then there is no available alarms*/
        if (indexOfFirstavailablealarm == ERR_STATE)
        {

            RTE_LCD_displayString("Number of Alarms limit exceeded");
            _delay_ms(500);
            exit_Flag = TRUE;
            /*Exit the main loop, no alarm has been found*/
            continue;
        }

        RTE_LCD_moveCursor(0, 0);
        RTE_LCD_displayString("Enter Desired Time  ");

        /*LCD display "Enter desired time"*/

        /* For loop to save user input in the tempalarmdigits array*/

        for (alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)
        {
            /*Checking for the field of ones(0,2) and tens(1,3) of seconds and minutes*/
            if (alarmindex % 2 == 0)
            {
                do
                {
                    /*Checking for any fired alarms*/
                    if (g_alarmHasFired == TRUE)
                    {
                        /* Reset the alarm flag. */
                        g_alarmHasFired = FALSE;
                        /* Perform actions associated with alarm activation. */
                        alarmAction();
                    }
                    /*Take the first one in the seconds field
                     * and the first ten in the seconds field */
                    keypadBuffer = RTE_KEYPAD_getPressedKey();

                    if (alarmindex == 2)
                        RTE_LCD_moveCursor(2, 10 - alarmindex - 1);
                    /* Moving cursor to the appropriate position*/
                    else
                        RTE_LCD_moveCursor(2, 10 - alarmindex);
                }
                while ((keypadBuffer > ONES_OF_SEC_OR_MIN) || (keypadBuffer < 0));
                /*While loop is restricted by not entering a number bigger
                 * than 9 or smaller than 0 in the ones fields, otherwise the
                 * user input will be rejected and the loop iterates again*/

                tempalarmdigits[alarmindex] = keypadBuffer;
                /*Saving the index after appropriate user input*/

                RTE_LCD_integerToString(keypadBuffer);
                /*Displaying the user input*/
            }
            /*Checking for the field of ones(0,2) and tens(1,3) of seconds and minutes*/
            else
            {
                do
                {
                    /*Take the first one in the minutes field
                     * an the first ten in the minutes field */
                    keypadBuffer = RTE_KEYPAD_getPressedKey();

                    if (alarmindex == 3)
                        RTE_LCD_moveCursor(2, 10 - alarmindex - 1);
                    /* Moving cursor to the appropriate position*/
                    else
                        RTE_LCD_moveCursor(2, 10 - alarmindex);

                }
                while (keypadBuffer > TENS_OF_SEC_OR_MIN || keypadBuffer < 0);
                /*While loop is restricted by not entering a number bigger
                 * than 5 or smaller than 0 in the tens fields, otherwise the
                 * user input will be rejected and the loop iterates again*/

                tempalarmdigits[alarmindex] = keypadBuffer;
                /*Saving the index after appropriate user input*/

                RTE_LCD_integerToString(keypadBuffer);
                /*Displaying the user input*/
            }
            if (alarmindex == 1)
            {
                RTE_LCD_moveCursor(2, 10 - alarmindex - 1);
                /* Moving cursor to the appropriate position*/
                RTE_LCD_displayCharacter(':');
                /*LCD display of : between seconds and minutes*/
            }
        }

        _delay_ms(500);
        /*Displaying the user choice and asking for an input*/
        RTE_LCD_clearScreen();
        RTE_LCD_displayString("To Confirm, Press 1");
        /*Confirmation and saving of entered alarm*/
        RTE_LCD_moveCursor(1, 0);
        /*Going back to edit the set alarm, set alarm is not saved*/
        RTE_LCD_displayString("To go back, Press 0");
        RTE_LCD_moveCursor(2, 0);
        /*Exiting to the main loop, set alarm is not saved*/
        RTE_LCD_displayString("To Exit, Press 2");
        RTE_LCD_moveCursor(3, 7);
        RTE_LCD_integerToString(tempalarmdigits[3]);
        RTE_LCD_integerToString(tempalarmdigits[2]);
        RTE_LCD_displayCharacter(':');
        /*LCD display "  :  " in coordinates in the middle of the screen*/
        RTE_LCD_moveCursor(3, 10);
        RTE_LCD_integerToString(tempalarmdigits[1]);
        RTE_LCD_integerToString(tempalarmdigits[0]);

        /*Loop for the user to input his choice through keypad
         * 1 For Confirmation
         * 2 For Exiting to the main menu
         * 3 For Setting again without saving i.e. editing
         */
        do
        {
            keypadBuffer = RTE_KEYPAD_getPressedKey();
        }
        while (keypadBuffer > 2 || keypadBuffer < 0);

        /*Confirmation Case*/
        if (keypadBuffer == CONFIRMED)
        {

            /*Loop for storing the time set in the global array alarmDigits*/
            for (alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)
            {
                alarms[indexOfFirstavailablealarm].alarmDigits[alarmindex] =
                        tempalarmdigits[alarmindex];
            }
            /*Storing the total number of seconds in secCnt variable*/
            alarms[indexOfFirstavailablealarm].secCnt =
                    (((alarms[indexOfFirstavailablealarm].alarmDigits[3] * 10)
                            + (alarms[indexOfFirstavailablealarm].alarmDigits[2]))
                            * 60)
                            + ((alarms[indexOfFirstavailablealarm].alarmDigits[1]
                                    * 10)
                                    + (alarms[indexOfFirstavailablealarm].alarmDigits[0]));
            /*Setting the alarm flag to indicate that this alarm is taken*/
            alarms[indexOfFirstavailablealarm].flag = TRUE;
            /*Timer 1 Start*/
            RTE_TIMER1_vidStart();
            exit_Flag = TRUE;
            /*Returning the index of taken alarm*/
            return indexOfFirstavailablealarm;
        }

        /*Go back Case*/
        else if (keypadBuffer == CANCELLED)
            continue;
        /*Exit to the main menu case*/
        else if (keypadBuffer == EXIT)
        {
            exit_Flag = TRUE;
            return CANCELLED;
        }
        /*Unexpected error*/
        else
        {
            return ERR_STATE;
        }

    }

    return ERR_STATE;

}

/**==============================================================================================
 *                                      Cancel Alarm Function
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
 * 5. If the user tries to cancel an alarm that isn't set , it displays alarm is not set yet.
 * 6. Returns a status code indicating the result of the cancellation.
 *
 * @return STATUS:
 *  - CANCELLED: The operation is cancelled.
 *  - CONFIRMED: The alarm was successfully cancelled.
 */

STATUS App_cancelAlarm()
{

    RTE_LCD_clearScreen();

    uint8 alarmindex, keypadBuffer;

    for (alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)

    {
        if (alarms[alarmindex].flag == TRUE)
        {

            RTE_LCD_moveCursor(alarmindex, 0);
            RTE_LCD_displayString("Alarm");
            RTE_LCD_moveCursor(alarmindex, 6);
            RTE_LCD_integerToString(alarmindex);
            RTE_LCD_moveCursor(alarmindex, 8);
            RTE_LCD_displayString("-> ");
            RTE_LCD_moveCursor(alarmindex, 13);

            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[3]);
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[2]);
            RTE_LCD_displayCharacter(':');
            /*LCD display "  :  " in coordinates in the middle of the screen*/
            RTE_LCD_moveCursor(alarmindex, 16);
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[1]);
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[0]);
        }
        else
        {
            RTE_LCD_moveCursor(alarmindex, 0);
            RTE_LCD_displayString("Alarm ");
            RTE_LCD_integerToString(alarmindex);
            RTE_LCD_displayString(" isn't set");
        }

    }

    do
    {
        keypadBuffer = RTE_KEYPAD_getPressedKey();

    }
    while ((keypadBuffer > MaximumAlarms) || (keypadBuffer < 0));

    if (keypadBuffer == 4)
    {
        return CANCELLED;
    }

    for (alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)
    {
        if (keypadBuffer == alarmindex)
        {
            if (alarms[alarmindex].flag == FALSE)
            {
                RTE_LCD_clearScreen();
                RTE_LCD_displayString("Alarm ");
                RTE_LCD_integerToString(alarmindex);
                RTE_LCD_displayString(" is not set");
                _delay_ms(1000);
            }
            else
            {
                alarms[alarmindex].flag = FALSE;
                alarms[alarmindex].flag = FALSE;
                alarms[alarmindex].alarmDigits[0] = 0;
                alarms[alarmindex].alarmDigits[1] = 0;
                alarms[alarmindex].alarmDigits[2] = 0;
                alarms[alarmindex].alarmDigits[3] = 0;
                alarms[alarmindex].secCnt = 0;
                /*Here: Alarm digits is not deleted*/
                RTE_LCD_clearScreen();
                RTE_LCD_moveCursor(0, 0);
                RTE_LCD_displayString("Alarm ");
                RTE_LCD_integerToString(alarmindex);
                RTE_LCD_displayString(" cancelled");
                _delay_ms(2000);
            }
        }

    }

    return CONFIRMED;

}
/**=================================================================
                        ISR CallBack
 ==================================================================
 * @brief Routine for handling alarms.
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
void Interrupt_function(void)
{
    /*Iterating through alarms*/
    for (uint8 alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)
    {
        /*Alarm flag is set i.e. an active alarm has been set*/
        if (alarms[alarmindex].flag)
        {
            /*After decrementing the seconds count to 0 the alarm is fired*/
            if (alarms[alarmindex].secCnt == 0)
            {
                /*Alarm has fired flag is set*/
                g_alarmHasFired = TRUE;
                /*Index of the fired alarm is saved*/
                g_NowFiredAlarm = alarmindex;
                /*Alarm flag is cleared as it has already fired*/
                alarms[alarmindex].flag = FALSE;

            }
            /*Decrementing the number of seconds in each interrupt
             (happens every second) by timer 1 until it reaches zero*/
            alarms[alarmindex].secCnt--;
        }

    }

}

/**=============================================================================================
 *                                  Alarm Action
 *==============================================================================================
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
    readingLDR = LDR_MIN;
    RTE_TIMER0_vidStart();

    RTE_Buzzer_TurnOnOff(TRUE);
    RTE_LCD_clearScreen();

    RTE_LCD_moveCursor(0, 0);
    RTE_LCD_displayString("Alarm ");
    RTE_LCD_integerToString(g_NowFiredAlarm);
    RTE_LCD_displayString(" is Off");
    _delay_ms(1);

    while (readingLDR < LDR_THRESHOLD)
    {
        readingLDR = LDR_u16GetLDRReadingSync(ADC_CHANNEL_0);
        _delay_ms(100);
    }

    RTE_LCD_moveCursor(1, 0);
    RTE_LCD_displayString("Solve to close Alarm");
    RTE_LCD_moveCursor(2, 0);

    UserIn = WakeUpCalculator();

    if (UserIn == CONFIRMED)
    {
        RTE_LCD_clearScreen();
        RTE_LCD_displayString("Good Morning");
        _delay_ms(900);

        LCD_clearScreen();
        RTE_Buzzer_TurnOnOff(FALSE);
        LCD_displayString("Alarm closed!");
        _delay_ms(800);
        RTE_Buzzer_TurnOnOff(FALSE);
    }
    RTE_TIMER0_vidStop();
    LED_All_Off();
    MainApp();
    return CONFIRMED;

}

/**==============================================================================================
                             Solve Puzzle to Turnoff Alarm
 *==============================================================================================
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
 * @return The status `CONFIRMED` if the user provides the correct answer; otherwise, it returns ERR_STATE.
 */

STATUS WakeUpCalculator()
{
    uint32 result = 0;
    uint32 userAnswer = 0;
    uint8 answerCorrect = FALSE;
    uint8 keyPadBuffer;
    uint8 cases = g_NowFiredAlarm;
    switch (cases)
    {

    case 0:
        result = 10 + 2 * 4;
        RTE_LCD_displayString(" 10 + 2 * 4 =");
        numOfDigits = 2;
        break;
    case 1:
        result = 21 - 5 * 4;
        RTE_LCD_displayString(" 21 - 5 * 4 =");
        numOfDigits = 1;
        break;
    case 2:
        result = 80 + 1 * 4 - 5;
        RTE_LCD_displayString(" 80 + 1 * 4 - 5 =");
        numOfDigits = 2;
        break;
    case 3:
        result = 2;
        RTE_LCD_displayString(" 10 - 4 * 2 =");
        break;
    default:
        ;
    }

    do
    {
        userAnswer = 0;

        for (uint8 digits = 0; digits < numOfDigits; digits++)
        {
            keyPadBuffer = RTE_KEYPAD_getPressedKey();
            RTE_LCD_moveCursor(2, 17 + digits);
            RTE_LCD_integerToString(keyPadBuffer);
            _delay_ms(80);
            userAnswer = userAnswer * 10 + keyPadBuffer;
        }

        if (userAnswer == result)
        {
            answerCorrect = TRUE;
            RTE_LCD_moveCursor(2, 17);
            RTE_LCD_integerToString(userAnswer);
            _delay_ms(150);
            return CONFIRMED;
        }
        else
        {
            RTE_LCD_moveCursor(3, 0);
            LCD_displayString("Wrong !");
            RTE_LCD_moveCursor(2, 17);
            LCD_displayString("  ");
        }

    }
    while (keyPadBuffer > ONES_OF_SEC_OR_MIN || keyPadBuffer < 0
            || (answerCorrect == FALSE));

    return ERR_STATE;

}

/**=============================================================================
                              Show Alarms
 *==============================================================================
 * This function displays a list of set alarms on an LCD screen.
 *
 * Parameters: None
 *
 * Returns:
 * - CONFIRMED: The function displayed correctly
 * - RETURN_TO_MAIN_MENU: If the user wants to return to main menu.
 *============================================================================*/

STATUS App_listAlarm()
{

    RTE_LCD_clearScreen();

    uint8 alarmindex, keypadBuffer;

    /*Iterating through maximum alarms*/
    for (alarmindex = 0; alarmindex < MaximumAlarms; alarmindex++)
    {
        /*Check to display only active alarms set*/
        if (alarms[alarmindex].flag == TRUE)
        {
            /*Displaying firstly Alarm -> on the LCD*/
            RTE_LCD_moveCursor(alarmindex, 0);
            RTE_LCD_displayString("Alarm");
            RTE_LCD_moveCursor(alarmindex, 6);
            RTE_LCD_integerToString(alarmindex);
            RTE_LCD_moveCursor(alarmindex, 8);
            RTE_LCD_displayString("-> ");
            RTE_LCD_moveCursor(alarmindex, 13);
            /*Displaying the set alarms saved in the global array*/
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[3]);
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[2]);
            RTE_LCD_displayCharacter(':');
            /*LCD display "  :  " in coordinates in the middle of the screen*/
            RTE_LCD_moveCursor(alarmindex, 16);
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[1]);
            RTE_LCD_integerToString(alarms[alarmindex].alarmDigits[0]);
        }
        /*The alarm with the associated index isn't set*/
        else
        {
            RTE_LCD_moveCursor(alarmindex, 0);
            RTE_LCD_displayString("Alarm ");
            RTE_LCD_integerToString(alarmindex);
            RTE_LCD_displayString(" isn't set");
        }

    }

    /*Loop to take a single press from the user to return to main menu*/
    /*Mapped to button '#' in the keypad Col 3 Row 4*/
    do
    {
        keypadBuffer = RTE_KEYPAD_getPressedKey();

    }
    while ((keypadBuffer > 35) || (keypadBuffer < 35));
    /*35 is the ASCII of # */

    /*Checking for the user input*/
    if (keypadBuffer == '#')
    {
        return RETURN_TO_MAIN_MENU;
    }

    return CONFIRMED;

}

/**==================================================================
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
    if (DUTY >= MAX_DUTY_CYCLE)
    {
        /* Set flags for decreasing and stop increasing */
        decreasing = TRUE;
        increasing = FALSE;
    }

    /* Check if duty cycle has reached minimum */
    if (DUTY <= MIN_DUTY_CYCLE)
    {
        /* Set flags for increasing and stop decreasing */
        decreasing = FALSE;
        increasing = TRUE;
    }

    /* Increase duty cycle */
    if (increasing)
    {
        /* Delay the duty cycle change by maximum overflow count */
        if (g_timer0Overflow_cnt < MAX_OVERFLOW_COUNT)
        {
            g_timer0Overflow_cnt++;
        }
        else
        {
            g_timer0Overflow_cnt = 0;
            DUTY++;
            /* Update the Timer0 duty cycle */
            TIMER0_u8SetDutyCycle(DUTY);
        }
    }

    /* Decrease duty cycle */
    if (decreasing)
    {
        /* Delay the duty cycle change by maximum overflow count */
        if (g_timer0Overflow_cnt < MAX_OVERFLOW_COUNT)
        {
            g_timer0Overflow_cnt++;
        }
        else
        {
            g_timer0Overflow_cnt = 0;
            DUTY--;
            /* Update the Timer0 duty cycle */
            TIMER0_u8SetDutyCycle(DUTY);
        }
    }
}

/**==================================================================
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

void LEDdimmingCompareMatch()
{

    LED_Toggle(LED_BLUE);
    LED_Toggle(LED_RED);
    LED_Toggle(LED_GREEN);
    LED_Toggle(LED_YELLOW);
}

/**===============================================================
                    Welcome Screen Display
 ==================================================================
 ==================================================================
 * Function: App_welcomeScreen
 *
 * Description:
 *   This function displays a welcome screen on an LCD.
 *   It shows team information, names, class, company info
 *   and a welcome message.
 *
 * Inputs:
 *   None.
 *
 * Returns:
 *   None.
 *
 *===============================================================*/
void App_welcomeScreen()
{
    /* Initialize LCD */
    LCD_clearScreen();

    /* Display Team Information */
    LCD_moveCursor(1, 0);

    LCD_displayString(TEAM);
    _delay_ms(50); /* Delay for 50 milli seconds */
    LCD_clearScreen();
    LCD_moveCursor(1, 0);
    LCD_displayString(TEAM_REVERSE);
    _delay_ms(50); /* Delay for 50 milli seconds */
    LCD_clearScreen();
    LCD_moveCursor(1, 0);
    LCD_displayString(TEAM);
    _delay_ms(2000); /* Delay for 2 seconds */
    LCD_clearScreen();
    LCD_moveCursor(0, 0);
    LCD_displayString(NAME_1);
    LCD_moveCursor(1, 0);
    LCD_displayString(NAME_2);
    LCD_moveCursor(2, 0);
    LCD_displayString(NAME_3);
    LCD_moveCursor(3, 0);
    LCD_displayString(NAME_4);
    _delay_ms(700); /* Delay for 1 second */
    LCD_clearScreen();
    LCD_moveCursor(1, 0);
    LCD_displayString(NAME_5);
    _delay_ms(700); /* Delay for 3 seconds */

    /* Display class and company info */
    LCD_clearScreen();
    LCD_moveCursor(0, 0);
    LCD_displayString(COMPANY);
    LCD_moveCursor(1, 0);
    LCD_displayString(CLASS);
    _delay_ms(700); /* Delay for 3 seconds */

    /* Display Welcome Message */
    LCD_clearScreen();
    LCD_moveCursor(1, 3);
    LCD_displayString(WELCOME);
    _delay_ms(700); /* Delay for 2 seconds */

    /* Display Start Engine Message */
    LCD_clearScreen();
    LCD_moveCursor(1, 1);
    LCD_displayString(START_PROJ);
    _delay_ms(700); /* Delay for 2 seconds */
}
