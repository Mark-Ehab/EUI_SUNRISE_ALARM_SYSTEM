/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 10, 2022               	*/
/*              SWC              : TIMER1			*/
/*              Description	 : TIMER1 Interface             */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TIMER1_INTERFACE_H_
#define MCAL_TIMER1_INTERFACE_H_
       
#include "Timer1_Cfg.h"
#include "Timer1_Private.h"
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                       DEFINING NEW TYPES FOR INTERFACING		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*
 * Define new enum type for Timer1 Input Capture Event Trigger Edges which are :
 * 1) Generate Input Capture Event request on The Falling Edge
 * 2) Generate Input Capture Event request on The Rising Edge
 */
typedef enum
{
	TIMER1_ICU_FALLING_EDGE   = 1,
	TIMER1_ICU_RISING_EDGE    = 2
}TIMER1_ICUTriggerEdge_e;


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Timer1 based on selected configurations from      */
/* 		     config file						  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER1_vidInit(void);
/**********************************************************************************/
/* Description     : Start Timer1 by setting Timer1 prescaler selected from       */
/* 		     config file					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER1_vidStart(void);
/**********************************************************************************/
/* Description     : Stop Timer1  					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER1_vidStop(void);
/**********************************************************************************/
/* Description     : Set preload value					          */
/* Input Arguments : uint16 Copy_uint16PreloadValue                                     */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetPreloadValue(uint16 Copy_uint16PreloadValue);
/**********************************************************************************/
/* Description     : Set compare match A value				          */
/* Input Arguments : uint16 Copy_uint16CompareMatchAValue                               */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetCompareMatchAValue(uint16 Copy_uint16CompareMatchAValue);
/**********************************************************************************/
/* Description     : Set compare match B value				          */
/* Input Arguments : uint16 Copy_uint16CompareMatchBValue                               */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetCompareMatchBValue(uint16 Copy_uint16CompareMatchBValue);
/**********************************************************************************/
/* Description     : Set input capture value				          */
/* Input Arguments : uint16 Copy_uint16InputCaptureValue                                */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetInputCaptureValue(uint16 Copy_uint16InputCaptureValue);
/**********************************************************************************/
/* Description     : Read Timer/Counter1 Value				          */
/* Input Arguments : void                                                         */
/* Return          : uint16                                		          */
/**********************************************************************************/
uint16 TIMER1_uint16ReadTimerValue(void);
/**********************************************************************************/
/* Description     : Read Timer1 Input Capture Value			          */
/* Input Arguments : void                                                         */
/* Return          : void                                		          */
/**********************************************************************************/
uint16 TIMER1_uint16ReadInputCaptureValue(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Overflow Interrupt			          */
/* Input Arguments : void                                                         */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidEnableOverflowInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Overflow Interrupt			          */
/* Input Arguments : void                        			          */
/* Return          : void                               	                  */
/**********************************************************************************/
void TIMER1_vidDisableOverflowInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Compare Match A Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER1_vidEnableCompareMatchAInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Compare Match A Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER1_vidDisableCompareMatchAInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Compare Match B Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER1_vidEnableCompareMatchBInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Compare Match B Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER1_vidDisableCompareMatchBInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Capture Event Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER1_vidEnableCaptureEventInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Capture Event Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER1_vidDisableCaptureEventInterrupt(void);
/**********************************************************************************/
/* Description     : Set Timer1 Input Capture Event Trigger Edge 		  */
/* 		     (Rising or Falling) Edge				          */
/* Input Arguments : TIMER1_ICUTriggerEdge_e Copy_EdgeType_e         		  */
/* Return          : uint8                   			                  */
/**********************************************************************************/
uint8 TIMER1_uint8SetInputCaptureEventEdge(TIMER1_ICUTriggerEdge_e Copy_EdgeType_e);
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 overflow ISR is triggered		  */
/* Input Arguments : void(*Copy_pvTIMER1OverflowFunc)(void)		          */
/* Return          : uint8						                  */
/**********************************************************************************/
uint8 TIMER1_uint8SetOverflowCallback(void(*Copy_pvTIMER1OverflowFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 compare match A ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER1CompareMatchAFunc)(void)		  */
/* Return          : uint8						                  */
/**********************************************************************************/
uint8 TIMER1_uint8SetCompareMatchACallback(void(*Copy_pvTIMER1CompareMatchAFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 compare match B ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER1CompareMatchBFunc)(void)		  */
/* Return          : uint8						                  */
/**********************************************************************************/
uint8 TIMER1_uint8SetCompareMatchBCallback(void(*Copy_pvTIMER1CompareMatchBFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 capture event ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER1CaptureEventFunc)(void)		 	  */
/* Return          : uint8						                  */
/**********************************************************************************/
uint8 TIMER1_uint8SetCaptureEventCallback(void(*Copy_pvTIMER1CaptureEventFunc)(void));
/**********************************************************************************/
/* Description     : A function used to delay the processor for some time in      */
/*		     milli-second based on passed value of time in milli-second   */
/* Input Arguments : uint32 Copy_uint32DelayTime_ms				          */
/* Return          : uint8                                                	          */
/**********************************************************************************/
uint8 TIMER1_uint8SetBusyWait_ms(uint32 Copy_uint32DelayTime_ms);
/**********************************************************************************/
/* Description     : Start to generate PWM from Timer1 Output Compare Match 	  */
/*		     Channel A						          */
/* Input Arguments : uint8 Copy_uint8DutyCyclePercentage				  */
/* Return          : void						          */
/**********************************************************************************/
uint8 TIMER1_uint8StartPWMChannelA(uint8 Copy_uint8DutyCyclePercentage);
/**********************************************************************************/
/* Description     : Start to generate PWM from Timer1 Output Compare Match 	  */
/*		     Channel B						          */
/* Input Arguments : uint8 Copy_uint8DutyCyclePercentage				  */
/* Return          : void						          */
/**********************************************************************************/
uint8 TIMER1_uint8StartPWMChannelB(uint8 Copy_uint8DutyCyclePercentage);
        
#endif /* MCAL_TIMER1_INTERFACE_H_ */
