/*
 * keypad.h
 *
 *  Created on: Aug 20, 2023
 *      Author: MetaWare LLC
		Mahmoud Sayed Mahmoud Helmy (1285)
		Mohamed Mahmoud Masoud (200)
		Mark Ehab Tawfik (201)
		Hazzem Mohamed Ezzeldin (1297)
		Yousef Khaled Ahmed (558)
 */
/* =============================================================
 * 							File Guard
 * =============================================================*/
#ifndef KEYPAD_H_
#define KEYPAD_H_
/* =============================================================
 * 							Includes
 * =============================================================*/
#include "keypad_cfg.h"
#include "../../Commons/std_types.h"
#include "../../MCAL/DIO/atmega32_DIO.h"
/* =============================================================
 * 						Function Prototypes
 * =============================================================*/
/**
 * @brief Initialize the keypad hardware.
 *
 * This function sets up the necessary pin directions and initial logic levels
 * for the keypad rows and columns.
 */
void KeyPad_Init(void);

/**
 * @brief Get the pressed key from the keypad.
 *
 * This function scans through the keypad rows and columns to detect a pressed key.
 *
 * @return The ASCII value of the pressed key. If no key is pressed, returns 0.
 */
uint8 GetPresseKey(void);

#endif /* KEYPAD_H_ */
