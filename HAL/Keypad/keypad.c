/*
 * keypad.c
 *
 *  Created on: Aug 20, 2023
 *      Author: MetaWare LLC
		Mahmoud Sayed Mahmoud Helmy (1285)
		Mohamed Mahmoud Masoud (200)
		Mark Ehab Tawfik (201)
		Hazzem Mohamed Ezzeldin (1297)
		Yousef Khaled Ahmed (558)
 */


#include "keypad.h"

/* Column and row initialization constants */
#define COL_INIT    0
#define COL_FINAL   3
#define ROW_INIT    0
#define ROW_FINAL   3

/* Pin IDs for rows and columns */
uint8 ArrOfRows[4] = {PIN5_ID, PIN4_ID, PIN3_ID, PIN2_ID};
uint8 ArrOfCols[4] = {PIN7_ID, PIN6_ID, PIN5_ID, PIN3_ID};

/* Keypad character values */
const uint8 KeyPad_Values[4][4] = {
	{1, 2, 3,43},
	{4, 5, 6,'-'},
	{7, 8, 9,'/'},
	{'*',0,'#','='}
};

/* Initialize the keypad */
void KeyPad_Init(void) {
	/* Configure columns as input pins */
	DIO_setupPinDirection(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN0, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN1, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN2, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN3, PIN_INPUT);

	/* Configure rows as input pins and set them to logic high */
	DIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW0, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW1, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW2, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW3, PIN_INPUT);

	DIO_writePin(KEYPAD_ROW_PORT, KEYPAD_ROW0, LOGIC_HIGH);
	DIO_writePin(KEYPAD_ROW_PORT, KEYPAD_ROW1, LOGIC_HIGH);
	DIO_writePin(KEYPAD_ROW_PORT, KEYPAD_ROW2, LOGIC_HIGH);
	DIO_writePin(KEYPAD_ROW_PORT, KEYPAD_ROW3, LOGIC_HIGH);
}

/* Get the pressed key */
uint8 GetPresseKey(void) {
	uint8 i, j, val;
	if(g_alarmHasFired == TRUE)
	                {
	                    g_alarmHasFired = FALSE;
	                    alarmAction();
	                }
	while (1) {
		/* Iterate through rows */
	    if(g_alarmHasFired == TRUE)
	                    {
	                        g_alarmHasFired = FALSE;
	                        alarmAction();
	                    }
		for (i = 0; i < 4; i++) {
			/* Set the current row to logic low */
			DIO_setupPinDirection(KEYPAD_ROW_PORT, ArrOfRows[i], PIN_OUTPUT);
			DIO_writePin(KEYPAD_ROW_PORT, ArrOfRows[i], LOGIC_LOW);
			if(g_alarmHasFired == TRUE)
			                {
			                    g_alarmHasFired = FALSE;
			                    alarmAction();
			                }
			/* Check columns for a pressed key */
			for (j = 0; j < 4; j++) {
				val = DIO_readPin(KEYPAD_COLUMN_PORT, ArrOfCols[j]);
				if(g_alarmHasFired == TRUE)
				                {
				                    g_alarmHasFired = FALSE;
				                    alarmAction();
				                }
				if (val == 0) {
					_delay_ms(50); // Small delay to debounce the key press
					while (val == 0) {
						val = DIO_readPin(KEYPAD_COLUMN_PORT, ArrOfCols[j]);
					}
					/* Restore row configuration and return the key value */
					DIO_setupPinDirection(KEYPAD_ROW_PORT, ArrOfRows[i], PIN_INPUT);
					DIO_writePin(KEYPAD_ROW_PORT, ArrOfRows[i], LOGIC_HIGH);
					if(g_alarmHasFired == TRUE)
					                {
					                    g_alarmHasFired = FALSE;
					                    alarmAction();
					                }
					return (KeyPad_Values[i][j]);
				}
			}
			if(g_alarmHasFired == TRUE)
			                {
			                    g_alarmHasFired = FALSE;
			                    alarmAction();
			                }
			/* Restore row configuration */
			DIO_setupPinDirection(KEYPAD_ROW_PORT, ArrOfRows[i], PIN_INPUT);
			DIO_writePin(KEYPAD_ROW_PORT, ArrOfRows[i], LOGIC_HIGH);
		}
	}
}


