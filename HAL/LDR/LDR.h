/*================================================================
                      _      ____   ____
                     | |    |  _ \ |  _ \
                     | |    | | | || |_) |
                     | |___ | |_| ||  _ <
                     |_____||____/ |_| \_\

==================================================================
      HAL     : LDR.h
      Date    : 8/26/2023
      Authors : MetaWare LLC
                Mahmoud Sayed Mahmoud Helmy (1285)
                Mohamed Mahmoud Masoud (200)
                Mark Ehab Tawfik (201)
                Hazzem Mohamed Ezzeldin (1297)
                Yousef Khaled Ahmed (558)
================================================================*/

#ifndef HAL_LDR_INTERFACE_H_
#define HAL_LDR_INTERFACE_H_

#include "../../Commons/std_types.h"
#include "../../MCAL/ADC/Adc.h"
#include "LDR_Cfg.h"
#define LDR_THRESHOLD				700UL
#define VREF_MV 					5000UL
#define TWO_POWER_RESOLUTION		1024UL
/* ==================================================================================
                           	    MACROS
==================================================================================*/

/* Possible Analog Single Ended Channels to Which LDR Can Connect */
#define LDR_CH0            0
#define LDR_CH1            1
#define LDR_CH2            2
#define LDR_CH3            3
#define LDR_CH4            4
#define LDR_CH5            5
#define LDR_CH6            6
#define LDR_CH7            7

/*================================================================================
                           	 FUNCTIONS PROTOTYPES
==================================================================================*/

/**********************************************************************************
 Description     : Initialize LDR
 Input Arguments : void
 Return          : void
**********************************************************************************/
void LDR_vidLDRInit(void);
/*********************************************************************************
 Description     : Get the digital reading equivalent to analog reading sensed
		     by LDR Sensor synchronously
 Input Arguments : Copy_u8LDRChannelNum
 Return          : u16
**********************************************************************************/
uint16 LDR_u16GetLDRReadingSync(uint8 Copy_u8LDRChannelNum);
/* ==================================================================================
 Description     : Get the digital reading equivalent to analog reading sensed
		     by LDR Sensor asynchronously
 Input Arguments : Copy_u8LDRChannelNum , Copy_pu16LDRReading,
		     void(*Copy_pvLDRFunc)(void)
Return          : void
==================================================================================*/

#endif /* HAL_LDR_INTERFACE_H_ */
