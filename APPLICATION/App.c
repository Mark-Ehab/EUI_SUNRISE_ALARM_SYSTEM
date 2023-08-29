/********************************************************************/
/*      SWC     : App.c		                                        */
/*      Date    : 8/28/2023                                         */
/*      Authors : MetaWare LLC                                      */
/*				  Mahmoud Sayed Mahmoud Helmy (1285)                */
/*		          Mohamed Mahmoud Masoud (200)                      */
/*		          Mark Ehab Tawfik (201)                            */
/*		          Hazzem Mohamed Ezzeldin (1297)                    */
/*		          Yousef Khaled Ahmed (558)                         */
/********************************************************************/

#include "App.h"

/* this is the counter that counts how many alarms are used */
uint8 g_alarm_cnt = 1;

/* array of Alarm_config structure that holds the required    *
 * configuration of each alarm.                               */
Alarm_config alarms[MaximumAlarms] = {
		{FALSE , {AlarmInitialValue}, 0}, /* alarm 0 */
		{FALSE , {AlarmInitialValue}, 0}, /* alarm 1 */
		{FALSE , {AlarmInitialValue}, 0}, /* alarm 2 */
		{FALSE , {AlarmInitialValue}, 0}  /* alarm 3 */
};

/***********************************************************************************
 * Service Name: App_init
 * Syntax: void App_init(void)
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: initializes the used drivers as LCD and Keypad
 ***********************************************************************************/
void App_init(void){
	LCD_init_(); /* LCD initialization */
	KEYPAD_init_(); /* keypad initialization */
}

/**********************************************
 * Service Name: App_mainMenu
 * Syntax: void App_mainMenu(void)
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: displays the main menu
 **********************************************/
void App_mainMenu(void){
	/* clearing the LCD */
	LCD_clearScreen();
	/* moving the cursor to the first row and first column*/
	LCD_moveCursor(0,0);
	LCD_displayString("+Set Alarm   |");
	/* moving the cursor to the second row and first column*/
	LCD_moveCursor(1,0);
	LCD_displayString("-Cancel Alarm|");
	/* moving the cursor to the third row and first column*/
	LCD_moveCursor(2,0);
	LCD_displayString("*Alarm List  |");
	/* moving the cursor to the fourth row and first column*/
	LCD_moveCursor(3,0);
	LCD_displayString("             |");
}

/***********************************************************************************
 * Service Name: App_firstAvailableAlarm
 * Syntax: void App_firstAvailableAlarm(uint8* avialableAlramBuffer)
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): avialableAlramBuffer
 * Return value: void
 * Description: searches in the alarms array about which alarm is
 * 				available(i.e.,which alarm that its flag is not set)
 ***********************************************************************************/
void App_firstAvailableAlarm(uint8* avialableAlramBuffer){
	/* flag that is raised if an available alarm is found*/
	uint8 alarmFoundFlag = FALSE;
	/* this variable represents the alarm id */
	uint8 alarm_id;
	/* this loop searches in the array for the first available   *
	 * alarm to be set(i.e., not set one)                     */
	for(alarm_id = 0 ; ((alarm_id < MaximumAlarms) && !(alarmFoundFlag)) ; alarm_id++){
		/* this condition checks on the status of the flag of   *
		 * each alarm.                                          */
		if(alarms[(int)alarm_id].flag == FALSE){
			/* is the alarm flag is not set then we found the   *
			 * first available alarm to be set then we set the  *
			 * flag that indicates that an available alarm is   *
			 * found.                                           */
			alarmFoundFlag = TRUE;
			/* assigning the passed buffer with the found alarm id. */
			*avialableAlramBuffer = alarm_id;
		}
	}
}

/***********************************************************************************
 * Service Name: App_setAlarm
 * Syntax: void App_setAlarm(void)
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: this function is responsible of setting the alarm
 *              with the minutes and seconds that the user is going
 *              to enter.
 ***********************************************************************************/
