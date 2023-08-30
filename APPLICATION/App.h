/*
 * Team: Metaware
 * */

#ifndef APP_H_
#define APP_H_


#include <util/delay.h>
#include "../RTE/RTE.h"

#define AlarmInitialValue 0
#define MaximumAlarms 4

#define MINUTES_TENS 4
#define MINUTED_ONES 3
#define SECONDS_TENS 2
#define SECONDS_ONES 1

#define MAX_MINUTES_TENS 6

#define SET_ALARM_CHOICE '+'
#define CANCEL_ALARM_CHOICE '-'
#define ALARM_LIST_CHOICE '*'

#define CLOSE '/'
#define CONTINUE 0

typedef enum{
	ALARM_0 , ALARM_1 , ALARM_2 , ALARM_3
} alarms_id;

typedef struct{
	uint8 flag;
	int alarmDigits[4];
	int secCnt;
}Alarm_config;

void App_init(void);
void App_mainMenu(void);
void App_setAlarm(void);
void App_listAlarm(void);
void App_cancelAlarm(void);
void App_main(void);

#endif /* APP_H_ */
