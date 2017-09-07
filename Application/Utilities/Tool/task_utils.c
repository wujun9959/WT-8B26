/********************************************************************************
  Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      task_utils.c
  Author: wujun      Version:  2.0      Date: 2016.7.28
  Description:    任务创建，删除函数
                  
  Others:          

  Function List:  
    1. ....
  History:        
    1. Date:
       Author:
       Modification:
    2. ...
    
******************************************************************************/

#include  "task_utils.h"
#include  "k_bsp.h"
#include "wt_task_wiretest.h"
#include "wt_task_wirestudy.h"
#include "wt_task_wirefindpoint.h"

osMessageQId 						WireTestEvent;
osMessageQId 						WireStudyEvent;
osMessageQId 						WireSelfCheckEvent;
osMessageQId 						WireFindPointEvent;
osMessageQId 						UartCOM1Event;
osMessageQId 						UartCOM2Event;
osMessageQId 						UartAudioEvent;
osMessageQId 						Uart24GHzEvent;
osMessageQId 						UartInfrEvent;

osThreadId              WireTestThread;//wire test taskid
osThreadId              WireStudyThread;//wire study taskid
osThreadId              UartCom1Thread;//Uart Com1 taskid
osThreadId              UartInfrThread;//Uart Infr taskid
osThreadId              Uart24GThread;//Uart 2.4G taskid
osThreadId              UartCom2Thread;//Uart Com2 taskid
//osThreadId              SelfCheckThread;//Self Check taskid
osThreadId              FindPointThread;//wire study taskid


/**
  * @brief  create_wiretest_task.
  * @param  
  * @retval None
  */
void Create_Wiretest_Task(void)
{
    TestFolder  = mymalloc(SDRAM, sizeof(WT_TestFolderTypedef));
    TestFile    = mymalloc(SDRAM, sizeof(WT_TestFileTypedef));
    
    /* Create WireTest task */
    osThreadDef(WireTest_Thread, WIRETESTThread, osPriorityNormal, 0, 5 * configMINIMAL_STACK_SIZE);	//15
    WireTestThread = osThreadCreate (osThread(WireTest_Thread), NULL); 

//    /* Create Uart_COM1 task COM1-串口打印 */
//    osThreadDef(UART_COM1_Thread, UARTCOM1Thread, osPriorityAboveNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//15
//    UartCom1Thread = osThreadCreate (osThread(UART_COM1_Thread), NULL); 

//    /* Create Uart_INFR task --红外发射*/
//    osThreadDef(UART_INFR_Thread, UARTINFRThread, osPriorityAboveNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//15
//    UartInfrThread = osThreadCreate (osThread(UART_INFR_Thread), NULL);

//    /* Create Uart_24GHZ task --WiFi通信*/
//    osThreadDef(UART_24GHZ_Thread, UART24GHZThread, osPriorityAboveNormal, 0, 6 * configMINIMAL_STACK_SIZE);	//15
//    Uart24GThread = osThreadCreate (osThread(UART_24GHZ_Thread), NULL); 

//    /* Create Uart_COM2 task --串口扫码枪*/
//    osThreadDef(UART_COM2_Thread, UARTCOM2Thread, osPriorityAboveNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//15
//    UartCom2Thread = osThreadCreate (osThread(UART_COM2_Thread), NULL); 
}

/**
  * @brief  delete_wiretest_task.
  * @param  
  * @retval 0--ok  1--error
  */
uint8_t Delete_Wiretest_Task(void)
{
	osStatus task_stat;
    myfree(SDRAM,TestFolder);
    myfree(SDRAM,TestFile);
	/* Delete WireTest task */
    task_stat = osThreadTerminate(WireTestThread);
//	task_stat = osThreadTerminate(UartCom1Thread);
//	task_stat = osThreadTerminate(UartInfrThread);
//	task_stat = osThreadTerminate(Uart24GThread);
//	task_stat = osThreadTerminate(UartCom2Thread);

	if(osOK == task_stat) {return 0;}
	else return 1;
}

/**
  * @brief  create_autostudy_task.
  * @param  
  * @retval None
  */
void Create_AutoStudy_Task(void)
{
	/* Create Auto Study task */
  osThreadDef(WireStudy_Thread, WIRESTUDYThread, osPriorityNormal, 0, 5 * configMINIMAL_STACK_SIZE);	//15
  WireStudyThread = osThreadCreate (osThread(WireStudy_Thread), NULL);
}

/**
  * @brief  delete_wiretest_task.
  * @param  
  * @retval 0--ok  1--error
  */
uint8_t Delete_AutoStudy_Task(void)
{
    osStatus task_stat;
    /* Delete WireTest task */
    task_stat = osThreadTerminate(WireStudyThread);
    if(osOK == task_stat) {return 0;}
    else return 1;
}

/**
  * @brief  创建自检任务.
  * @param  
  * @retval None
  */
void Create_SelfCheck_Task(void)
{
///* Create Self Check task */
//  osThreadDef(WireSelfCheck_Thread, WIRESELFCHECKThread, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//15
//  SelfCheckThread = osThreadCreate (osThread(WireSelfCheck_Thread), NULL); 
///* Create Auto Study task */
//  osThreadDef(WireStudy_Thread, WIRESTUDYThread, osPriorityNormal, 0, 5 * configMINIMAL_STACK_SIZE);	//15
//  WireStudyThread = osThreadCreate (osThread(WireStudy_Thread), NULL);
}

/**
  * @brief  delete_wiretest_task.
  * @param  
  * @retval 0--ok  1--error
  */
uint8_t Delete_SelfCheck_Task(void)
{
//	osStatus task_stat;
//	/* Delete WireTest task */
//  task_stat = osThreadTerminate(SelfCheckThread);
//	task_stat = osThreadTerminate(WireStudyThread);
//	if(osOK == task_stat) {return 0;}
//	else return 1;
    return 0; //just for warning
}

/**
  * @brief  创建找点任务.
  * @param  
  * @retval None
  */
void Create_FindPoint_Task(void)
{
	/* Create Find Point Check task */
  osThreadDef(WireFindPoint_Thread, WIREFINDPOINTThread, osPriorityNormal, 0, 2 * configMINIMAL_STACK_SIZE);	//15
  FindPointThread = osThreadCreate (osThread(WireFindPoint_Thread), NULL);
}

/**
  * @brief  delete_wiretest_task.
  * @param  
  * @retval 0--ok  1--error
  */
uint8_t Delete_FindPoint_Task(void)
{
    osStatus task_stat;
    /* Delete WireTest task */
    task_stat = osThreadTerminate(FindPointThread);
    if(osOK == task_stat) {return 0;}
    else return 1;
}
