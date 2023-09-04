/*================================================================
		  _____  _                         _  
		 |_   _|(_) _ __ ___    ___  _ __ / | 
		   | |  | || '_ ` _ \  / _ \| '__|| | 
		   | |  | || | | | | ||  __/| |   | | 
		   |_|  |_||_| |_| |_| \___||_|   |_|
                                             
                                  
/*================================================================*/				  
/*      Driver  : Timer1                          
/*      Date    : 8/26/2023                                        
/*      Authors : MetaWare LLC                                     
/*				  Mahmoud Sayed Mahmoud Helmy (1285)               
/*		          Mohamed Mahmoud Masoud (200)                     
/*		          Mark Ehab Tawfik (201)                           
/*		          Hazzem Mohamed Ezzeldin (1297)                   
/*		          Yousef Khaled Ahmed (558)                        
/*================================================================*/

#ifndef MCAL_TIMER1_PRIVATE_H_
#define MCAL_TIMER1_PRIVATE_H_

/*                                                                                   */
/*                              Includes                    		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "../../Commons/atmega32_mapping.h"
#include "../../Commons/std_types.h"
#include "../../Commons/Macros.h"
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some Bits Definitions of Timer/Counter1 Control Register A (TCCR1A) */
#define TCCR1A_WGM10						             0 /* Waveform Generation Bit 0 */
#define TCCR1A_WGM11						             1 /* Waveform Generation Bit 1 */


/* Some Bits Definitions of Timer/Counter1 Control Register B (TCCR1B) */
#define TCCR1B_WGM12						             3 /* Waveform Generation Bit 2 */
#define TCCR1B_WGM13						             4 /* Waveform Generation Bit 3 */
#define TCCR1B_ICES1							     6 /* Input Capture Edge Select */


/* Some Bits Definitions of Timer/Counter Interrupt Mask Register (TIMSK) */
#define TIMSK_TOIE1						             2 /* Timer/Counter1 Overflow Interrupt Enable */
#define TIMSK_OCIE1B						             3 /* Timer/Counter1 Output Compare B Match Interrupt Enable */
#define TIMSK_OCIE1A						             4 /* Timer/Counter1 Output Compare A Match Interrupt Enable */
#define TIMSK_TICIE1						             5 /* Timer/Counter1 Input Capture Interrupt Enable */


/* Some Bits Definitions of Timer/Counter Interrupt Flag Register (TIFR) */
#define TIFR_TOV1 						             2 /* Timer/Counter1 Overflow Flag */
#define TIFR_OCF1B						             3 /* Timer/Counter1 Output Compare B Match Flag */
#define TIFR_OCF1A						             4 /* Timer/Counter1 Output Compare A Match Flag*/
#define TIFR_ICF1						             5 /* Timer/Counter1 Input Capture Flag */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define Timer1 Overflow Ticks */
#define TIMER1_OVERFLOW_TICKS		                             	     65535 /* Maximum Number of Timer Ticks to Reach Overflow and Calculated Based on Timer Resolution (8 bits in case of Timer0) */


/* Mask of Timer1 Output Compare Match Pin Channel A Mode Bits */
#define TIMER1_OUTPUT_COMPARE_PIN_CHA_MODE_MASK                              0b00111111


/* Define Timer1 Output Compare Match Pin Channel A Modes (Non PWM)  */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHA_DISCONNECTED                   0b00000000 /* Timer1 Output Compare Match Pin Channel A is Disconnect */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHA_TOGGLE                         0b01000000 /* Timer1 Output Compare Match Pin Channel A is Toggled */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHA_CLEAR                          0b10000000 /* Timer1 Output Compare Match Pin Channel A is Cleared */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHA_SET                            0b11000000 /* Timer1 Output Compare Match Pin Channel A is Set */


/* Define Timer1 Output Compare Match Pin Channel A Modes (Fast PWM) */
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHA_DISCONNECTED		     0b00000000 /* Timer1 Output Compare Match Pin Channel A is Disconnect */
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHA_NON_INVERTED_MODE             0b10000000 /* Clear OC1A on compare match, set OC1A at TOP */
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHA_INVERTED_MODE                 0b11000000 /* Set OC1A on compare match, clear OC1A at TOP */


/* Define Timer1 Output Compare Match Pin Channel A Modes (Phase-Correct PWM) */
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHA_DISCONNECTED         0b00000000 /* Timer1 Output Compare Match Pin Channel A is Disconnect */
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHA_NON_INVERTED_MODE    0b10000000 /* Clear OC1A on compare match when up-counting. Set OC1A on compare match when downcounting */
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHA_INVERTED_MODE        0b11000000 /* Set OC1A on compare match when up-counting. Clear OC1A on compare match when downcounting */


/* Mask of Timer1 Output Compare Match Pin Channel B Mode Bits */
#define TIMER1_OUTPUT_COMPARE_PIN_CHB_MODE_MASK                              0b11001111


