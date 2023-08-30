/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 10, 2022               	*/
/*              SWC              : TIMER1			*/
/*              Description	 : TIMER1 Config                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TIMER1_CONFIG_H_
#define MCAL_TIMER1_CONFIG_H_

/*********************************************************/
/* Set AVR ATmega32 Clock Frequency			 */
/*********************************************************/
#define TIMER1_MCU_CLK_FREQ 8000000UL /* Default: 8000000UL */
/*********************************************************/
/* Set Timer1 Operating Mode :-				 */
/* 		         	                         */
/* Options : - OVERFLOW_MODE			         */
/* 	     - PHASE_CORRECT_PWM_EIGHT_BIT_MODE          */
/* 	     - PHASE_CORRECT_PWM_NINE_BIT_MODE           */
/* 	     - PHASE_CORRECT_PWM_TEN_BIT_MODE            */
/* 	     - CTC_OCR1A_MODE				 */
/* 	     - FAST_PWM_EIGHT_BIT_MODE                   */
/* 	     - FAST_PWM_NINE_BIT_MODE                    */
/* 	     - FAST_PWM_TEN_BIT_MODE                     */
/*	     - PHASE_FREQUENCY_CORRECT_PWM_ICR1_MODE	 */
/*	     - PHASE_FREQUENCY_CORRECT_PWM_OCR1A_MODE	 */
/*	     - PHASE_CORRECT_PWM_ICR1_MODE		 */
/*	     - PHASE_CORRECT_PWM_OCR1A_MODE		 */
/* 	     - CTC_ICR1_MODE				 */
/*	     - FAST_PWM_ICR1_MODE		         */
/*	     - FAST_PWM_OCR1A_MODE		         */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_MODE OVERFLOW_MODE /* Default: OVERFLOW_MODE */
/*********************************************************/
/* Select Timer1 Output Compare Match Channel:-		 */
/* 		         	                         */
/* Options : - CHANNELA	                 		 */
/* 	     - CHANNELB	                 		 */
/* 	     - BOTH_CHANNELS	                 	 */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_OUTPUT_COMPARE_MATCH_CHANNEL CHANNELA /* Default : CHANNELA */
/*********************************************************/
/* Set Mode of Timer1 Output Compare Match Pin of 	 */
/* Channel A (Non-PWM):					 */
/* 		         	                         */
/* Options : - DISCONNECTED				 */
/* 	     - TOGGLE					 */
/* 	     - CLEAR					 */
/*	     - SET					 */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHA_MODE DISCONNECTED /* Default : DISCONNECTED */
/*********************************************************/
/* Set Mode of Timer1 Output Compare Match Pin of 	 */
/* Channel A (Fast PWM):				 */
/* 		         	                         */
/* Options : - DISCONNECTED				 */
/* 	     - NON_INVERTED_MODE                         */
/* 	     - INVERTED_MODE                             */
/*							 */
/* Note    : Only Selected When Fast PWM Mode is Enabled */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHA_MODE DISCONNECTED /* Default : DISCONNECTED */
/*********************************************************/
/* Set Mode of Timer1 Output Compare Match Pin of 	 */
/* Channel A (Phase-Correct PWM):			 */
/* 		         	                         */
/* Options : - DISCONNECTED				 */
/* 	     - NON_INVERTED_MODE                         */
/* 	     - INVERTED_MODE                             */
/*							 */
/* Note    : Only Selected When Phase Correct PWM Mode   */
/*	     is Enabled				         */
/*							 */
/*********************************************************/
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHA_MODE DISCONNECTED /* Default : DISCONNECTED */
/*********************************************************/
/* Set Mode of Timer1 Output Compare Match Pin of 	 */
/* Channel B (Non-PWM):					 */
/* 		         	                         */
/* Options : - DISCONNECTED				 */
/* 	     - TOGGLE					 */
/* 	     - CLEAR					 */
/*	     - SET					 */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_NON_PWM_OUTPUT_COMPARE_PIN_CHB_MODE DISCONNECTED /* Default : DISCONNECTED */
/*********************************************************/
/* Set Mode of Timer1 Output Compare Match Pin of 	 */
/* Channel B (Fast PWM):				 */
/* 		         	                         */
/* Options : - DISCONNECTED				 */
/* 	     - NON_INVERTED_MODE                         */
/* 	     - INVERTED_MODE                             */
/*							 */
/* Note    : Only Selected When Fast PWM Mode is Enabled */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_FAST_PWM_OUTPUT_COMPARE_PIN_CHB_MODE DISCONNECTED /* Default : DISCONNECTED */
/*********************************************************/
/* Set Mode of Timer1 Output Compare Match Pin of 	 */
/* Channel B (Phase-Correct PWM):			 */
/* 		         	                         */
/* Options : - DISCONNECTED				 */
/* 	     - NON_INVERTED_MODE                         */
/* 	     - INVERTED_MODE                             */
/*							 */
/* Note    : Only Selected When Phase Correct PWM Mode   */
/*	     is Enabled				         */
/*							 */
/*********************************************************/
#define TIMER1_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_CHB_MODE DISCONNECTED /* Default : DISCONNECTED */
/*********************************************************/
/* Enable/Disable Timer1 ICU Mode:- 			 */
/*  							 */
/* Options : - ENABLE             	                 */
/* 	     - DISABLE                	                 */
/*							 */
/*********************************************************/
#define TIMER1_ICU_ENABLE ENABLE /* Default : DISABLE */
/*********************************************************/
/* Select Timer1 Input Capture Event Trigger Edge Type:- */
/*  							 */
/* Options : - FALLING_EDGE                              */
/* 	     - RISING_EDGE                               */
/* 	                          		 	 */
/* Note	   : Only selected when Timer ICU mode is 	 */
/* 	     enabled				         */
/*							 */
/*********************************************************/
#define TIMER1_ICU_TRIGGER_EDGE FALLING_EDGE /* Default: FALLING_EDGE */
/*********************************************************/
/* Enable/Disable Timer/Counter1 Overflow Interrupt :- 	 */
/*  							 */
/* Options : - ENABLE                                    */
/* 	     - DISABLE                                   */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_OVERFLOW_INTERRUPT_ENABLE DISABLE /* Default : DISABLE */
/*********************************************************/
/* Enable/Disable Timer/Counter1 Compare Match A	 */
/* Interrupt :- 	 				 */
/*  							 */
/* Options : - ENABLE                                    */
/* 	     - DISABLE                                   */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_COMPARE_MATCH_A_INTERRUPT_ENABLE DISABLE /* Default : DISABLE */
/*********************************************************/
/* Enable/Disable Timer/Counter1 Compare Match B	 */
/* Interrupt :- 	 				 */
/*  							 */
/* Options : - ENABLE                                    */
/* 	     - DISABLE                                   */
/* 	                          		 	 */
/*********************************************************/
#define TIMER1_COMPARE_MATCH_B_INTERRUPT_ENABLE DISABLE /* Default : DISABLE */
/*********************************************************/
/* Enable/Disable Timer/Counter1 Capture Event		 */
/* Interrupt :- 	 				 */
/*  							 */
/* Options : - ENABLE                                    */
/* 	     - DISABLE                                   */
/*							 */
/* Note	   : Only selected when Timer ICU mode is 	 */
/* 	     enabled				         */
/*							 */
/*********************************************************/
#define TIMER1_CAPTURE_EVENT_INTERRUPT_ENABLE DISABLE /* Default : DISABLE */
/*********************************************************/
/* Set Timer1 Pre-scaler :-				 */
/* 		         	                         */
/* Options : - CLK_DIV_BY_NO_PRESCALER	   	         */
/* 	     - CLK_DIV_BY_8	        		 */
/* 	     - CLK_DIV_BY_64		 		 */
/* 	     - CLK_DIV_BY_256      		 	 */
/* 	     - CLK_DIV_BY_1024                   	 */
/*	     - EXT_CLK_FALLING_EDGE			 */
/*	     - EXT_CLK_RISING_EDGE			 */
/*							 */
/* Note    : Last two options are selected only if used	 */
/*	     Timer1 as counter				 */
/*							 */
/*********************************************************/
#define TIMER1_PRESCALER CLK_DIV_BY_8 /* Default: CLK_DIV_BY_8 */

#endif /* MCAL_TIMER1_CONFIG_H_ */
