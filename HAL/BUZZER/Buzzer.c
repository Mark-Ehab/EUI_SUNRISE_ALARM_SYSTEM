/*
 * Buzzer.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Administrator
 */


#include "Buzzer.h"


void Buzzer_Init (void)
{
	DIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
}


void Buzzer_TurnOnOff (uint8 Turn)
{
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,Turn);
}
