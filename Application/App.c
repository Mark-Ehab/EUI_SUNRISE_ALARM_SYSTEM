#include "App.h"       /* Include the header file for this application */
#include <stdlib.h>    /* Include the standard library for various functions */

/*==================================================================
                       Global Variables
==================================================================*/
uint8 g_alarm_cnt = 1;  /* Counter for how many alarms are being used */
uint8 g_timer0Overflow_cnt = 0; /* Counter for Timer0 overflows */
volatile uint16 readingLDR = 0; /* Store the reading from an LDR (Light Dependent Resistor) */

volatile uint8 g_alarmHasFired = FALSE; /* Flag to indicate a fired alarm */
//uint8 alarmFoundFlag = FALSE;   /* Flag to indicate finding an available alarm */
uint8 numOfDigits = 0;          /* Number of digits used for displaying numbers */
uint8 Decreasing =0;
uint8 Increasing =1;
//uint8 exit_flag = 0;

/*Array to hold set time of alarm*/
char digitsArray [4];
volatile uint8 g_NowFiredAlarm;

Alarm_config alarms[MaximumAlarms] =
{
 {0 , {AlarmInitialValue}, 0}, /* alarm 0 */
 {0 , {AlarmInitialValue}, 0}, /* alarm 1 */
 {0 , {AlarmInitialValue}, 0}, /* alarm 2 */
 {0 , {AlarmInitialValue}, 0}  /* alarm 3 */
};

/* Array of alarm messages for each alarm */
const char* alarmMessages[] = {
                               "alarm 0 time is out",
                               "alarm 1 time is out",
                               "alarm 2 time is out",
                               "alarm 3 time is out"
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

    /*Timer0 Behaviour Functions*/
    RTE_TIMER0_vidSetPreloadValue(TIMER0_PRELOADED_VALUE);
    TIMER0_u8SetCompareMatchCallback(LEDdimmingCompareMatch);
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

    App_welcomeScreen();
}



