/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : JAN 23, 2023               	*/
/*              SWC              : LDR				*/
/*              Description	 : LDR Config                   */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_LDR_CONFIG_H_
#define HAL_LDR_CONFIG_H_

#include "../../MCAL/DIO/atmega32_DIO.h"

/************************************************************************/
/* Select the port for LDR to operate on:- 				*/
/*					       				*/
/* Options :  - PORT_A                         				*/
/* 	      - PORT_B               	       				*/
/* 	      - PORT_C               	       				*/
/* 	      - PORT_D               	       				*/
/*								        */
/* Note    : In case of AVR ATmega32 the only valid port to receive     */
/* 	     analog signal as input from sensors is PORT_A (Mandatory)  */
/* 					       				*/
/************************************************************************/
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
