/*================================================================
					  _      ____  ____                       
					 | |    / ___||  _ \                      
					 | |   | |    | | | |                     
					 | |___| |___ | |_| |                     
					 |_____|\____||____/                      
                        
/*================================================================*/				  
/*      HAL     : LCD                      
/*      Date    : 8/26/2023                                        
/*      Authors : MetaWare LLC                                     
/*				  Mahmoud Sayed Mahmoud Helmy (1285)               
/*		          Mohamed Mahmoud Masoud (200)                     
/*		          Mark Ehab Tawfik (201)                           
/*		          Hazzem Mohamed Ezzeldin (1297)                   
/*		          Yousef Khaled Ahmed (558)                        
/*================================================================*/
/* =============================================================
 * 							File Guard
 * =============================================================*/
#ifndef LCD_H_
#define LCD_H_
/* =============================================================
 * 							Includes
 * =============================================================*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include "../../MCAL/DIO/atmega32_DIO.h"
#include <util/delay.h>

/* =============================================================
 * 							Port Definitions
 * =============================================================*/
#define LCD_RS_PORT_ID						PORTA_ID
#define LCD_RS_PIN_ID						PIN3_ID

#define LCD_E_PORT_ID						PORTA_ID
#define LCD_E_PIN_ID						PIN2_ID

#define LCD_DATA_PORT_ID					PORTB_ID

/* =============================================================
 * 							LCD Commands
 * =============================================================*/

#define LCD_CLEAR_COMMAND                    0x01   
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF						 0x0C
#define LCD_CURSOR_ON						 0x0E
#define LCD_SET_CURSOR_LOCATION				 0x80

/*Setting Mode to 4 Bits as the kit is hardwired to be interfaced with 4 pins only*/
#define LCD_DATA_BITS_MODE 4

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#define LCD_ROW_0 0
#define LCD_ROW_1 1
#define LCD_ROW_2 2
#define LCD_ROW_3 3

#define LCD_COLUMN_0 0
#define LCD_COLUMN_1 1
#define LCD_COLUMN_2 2
#define LCD_COLUMN_3 3
#define LCD_COLUMN_4 4
#define LCD_COLUMN_5 5
#define LCD_COLUMN_6 6
#define LCD_COLUMN_7 7
#define LCD_COLUMN_8 8
#define LCD_COLUMN_9 9
#define LCD_COLUMN_10 10
#define LCD_COLUMN_11 11
#define LCD_COLUMN_12 12
#define LCD_COLUMN_13 13
#define LCD_COLUMN_14 14
#define LCD_COLUMN_15 15
#define LCD_COLUMN_16 16
#define LCD_COLUMN_17 17
#define LCD_COLUMN_18 18
#define LCD_COLUMN_19 19

/* =============================================================
 * 							LCD Pins
 * =============================================================*/

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN0_ID
#define LCD_DB5_PIN_ID                 PIN1_ID
#define LCD_DB6_PIN_ID                 PIN2_ID
#define LCD_DB7_PIN_ID                 PIN4_ID

#endif


/* =============================================================
 * 							Function Prototypes
 * =============================================================*/

void LCD_init(void);
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const char *Str);
void LCD_clearScreen(void);
void LCD_moveCursor(uint8_t row, uint8_t col);
void LCD_displayStringRowColumn(uint8_t row, uint8_t col, const char *Str);
void LCD_integerToString(int data);

#endif /* LCD_H_ */
