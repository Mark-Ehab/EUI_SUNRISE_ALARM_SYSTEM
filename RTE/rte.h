/*
 * rte.h
 *
 *  Created on: Aug 29, 2023
 *      Author: youss
 */

#ifndef RTE_H_
#define RTE_H_

#include "../HAL/LCD/AVR_LCD.h"
#include "../HAL/Keypad/keypad.h"
#include "../Commons/std_types.h"
#include "../HAL/LED/LED.h"

#define RTE_KEYPAD_init KeyPad_Init
#define RTE_KEYPAD_getPressedKey GetPresseKey
#define RTE_LCD_init LCD_init
#define RTE_LCD_displayCharacter LCD_displayCharacter
#define RTE_LCD_displayString LCD_displayString
#define RTE_LCD_integerToString LCD_integerToString
#define RTE_LCD_clearScreen LCD_clearScreen
#define RTE_LCD_moveCursor LCD_moveCursor


#endif /* RTE_H_ */