/* Define Timer1 Output Compare Match Pin Channel B Modes (Non PWM)  */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHB_DISCONNECTED                   0b00000000 /* Timer1 Output Compare Match Pin Channel B is Disconnect */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHB_TOGGLE                         0b00010000 /* Timer1 Output Compare Match Pin Channel B is Toggled */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHB_CLEAR                          0b00100000 /* Timer1 Output Compare Match Pin Channel B is Cleared */
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHB_SET                            0b00110000 /* Timer1 Output Compare Match Pin Channel B is Set */


/* Define Timer1 Output Compare Match Pin Channel B Modes (Fast PWM) */
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHB_DISCONNECTED		     0b00000000 /* Timer1 Output Compare Match Pin Channel B is Disconnect */
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHB_NON_INVERTED_MODE             0b00100000 /* Clear OC1B on compare match, set OC1B at TOP */
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHB_INVERTED_MODE                 0b00110000 /* Set OC1B on compare match, clear OC1B at TOP */


/* Define Timer1 Output Compare Match Pin Channel B Modes (Phase-Correct PWM) */
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHB_DISCONNECTED         0b00000000 /* Timer1 Output Compare Match Pin Channel B is Disconnect */
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHB_NON_INVERTED_MODE    0b00100000 /* Clear OC1B on compare match when up-counting. Set OC1B on compare match when downcounting */
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHB_INVERTED_MODE        0b00110000 /* Set OC1B on compare match when up-counting. Clear OC1B on compare match when downcounting */


/* Mask of Timer1 Clock Selection Bits */
#define TIMER1_CLK_MASK						             0b11111000


/* Timer1 Prescaler Selections */
#define TIMER1_CLK_DIV_BY_NO_PRESCALER				             0b00000001 /* clkI/O/(No prescaling) */
#define TIMER1_CLK_DIV_BY_8					             0b00000010 /* clkI/O/8 (From prescaler) */
#define TIMER1_CLK_DIV_BY_64					             0b00000011 /* clkI/O/64 (From prescaler) */
#define TIMER1_CLK_DIV_BY_256					             0b00000100 /* clkI/O/256 (From prescaler) */
#define TIMER1_CLK_DIV_BY_1024					             0b00000101 /* clkI/O/1024 (From prescaler) */
#define TIMER1_EXT_CLK_FALLING_EDGE				             0b00000110 /* External clock source on T0 pin. Clock on falling edge */
#define TIMER1_EXT_CLK_RISING_EDGE			       	             0b00000111 /* External clock source on T0 pin. Clock on rising edge */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Timer1 Operating Modes Options */
#define OVERFLOW_MODE			  			             1
#define PHASE_CORRECT_PWM_EIGHT_BIT_MODE      			             2
#define PHASE_CORRECT_PWM_NINE_BIT_MODE				             3
#define PHASE_CORRECT_PWM_TEN_BIT_MODE        			             4
#define CTC_OCR1A_MODE					                     5
#define FAST_PWM_EIGHT_BIT_MODE                                              6
#define FAST_PWM_NINE_BIT_MODE                                               7
#define FAST_PWM_TEN_BIT_MODE                                                8
#define PHASE_FREQUENCY_CORRECT_PWM_ICR1_MODE                                9
#define PHASE_FREQUENCY_CORRECT_PWM_OCR1A_MODE                               10
#define PHASE_CORRECT_PWM_ICR1_MODE		                             11
#define PHASE_CORRECT_PWM_OCR1A_MODE		                             12
#define CTC_ICR1_MODE				                             13
#define FAST_PWM_ICR1_MODE		                                     14
#define FAST_PWM_OCR1A_MODE		                                     15


/* Timer1 Possible Output Compare Match Channels */
#define CHANNELA	                                                     1
#define CHANNELB	                                                     2
#define BOTH_CHANNELS							     3


/* Output Compare Match Pin Modes Options for Both Channels A&B (Non PWM) */
#define DISCONNECTED					                     0
#define TOGGLE	                                                             1
#define CLEAR	                                                             2
#define SET	                                                             3


/* Output Compare Match Pin Modes Options for Both Channels A&B (Phase Correct & Fast PWM) */
#define NON_INVERTED_MODE                                                    1
#define INVERTED_MODE                                                        2


/* Timer1 Input Capture Event Trigger Edge Possible Values */
#define FALLING_EDGE							     1
#define RISING_EDGE 							     2


/* Enable/Disable signals for Overflow, Compare Match A, Compare Match B and Capture Event Interrupts of Timer1 */
#define ENABLE                                                               1
#define DISABLE                                                              2


/* Timer1 Pre-scaler Options */
#define CLK_DIV_BY_NO_PRESCALER	                                             1
#define CLK_DIV_BY_8	                                                     8
#define CLK_DIV_BY_64		                                             64
#define CLK_DIV_BY_256      	                                             256
#define CLK_DIV_BY_1024                                                      1024
#define EXT_CLK_FALLING_EDGE	                                             2
#define EXT_CLK_RISING_EDGE				                     3

#endif /* MCAL_TIMER1_PRIVATE_H_ */
