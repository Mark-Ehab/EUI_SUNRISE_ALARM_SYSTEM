/*
 * Buzzer.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Administrator
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "atmega32_DIO.h"


#define BUZZER_PORT		PORTC_ID
#define BUZZER_PIN		PIN6_ID

#define TURN_OFF		0
#define TURN_ON			1

void Buzzer_Init (void);
void Buzzer_TurnOnOff (uint8 Turn);

#endif /* BUZZER_H_ */
