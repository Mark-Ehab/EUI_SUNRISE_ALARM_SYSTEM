/********************************************************************/
/*      SWC     : LDR.c		                                        */
/*      Date    : 8/28/2023                                         */
/*      Authors : MetaWare LLC                                      */
/*				  Mahmoud Sayed Mahmoud Helmy (1285)                */
/*		          Mohamed Mahmoud Masoud (200)                      */
/*		          Mark Ehab Tawfik (201)                            */
/*		          Hazzem Mohamed Ezzeldin (1297)                    */
/*		          Yousef Khaled Ahmed (558)                         */
/********************************************************************/


#include "LDR.h"

ADC_ConfigType Config = {ADC_PRESCALER_128,ADC_REFERENCE_AVCC};



/* =============================================================
 * 							Public Functions					
 * =============================================================*/

/* =============================================================*/
/* Description     : Initialize LDR			        		  
/* Input Arguments : void			    			          
/* Return          : void                       			    
/* =============================================================*/
void LDR_vidLDRInit(void)
{
	/* Set the pin to which LDR is connected as input */
	DIO_setupPinDirection(LDR_PORT,LDR_PIN,PIN_INPUT);

	/* Initialize ADC */
	ADC_Init(&Config);
}

/* =============================================================*/
/* Description     : Get the digital reading equivalent to analog reading sensed  */
/*		     by LDR Sensor synchronously		        	  
/* Input Arguments : Copy_u8LDRChannelNum	    			          
/* Return          : u16	                      			          
/* =============================================================*/
uint16 LDR_u16GetLDRReadingSync(uint8 Copy_u8LDRChannelNum)
{	
	/* Define Some Local Variables */
	uint16	Local_u16LDRReading_mv;       /* Holds LDR Analog Reading in milli-volts */
	uint16	Local_pu16ADCDigitalReading; /* Holds Address of ADC Digital Reading Equivalent to Analog Reading Sensed by LDR */
	/* Get ADC Digital Reading Equivalent to Analog Reading Sensed by LDR */
	ADC_readChannel_polling(Copy_u8LDRChannelNum,&Local_pu16ADCDigitalReading);
	
	/* Get Analog Reading Sensed by LDR */
	Local_u16LDRReading_mv = ((uint32)(Local_pu16ADCDigitalReading) * VREF_MV)/TWO_POWER_RESOLUTION;

	return Local_u16LDRReading_mv;
}

