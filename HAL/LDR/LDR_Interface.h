/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : JAN 23, 2023               	*/
/*              SWC              : LDR				*/
/*              Description	 : LDR Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_LDR_INTERFACE_H_
#define HAL_LDR_INTERFACE_H_

#include "std_types.h"
#include "Adc.h"
#include "LDR_Config.h"

#define VREF_MV 					5000UL
#define TWO_POWER_RESOLUTION		1024UL

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Possible Analog Single Ended Channels to Which LDR Can Connect */
#define LDR_CH0            0
#define LDR_CH1            1
#define LDR_CH2            2
#define LDR_CH3            3
#define LDR_CH4            4
#define LDR_CH5            5
#define LDR_CH6            6
#define LDR_CH7            7


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize LDR			        		  */
/* Input Arguments : void			    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void LDR_vidLDRInit(void);
/**********************************************************************************/
/* Description     : Get the digital reading equivalent to analog reading sensed  */
/*		     by LDR Sensor synchronously		        	  */
/* Input Arguments : Copy_u8LDRChannelNum	    			          */
/* Return          : u16	                      			          */
/**********************************************************************************/
uint16 LDR_u16GetLDRReadingSync(uint8 Copy_u8LDRChannelNum);
/**********************************************************************************/
/* Description     : Get the digital reading equivalent to analog reading sensed  */
/*		     by LDR Sensor asynchronously	        		  */
/* Input Arguments : Copy_u8LDRChannelNum , Copy_pu16LDRReading,  		  */
/* 		     void(*Copy_pvLDRFunc)(void)			    	  */
/* Return          : void	                      			          */
/**********************************************************************************/
//void LDR_u16GetLDRReadingAsync(uint8 Copy_u8LDRChannelNum , uint16* Copy_pu16LDRReading, void(*Copy_pvLDRFunc)(void));

#endif /* HAL_LDR_INTERFACE_H_ */
