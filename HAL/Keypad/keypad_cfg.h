/*
 * keypad_cfg.h
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
#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/* =============================================================
 * 						Keypad_Configuration
 * =============================================================*/
/** @addtogroup Keypad_Configuration
 * @{
 */

/**
 * @brief The port to which the keypad columns are connected.
 * Define the port to which the keypad columns are connected, e.g., PORTD_ID.
 */
#define KEYPAD_COLUMN_PORT  PORTD_ID

/**
 * @brief The port to which the keypad rows are connected.
 * Define the port to which the keypad rows are connected, e.g., PORTC_ID.
 */
#define KEYPAD_ROW_PORT     PORTC_ID

/**
 * @brief The pins corresponding to keypad columns.
 * Define the pins corresponding to keypad columns, e.g., KEYPAD_COLUMN0 as PIN7_ID.
 */
#define KEYPAD_COLUMN0      PIN7_ID
#define KEYPAD_COLUMN1      PIN6_ID
#define KEYPAD_COLUMN2      PIN5_ID
#define KEYPAD_COLUMN3      PIN3_ID

/**
 * @brief The pins corresponding to keypad rows.
 * Define the pins corresponding to keypad rows, e.g., KEYPAD_ROW0 as PIN5_ID.
 */
#define KEYPAD_ROW0         PIN5_ID
#define KEYPAD_ROW1         PIN4_ID
#define KEYPAD_ROW2         PIN3_ID
#define KEYPAD_ROW3         PIN2_ID
/** @} */

#endif /* KEYPAD_CFG_H_ */
