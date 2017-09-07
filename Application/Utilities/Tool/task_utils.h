/********************************************************************************
  Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      task_utils.h
  Author: wujun      Version:  2.0      Date: 2016.8.1
  Description:  任务创建，删除
                  
  Others:          

  Function List:  
    1. ....
  History:        
    1. Date:
       Author:
       Modification:
    2. ...

******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __UTILITY_TASK_UTILS_H__
#define  __UTILITY_TASK_UTILS_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
#include "cmsis_os.h"	 


extern osMessageQId 						WireTestEvent;
extern osMessageQId 						WireStudyEvent;
extern osMessageQId 						WireSelfCheckEvent;
extern osMessageQId 						WireFindPointEvent;
extern osMessageQId 						UartCOM1Event;
extern osMessageQId 						UartCOM2Event;
extern osMessageQId 						UartAudioEvent;
extern osMessageQId 						Uart24GHzEvent;
extern osMessageQId 						UartInfrEvent;
	 
	 
	 
void Create_Wiretest_Task(void);
uint8_t Delete_Wiretest_Task(void);
void Create_AutoStudy_Task(void);
uint8_t Delete_AutoStudy_Task(void);
void Create_SelfCheck_Task(void);
uint8_t Delete_SelfCheck_Task(void);
void Create_FindPoint_Task(void);
uint8_t Delete_FindPoint_Task(void);

	 
#ifdef __cplusplus
}
#endif

#endif /* __UTILITY_TOOL_H__ */