void App()
{
    while (TRUE)
    {
        if (alarms[0].flag)
        {
             RTE_LCD_moveCursor((3),14);
             RTE_LCD_integerToString(alarms[0].alarmDigits[3]);
             RTE_LCD_integerToString(alarms[0].alarmDigits[2]);
             RTE_LCD_displayCharacter(':');
             RTE_LCD_moveCursor((3),17);
             RTE_LCD_integerToString(alarms[0].alarmDigits[1]);
             RTE_LCD_integerToString(alarms[0].alarmDigits[0]);

             if (alarms[0].alarmDigits[0] > 0)
             {
                 alarms[0].alarmDigits[0]--;

             }
             else if (alarms[0].alarmDigits[1] > 0)
             {
                 alarms[0].alarmDigits[0] = 9;
                 alarms[0].alarmDigits[1]--;
             }
             else if (alarms[0].alarmDigits[2] > 0)
             {
                 alarms[0].alarmDigits[0] = 9;
                 alarms[0].alarmDigits[1] = 5;
                 alarms[0].alarmDigits[2]--;
             }
             else if (alarms[0].alarmDigits[3] > 0)
             {
                 alarms[0].alarmDigits[0] = 9;
                 alarms[0].alarmDigits[1] = 5;
                 alarms[0].alarmDigits[2] = 9;
                 alarms[0].alarmDigits[3]--;
              }
        }

        if(g_alarmHasFired == TRUE)
        {
            g_alarmHasFired = FALSE;
            alarmAction();
        }

        uint8 mainMenuChoice = FALSE;
        uint8 state = 0;

        /* Clearing the LCD to start writing*/
        RTE_LCD_clearScreen();

        /* moving the cursor to the first row and first column*/
        RTE_LCD_moveCursor(0,0);
        RTE_LCD_displayString("+Set Alarm   |");

        /* moving the cursor to the second row and first column*/
        RTE_LCD_moveCursor(1,0);
        RTE_LCD_displayString("-Cancel Alarm|");

        /* moving the cursor to the third row and first column*/
        RTE_LCD_moveCursor(2,0);
        RTE_LCD_displayString("*Alarm List  |");

        /* moving the cursor to the fourth row and first column*/
        RTE_LCD_moveCursor(3,0);
        RTE_LCD_displayString("             |");
        /*G flag check*/
        if(g_alarmHasFired == TRUE)
        {
            g_alarmHasFired = FALSE;
            alarmAction();
        }

        do{
                if(g_alarmHasFired == TRUE)
                {
                    g_alarmHasFired = FALSE;
                    alarmAction();
                }

                 mainMenuChoice = RTE_KEYPAD_getPressedKey();

             } while(!(mainMenuChoice == SET_ALARM_CHOICE ||
                     mainMenuChoice == CANCEL_ALARM_CHOICE ||
                     mainMenuChoice == ALARM_LIST_CHOICE));

         if(mainMenuChoice == SET_ALARM_CHOICE){
                state = App_setAlarm();
             } else if(mainMenuChoice == CANCEL_ALARM_CHOICE){
                App_cancelAlarm();

             } else if(mainMenuChoice == ALARM_LIST_CHOICE){
                App_listAlarm();
             } else{
                /*Do nothing*/
             }
         /*G flag check*/
         if(g_alarmHasFired == TRUE)
         {
             g_alarmHasFired = FALSE;
             alarmAction();
         }

        }



}


 STATUS App_setAlarm()
 {
     if(g_alarmHasFired == TRUE)
     {
         g_alarmHasFired = FALSE;
         alarmAction();
     }
     char tempalarmdigits[4];
     uint8 exit_Flag = 0;
     uint8 keypadBuffer,indexOfFirstavailablealarm,i;
     indexOfFirstavailablealarm = 9;
     RTE_LCD_clearScreen();

     while (exit_Flag == 0)
     {
      RTE_LCD_clearScreen();
     for(i=0;i<MaximumAlarms;i++)
     {
         if (alarms[i].flag == FALSE) {
             indexOfFirstavailablealarm = i;
             break;
         }
     }

     if(indexOfFirstavailablealarm == 9){
         exit_Flag=1;
         RTE_LCD_displayString("Number of Alarms limit exceeded");
         continue;
     }

     RTE_LCD_moveCursor(0 , 0);
     RTE_LCD_displayString("Enter Desired Time  ");

     /*LCD display "Enter desired time"*/

     for(i=0; i<4;i++)
     {
//
         /*If 0>array[1]>5 continue , if 0>array[0]>9*/
         if(i%2 == 0)
         {
            do{
                if(g_alarmHasFired == TRUE)
                {
                    g_alarmHasFired = FALSE;
                    alarmAction();
                }
                 keypadBuffer = RTE_KEYPAD_getPressedKey();

                 if(i ==2) RTE_LCD_moveCursor(2 , 10-i-1);

                 else RTE_LCD_moveCursor(2 , 10-i);
             }
             while((keypadBuffer>9) || (keypadBuffer<0));

            tempalarmdigits[i]= keypadBuffer;
             //RTE_LCD_moveCursor(2 , 10-i);
             RTE_LCD_integerToString(keypadBuffer);
         }
         else
         {
             do{
                 keypadBuffer = RTE_KEYPAD_getPressedKey();
                 if(i == 3) RTE_LCD_moveCursor(2 , 10-i-1);

                  else RTE_LCD_moveCursor(2 , 10-i);

             }
             while(keypadBuffer>5 || keypadBuffer<0);

             tempalarmdigits[i] = keypadBuffer;

             RTE_LCD_integerToString(keypadBuffer);
         }
         if(i == 1)
                  {
                      RTE_LCD_moveCursor(2 , 10-i-1);
                      RTE_LCD_displayCharacter(':');
                  }
     }
     _delay_ms(500);
     RTE_LCD_clearScreen();
     RTE_LCD_displayString("To Confirm, Press 1");
     RTE_LCD_moveCursor(1,0);
     RTE_LCD_displayString("To go back, Press 0");
     RTE_LCD_moveCursor(2 , 0);
         RTE_LCD_displayString("To Exit, Press 2");
     RTE_LCD_moveCursor(3 , 7);
     RTE_LCD_integerToString(tempalarmdigits[3]);
     RTE_LCD_integerToString(tempalarmdigits[2]);
     RTE_LCD_displayCharacter(':');
  /*LCD display "  :  " in coordinates in the middle of the screen*/
     RTE_LCD_moveCursor(3 , 10);
     RTE_LCD_integerToString(tempalarmdigits[1]);
     RTE_LCD_integerToString(tempalarmdigits[0]);


   do{
                    keypadBuffer = RTE_KEYPAD_getPressedKey();
                }
                while(keypadBuffer>2 || keypadBuffer<0);

                if(keypadBuffer == 1)
                    {

                        for(i=0; i<4;i++){
                            alarms[indexOfFirstavailablealarm].alarmDigits[i] = tempalarmdigits[i];
                        }
                        alarms[indexOfFirstavailablealarm].secCnt = (((alarms[indexOfFirstavailablealarm].alarmDigits[3]*10)+(alarms[indexOfFirstavailablealarm].alarmDigits[2]))*60)+((alarms[indexOfFirstavailablealarm].alarmDigits[1]*10)+(alarms[indexOfFirstavailablealarm].alarmDigits[0]));
                        alarms[indexOfFirstavailablealarm].flag = TRUE;
                        RTE_TIMER1_vidStart();
                        exit_Flag = 1;
                        return indexOfFirstavailablealarm;
                    }
                else if(keypadBuffer == 0)continue;
                else if(keypadBuffer == 2)
                    {   exit_Flag = 1;
                        return CANCELLED;}
                else{
                    return 8;
                }



     }


     /*Get keypressed four times only*/
     /*if key not entered within timeout exit */

     /*Display keypressed overwriting over previous LCD display*/


     /*Store the time set*/

     /* */
     return 8;

 }

 STATUS App_cancelAlarm(){

     RTE_LCD_clearScreen();

     uint8 i,keypadBuffer;

     for(i=0;i<MaximumAlarms;i++)

     {
              if (alarms[i].flag == TRUE)
              {

                          RTE_LCD_moveCursor(i,0);
                           RTE_LCD_displayString("Alarm");
                           RTE_LCD_moveCursor(i,6);
                           RTE_LCD_integerToString(i);
                           RTE_LCD_moveCursor(i,8);
                           RTE_LCD_displayString("-> ");
                           RTE_LCD_moveCursor(i , 13);

                           RTE_LCD_integerToString(alarms[i].alarmDigits[3]);
                           RTE_LCD_integerToString(alarms[i].alarmDigits[2]);
                           RTE_LCD_displayCharacter(':');
                        /*LCD display "  :  " in coordinates in the middle of the screen*/
                           RTE_LCD_moveCursor(i , 16);
                           RTE_LCD_integerToString(alarms[i].alarmDigits[1]);
                           RTE_LCD_integerToString(alarms[i].alarmDigits[0]);
              }
                  else {
                  RTE_LCD_moveCursor(i , 0);
                  RTE_LCD_displayString("Alarm ");
                  RTE_LCD_integerToString(i);
                  RTE_LCD_displayString(" isn't set");
              }

          }


     do{
                      keypadBuffer = RTE_KEYPAD_getPressedKey();

                  }
                  while((keypadBuffer>4) || (keypadBuffer<0));

     if(keypadBuffer == 4)
      {
          return CANCELLED;
      }

     for(i=0;i<MaximumAlarms;i++)
               {
                   if (keypadBuffer == i) {
                       if(alarms[i].flag == FALSE){
                           RTE_LCD_clearScreen();
                           RTE_LCD_displayString("Alarm ");
                           RTE_LCD_integerToString(i);
                           RTE_LCD_displayString(" is not set");
                           _delay_ms(1000);
                       }
                       else{
                       alarms[i].flag = FALSE;
                       alarms[i].flag = FALSE;
                                       alarms[i].alarmDigits[0] = 0;
                                       alarms[i].alarmDigits[1] = 0;
                                       alarms[i].alarmDigits[2] = 0;
                                       alarms[i].alarmDigits[3] = 0;
                                       alarms[i].secCnt = 0;
                       /*Here: Alarm digits is not deleted*/
                       RTE_LCD_clearScreen();
                       RTE_LCD_moveCursor(0,0);
                       RTE_LCD_displayString("Alarm ");
                       RTE_LCD_integerToString(i);
                       RTE_LCD_displayString(" cancelled");
                       _delay_ms(2000);
                   }
                   }

               }

return CONFIRMED;

 }
