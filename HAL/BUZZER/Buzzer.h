/*================================================================
			  ____   _   _  _____ _____ _____  ____   
			 | __ ) | | | ||__  /|__  /| ____||  _ \  
			 |  _ \ | | | |  / /   / / |  _|  | |_) | 
			 | |_) || |_| | / /_  / /_ | |___ |  _ <  
			 |____/  \___/ /____|/____||_____||_| \_\ 
/*================================================================*/				  
/*      HAL     : BUZZER                      
/*      Date    : 8/26/2023                                        
/*      Authors : MetaWare LLC                                     
/*				  Mahmoud Sayed Mahmoud Helmy (1285)               
/*		          Mohamed Mahmoud Masoud (200)                     
/*		          Mark Ehab Tawfik (201)                           
/*		          Hazzem Mohamed Ezzeldin (1297)                   
/*		          Yousef Khaled Ahmed (558)                        
/*================================================================*/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/atmega32_DIO.h"


#define BUZZER_PORT		PORTC_ID
#define BUZZER_PIN		PIN6_ID

#define BUZZER_OFF		0
#define BUZZER_ON	    1

void Buzzer_Init (void);
void Buzzer_TurnOnOff (uint8 Turn);

#endif /* BUZZER_H_ */