void App_setAlarm(void){
	/* this is the variable that will be passed to the function  *
	 * App_firstAvailableAlarm where it will hold the id of the  *
	 * first available alarm.                                    */
	uint8 firstAvailableAlarm;
	/* this buffer will hold the value that will return from the  *
	 * keypad.                                                    */
	uint8 keypad_readBuffer;
	/* this is the counter that will used in the loop that will  *
	 * save the minutes and seconds values that will be entered  *
	 * from the user.                                            */
	uint8 placeCnt;
	/* this counter will hold the value of the minutes */
	uint8 tempCnt = 0;
	/* this is the variable that the is passed by address to the  *
	 * keypad to hold the choice of the user whether he or she    *
	 * wants to cancel and return to the main menu or to continue */
	uint8 cancelOrContinue;
	/* here we are setting the LCD to display continue or close *
	 * options.                                                 */
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("please choose:");
	LCD_moveCursor(1,3);
	LCD_displayString("0.[continue]");
	LCD_moveCursor(2,3);
	LCD_displayString("%.[close]");
	/* here we are taking the input from the user to continue *
	 * or cancel.                                             */
	cancelOrContinue = KEYPAD_getPressedKey();
	/* checking on the user choice if continue or return to the   *
	 * main menu                                                  */
	if(cancelOrContinue == CONTINUE){
		/* setting the LCD to display this sentence. */
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("Set the alarm:");
		/* checking is the counter of the alarms reaches the maximum *
		 * amount of the allowed alarms or not(i.e., is there any    *
		 * more available alarms or not).                            */
		if(g_alarm_cnt <= MaximumAlarms){
			/* incrementing the counter of the alarms by one */
			g_alarm_cnt++;
			/* calling the function that will search for the     *
			 * first available alarm to hold the desired minutes *
			 * and seconds that will be set by the user.         */
			App_firstAvailableAlarm(&firstAvailableAlarm);
			/* setting the flag of the alarm(i.e, this flag  *
			 * isn't available any more).                    */
			alarms[(int)firstAvailableAlarm].flag = TRUE;
			/* setting up the LCD to display the choices of the *
			 * user.                                            */
			LCD_moveCursor(2 , 9);
			LCD_displayCharacter(':');
			LCD_moveCursor(2 , 7);
			/* looping to get the minutes and seconds then saving *
			 * them.                                              */
			for(placeCnt = 4 ; placeCnt>0 ; placeCnt--){
				/* if we are in the tens of the minutes */
				if(placeCnt == MINUTES_TENS){
					/* we are using do while loop to first    *
					 * get the minute's tens from the user    *
					 * then checking whether it is more than  *
					 * 6 or not.                              */
					do{
						/* getting the minute's tens from the user */
						keypad_readBuffer = KEYPAD_getPressedKey();
						/* displaying the user choice */
						LCD_moveCursor(2 , 7);
						LCD_integerToString(keypad_readBuffer);
						/*saving the minute's tens in the array *
						 * of the minutes and seconds that are  *
						 * specific to this alarm.              */
						alarms[(int)firstAvailableAlarm].alarmDigits[0] = keypad_readBuffer;
					}while((keypad_readBuffer > MAX_MINUTES_TENS));
				} else if(placeCnt == 3){
					do{
						keypad_readBuffer = KEYPAD_getPressedKey();
						LCD_moveCursor(2 , 8);
						LCD_integerToString(keypad_readBuffer);
						alarms[(int)firstAvailableAlarm].alarmDigits[1] = keypad_readBuffer;
					}while(((keypad_readBuffer != 0) &&(alarms[(int)firstAvailableAlarm].alarmDigits[0] == 6)));
					tempCnt = alarms[(int)firstAvailableAlarm].alarmDigits[0] * 10
							+ alarms[(int)firstAvailableAlarm].alarmDigits[1];
					alarms[(int)firstAvailableAlarm].secCnt += tempCnt*60;
				} else if(placeCnt == 2){
					do{
						keypad_readBuffer = KEYPAD_getPressedKey();
						LCD_moveCursor(2 , 10);
						LCD_integerToString(keypad_readBuffer);
						alarms[(int)firstAvailableAlarm].alarmDigits[2] = keypad_readBuffer;
					}while((keypad_readBuffer > 6));
				} else if(placeCnt == 1){
					do{
						keypad_readBuffer = KEYPAD_getPressedKey();
						LCD_moveCursor(2 , 11);
						LCD_integerToString(keypad_readBuffer);
						alarms[(int)firstAvailableAlarm].alarmDigits[3] = keypad_readBuffer;
					}while(((keypad_readBuffer != 0) &&(alarms[(int)firstAvailableAlarm].alarmDigits[2] == 6)));
					alarms[(int)firstAvailableAlarm].secCnt += (alarms[(int)firstAvailableAlarm].alarmDigits[2] * 10)
										        				+ alarms[(int)firstAvailableAlarm].alarmDigits[3];
				}
			}
		} else{
			LCD_clearScreen();
			LCD_moveCursor(1,0);
			LCD_displayString("no more available");
			LCD_moveCursor(2,0);
			LCD_displayString("alarms");
		}
		_delay_ms(500);
	} else{
		/* here the user chose to return to the main menu */
	}
}