/*==================================================================*/
/*                           ISR Body                               */
/*==================================================================*/
void Interrupt_function(void)
{
    /*if (alarms[0].flag){
     RTE_LCD_moveCursor((3),14);
     RTE_LCD_integerToString(alarms[0].alarmDigits[3]);
     RTE_LCD_integerToString(alarms[0].alarmDigits[2]);
     RTE_LCD_displayCharacter(':');
     RTE_LCD_moveCursor((3),17);
     RTE_LCD_integerToString(alarms[0].alarmDigits[1]);
     RTE_LCD_integerToString(alarms[0].alarmDigits[0]);

     if (alarms[0].alarmDigits[0] > 0)
     {
         alarms[0].alarmDigits[0]--;

     }
     else if (alarms[0].alarmDigits[1] > 0)
     {
         alarms[0].alarmDigits[0] = 9;
         alarms[0].alarmDigits[1]--;
     }
     else if (alarms[0].alarmDigits[2] > 0)
     {
         alarms[0].alarmDigits[0] = 9;
         alarms[0].alarmDigits[1] = 5;
         alarms[0].alarmDigits[2]--;
     }
     else if (alarms[0].alarmDigits[3] > 0)
     {
         alarms[0].alarmDigits[0] = 9;
         alarms[0].alarmDigits[1] = 5;
         alarms[0].alarmDigits[2] = 9;
         alarms[0].alarmDigits[3]--;
      }
      }*/
    for (uint8 i = 0; i < MaximumAlarms; i++)
    {
            if (alarms[i].flag)
            {
                if (alarms[i].secCnt == 0)
                {

                        g_alarmHasFired = TRUE;
                        g_NowFiredAlarm = i;
                        alarms[i].flag=FALSE;

                }
                alarms[i].secCnt--;
            }

    }


}




