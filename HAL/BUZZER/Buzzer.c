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


#include "Buzzer.h"


void Buzzer_Init (void)
{
	DIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
}


void Buzzer_TurnOnOff (uint8 Turn)
{
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,Turn);
}