void App_listAlarm(void){
	uint8 lcd_row = 0;
	uint8 alarmListChoiceCancel;
	uint8 noAlarmsFlag = FALSE;
	LCD_clearScreen();
	LCD_moveCursor(1,3);
	LCD_displayString("0.[show]");
	LCD_moveCursor(2,3);
	LCD_displayString("%.[close]");
	do{
		alarmListChoiceCancel = KEYPAD_getPressedKey();
		if(alarmListChoiceCancel != '%'){ /* this check for the first time*/
			LCD_clearScreen();
			if(!(alarms[0].flag || alarms[1].flag || alarms[2].flag || alarms[3].flag)){
				LCD_displayString("no alarms are set yet");
				_delay_ms(1000);
				noAlarmsFlag = TRUE;
			} else{
				for(uint8 i =0 ; i<MaximumAlarms ; i++){
					if(alarms[(int)i].flag){
						LCD_moveCursor(lcd_row++ , 0);
						LCD_displayString("Alarm: ");
						LCD_integerToString(i);
						LCD_displayString(" -> ");
						LCD_integerToString(alarms[(int)i].alarmDigits[0]);
						LCD_integerToString(alarms[(int)i].alarmDigits[1]);
						LCD_displayCharacter(':');
						LCD_integerToString(alarms[(int)i].alarmDigits[2]);
						LCD_integerToString(alarms[(int)i].alarmDigits[3]);
					}
				}
			}
		}
		lcd_row = 0;
	}while(alarmListChoiceCancel != '%' && !(noAlarmsFlag));
}

void App_cancelAlarm(void){
	uint8 chosenAlarm;
	uint8 lcd_row = 0;
	uint8 alarmChosenFlag = FALSE;
	uint8 cancelOrContinue = FALSE;
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("please choose:");
	LCD_moveCursor(1,3);
	LCD_displayString("0.[continue]");
	LCD_moveCursor(2,3);
	LCD_displayString("%.[close]");
	cancelOrContinue = KEYPAD_getPressedKey();
	if(cancelOrContinue == CONTINUE){
		if(!(alarms[0].flag || alarms[1].flag || alarms[2].flag || alarms[3].flag)){
			LCD_clearScreen();
			LCD_displayString("no alarms are set");
			_delay_ms(1000);
		} else{
			do{
				if(alarmChosenFlag){
					LCD_clearScreen();
					LCD_displayString("you chose a un valid");
					LCD_moveCursor(1,8);
					LCD_displayString("ID");
					LCD_moveCursor(2,3);
					LCD_displayString("please choose:");
					LCD_moveCursor(3,0);
					LCD_displayString("0.[Yes]  %.[close]");
					cancelOrContinue = KEYPAD_getPressedKey();
				} else{
					/* do nothing */
				}
				if(cancelOrContinue == CONTINUE){
					LCD_clearScreen();
					for(uint8 i =0 ; i<MaximumAlarms ; i++){
						if(alarms[(int)i].flag){
							LCD_moveCursor(lcd_row++ , 0);
							LCD_displayString("Alarm: ");
							LCD_integerToString(i);
							LCD_displayString(" -> ");
							LCD_integerToString(alarms[(int)i].alarmDigits[0]);
							LCD_integerToString(alarms[(int)i].alarmDigits[1]);
							LCD_displayCharacter(':');
							LCD_integerToString(alarms[(int)i].alarmDigits[2]);
							LCD_integerToString(alarms[(int)i].alarmDigits[3]);
						}
					}
					LCD_moveCursor(0,17);
					LCD_displayCharacter('|');
					LCD_moveCursor(1,17);
					LCD_displayCharacter('|');
					LCD_moveCursor(2,17);
					LCD_displayCharacter('|');
					LCD_moveCursor(3,17);
					LCD_displayCharacter('|');
					chosenAlarm = KEYPAD_getPressedKey();
					alarmChosenFlag = TRUE;
				} else{
					alarmChosenFlag = FALSE;
				}
			}while((alarms[(int)chosenAlarm].flag == FALSE) &&
					(alarmChosenFlag == TRUE));
			--g_alarm_cnt;
			if(alarmChosenFlag == TRUE){
				alarms[(int)chosenAlarm].flag = FALSE;
				alarms[(int)chosenAlarm].alarmDigits[0] = 0;
				alarms[(int)chosenAlarm].alarmDigits[1] = 0;
				alarms[(int)chosenAlarm].alarmDigits[2] = 0;
				alarms[(int)chosenAlarm].alarmDigits[3] = 0;
				alarms[(int)chosenAlarm].secCnt = 0;
				LCD_clearScreen();
				LCD_moveCursor(1,0);
				LCD_displayString("alarm ");
				LCD_integerToString((int)chosenAlarm);
				LCD_displayString(" is cancelled");
				_delay_ms(2000);
			}
		}
	}
}


void App_main(void){
	uint8 mainMenuChoice = FALSE;
	App_mainMenu();
	do{
		mainMenuChoice = KEYPAD_getPressedKey();
	} while(!(mainMenuChoice == SET_ALARM_CHOICE ||
			mainMenuChoice == CANCEL_ALARM_CHOICE ||
			mainMenuChoice == ALARM_LIST_CHOICE));
	if(mainMenuChoice == SET_ALARM_CHOICE){
		App_setAlarm();
	} else if(mainMenuChoice == CANCEL_ALARM_CHOICE){
		App_cancelAlarm();
	} else if(mainMenuChoice == ALARM_LIST_CHOICE){
		App_listAlarm();
	} else{
		/* do nothing */
	}
}