STATUS alarmAction()
{
    STATUS UserIn;
    readingLDR = 0;
    RTE_TIMER0_vidStart();

     //uint8 currentPosition = 0;
    RTE_Buzzer_TurnOnOff(TRUE);
    RTE_LCD_clearScreen();

    RTE_LCD_moveCursor(0,0);
    RTE_LCD_displayString("Alarm ");
    RTE_LCD_integerToString(g_NowFiredAlarm);
    RTE_LCD_displayString(" is Off");
    _delay_ms(1);

    while(readingLDR<LDR_THRESHOLD)
    {
        readingLDR = LDR_u16GetLDRReadingSync(ADC_CHANNEL_0);
        _delay_ms(100);
    }

    RTE_LCD_moveCursor(1,0);
    RTE_LCD_displayString("Solve to close Alarm");
    RTE_LCD_moveCursor(2,0);

    UserIn = WakeUpCalculator();

    if(UserIn == CONFIRMED)
    {
        RTE_LCD_clearScreen();
        RTE_LCD_displayString("Good Morning");
        _delay_ms(900);

        //LED_All_Off();
        LCD_clearScreen();
        RTE_Buzzer_TurnOnOff(FALSE);
        LCD_displayString("Alarm closed!");
        _delay_ms(800);
        RTE_Buzzer_TurnOnOff(FALSE);
    }
        RTE_TIMER0_vidStop();
        LED_All_Off();
        App();
        return CONFIRMED;



}



STATUS WakeUpCalculator()
{
    uint32 result = 0;
    uint32 userAnswer = 0;
    uint8 answerCorrect = FALSE;
    uint8 keyPadBuffer;
    uint8 cases = g_NowFiredAlarm;
    switch(cases){

            case 0: result = 10 + 2 * 4;
                    RTE_LCD_displayString(" 10 + 2 * 4 =");
                    numOfDigits = 2;
                    break;
            case 1: result = 21 - 5 * 4;
                    RTE_LCD_displayString(" 21 - 5 * 4 =");
                    numOfDigits = 1;
                    break;
            case 2: result = 80 + 1 * 4 - 5;
                    RTE_LCD_displayString(" 80 + 1 * 4 - 5 =");
                    numOfDigits = 2;
                    break;
            case 3: result = 2;
                    RTE_LCD_displayString(" 10 - 4 * 2 =");
            break;
            default: ;
        }

              do
              {
                  userAnswer  =0;

                  for(uint8 i =0;i<numOfDigits;i++)
                  {
                      keyPadBuffer = RTE_KEYPAD_getPressedKey();
                      RTE_LCD_moveCursor(2,17+i);
                      RTE_LCD_integerToString(keyPadBuffer);
                      _delay_ms(80);
                      userAnswer = userAnswer * 10 + keyPadBuffer;
                  }

                  if(userAnswer == result)
                  {
                      answerCorrect = TRUE;
                      RTE_LCD_moveCursor(2,17);
                      RTE_LCD_integerToString(userAnswer);
                      _delay_ms(150);
                      return CONFIRMED;
                  }
                  else
                  {
                      RTE_LCD_moveCursor(3,0);
                      LCD_displayString("Wrong !");
                      RTE_LCD_moveCursor(2,17);
                      LCD_displayString("  ");
                  }

               } while(keyPadBuffer>9 || keyPadBuffer<0 || (answerCorrect == FALSE));

                 /* RTE_LCD_moveCursor(2,17);
                  RTE_LCD_integerToString(userAnswer);
                  _delay_ms(100);*/

                return 8;

}

