/*================================================================
					  _      ____   ____                      
					 | |    |  _ \ |  _ \                     
					 | |    | | | || |_) |                    
					 | |___ | |_| ||  _ <                     
					 |_____||____/ |_| \_\                    
                                          
/*================================================================*/				  
/*      HAL     : LDR                  
/*      Date    : 8/26/2023                                        
/*      Authors : MetaWare LLC                                     
/*				  Mahmoud Sayed Mahmoud Helmy (1285)               
/*		          Mohamed Mahmoud Masoud (200)                     
/*		          Mark Ehab Tawfik (201)                           
/*		          Hazzem Mohamed Ezzeldin (1297)                   
/*		          Yousef Khaled Ahmed (558)                        
/*================================================================*/

#ifndef HAL_LDR_CONFIG_H_
#define HAL_LDR_CONFIG_H_

#include "../../MCAL/DIO/atmega32_DIO.h"

/* ==================================================================================*/
/* Select the port for LDR to operate on:- 				   				
/* Options :  - PORT_A                         				
/* 	          - PORT_B               	       				
/* 	          - PORT_C               	       				
/* 	          - PORT_D               	       						        
/* Note    : In case of AVR ATmega32 the only valid port to receive     
/* 	     analog signal as input from sensors is PORT_A (Mandatory)  
/* ==================================================================================*/

#define LDR_PORT PORTA_ID /* Default: PORT_A */

/************************************************************************/
/* Select the pin for LDR to operate on:- 				*/
/*                                                                      */
/* Options :  - PIN_0                                                   */
/* 	      - PIN_1                                                   */
/* 	      - PIN_2                                                   */
/* 	      - PIN_3                                                   */
/* 	      - PIN_4                                                   */
/* 	      - PIN_5                                                   */
/* 	      - PIN_6                                                   */
/* 	      - PIN_7                                                   */
/*									*/
/************************************************************************/
#define LDR_PIN  PIN0_ID /* Default: PIN_0 */


#endif /* HAL_LDR_CONFIG_H_ */