STATUS App_listAlarm(){

RTE_LCD_clearScreen();

     uint8 i,keypadBuffer;


     for(i=0;i<MaximumAlarms;i++)

     {
              if (alarms[i].flag == TRUE)
              {

                          RTE_LCD_moveCursor(i,0);
                           RTE_LCD_displayString("Alarm");
                           RTE_LCD_moveCursor(i,6);
                           RTE_LCD_integerToString(i);
                           RTE_LCD_moveCursor(i,8);
                           RTE_LCD_displayString("-> ");
                           RTE_LCD_moveCursor(i , 13);

                           RTE_LCD_integerToString(alarms[i].alarmDigits[3]);
                           RTE_LCD_integerToString(alarms[i].alarmDigits[2]);
                           RTE_LCD_displayCharacter(':');
                        /*LCD display "  :  " in coordinates in the middle of the screen*/
                           RTE_LCD_moveCursor(i , 16);
                           RTE_LCD_integerToString(alarms[i].alarmDigits[1]);
                           RTE_LCD_integerToString(alarms[i].alarmDigits[0]);
              }
                  else {
                  RTE_LCD_moveCursor(i , 0);
                  RTE_LCD_displayString("Alarm ");
                  RTE_LCD_integerToString(i);
                  RTE_LCD_displayString(" isn't set");
              }

          }


     do{
                      keypadBuffer = RTE_KEYPAD_getPressedKey();

                  }
                  while((keypadBuffer>5) || (keypadBuffer<4));

     if(keypadBuffer == 1)
     {
         return CANCELLED;
     }

     return CONFIRMED;

}


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


void LEDdimmingCompareMatch(){

    LED_Toggle(LED_BLUE);
    LED_Toggle(LED_RED);
    LED_Toggle(LED_GREEN);
    LED_Toggle(LED_YELLOW);
}

/*==================================================================*/
/*                 Welcome Screen Display                           */
/*==================================================================*/
void App_welcomeScreen()
{
    /* Initialize LCD */
    LCD_clearScreen();

    /* Display Team Information */
    LCD_moveCursor(1, 0);

    LCD_displayString(TEAM);
    _delay_ms(50);          /* Delay for 50 milli seconds */
    LCD_clearScreen();
    LCD_moveCursor(1, 0);
    LCD_displayString(TEAM_REVERSE);
    _delay_ms(50);          /* Delay for 50 milli seconds */
    LCD_clearScreen();
    LCD_moveCursor(1, 0);
    LCD_displayString(TEAM);
    _delay_ms(2000);        /* Delay for 2 seconds */
    LCD_clearScreen();
    LCD_moveCursor(0, 0);
    LCD_displayString(NAME_1);
    LCD_moveCursor(1, 0);
    LCD_displayString(NAME_2);
    LCD_moveCursor(2, 0);
    LCD_displayString(NAME_3);
    LCD_moveCursor(3, 0);
    LCD_displayString(NAME_4);
    _delay_ms(700);     /* Delay for 1 second */
    LCD_clearScreen();
    LCD_moveCursor(1, 0);
    LCD_displayString(NAME_5);
    _delay_ms(700);         /* Delay for 3 seconds */

    /* Display class and company info */
    LCD_clearScreen();
    LCD_moveCursor(0,0);
    LCD_displayString(COMPANY);
    LCD_moveCursor(1,0);
    LCD_displayString(CLASS);
    _delay_ms(700);     /* Delay for 3 seconds */

    /* Display Welcome Message */
    LCD_clearScreen();
    LCD_moveCursor(1, 3);
    LCD_displayString(WELCOME);
    _delay_ms(700);         /* Delay for 2 seconds */


    /* Display Start Engine Message */
    LCD_clearScreen();
    LCD_moveCursor(1, 1);
    LCD_displayString(START_PROJ);
    _delay_ms(700);     /* Delay for 2 seconds */
}


