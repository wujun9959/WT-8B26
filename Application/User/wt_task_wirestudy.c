/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_task_wiretest.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-8-5
  * @brief   This file provides the wire test functions
  ******************************************************************************
  */

#define WT_WINDOWS_WIRESTUDY_GLOBALS



/* Includes ------------------------------------------------------------------*/
#include "wt_task_wirestudy.h"
#include "main.h"
#include "wt_ad_app.h"
#include "wt_task_wireselfcheck.h"

/* External variables --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
						 

/**
  * @brief  WIRETEST task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void WIRESTUDYThread(void const * argument)
{
	osEvent event;
  uint8_t res=0;
//	uint8_t str[100];
	
//	NumberStudyPort = 20;	//¼ì²â¶Ë¿ÚÊýÁ¿
	StudyFile->command = 0;	//0-no operate, 1-start, 2-cancel
	StudyFile->item_total = 0;
	StudyFile->item_index = 0;
	StudyFile->number_line = 0;
	StudyFile->number_point = 0;
	StudyFile->max_point = 0;
	StudyFile->min_point = 0;
	if(SelfCheckItem.port_board_number > 4) SelfCheckItem.port_board_number = 0;
//	if(WT_Config.StudyBoardNumber > 4) WT_Config.StudyBoardNumber = 0;
  for( ;; )
  {
		StudyFile->task_status = 0;	//0:waiting study command, 1:studying, 2:study ok, 3:study error, 4:optimize study file
//		StudyFile->item_total = 0;
//		StudyFile->item_index = 0;
//		StudyFile->number_line = 0;
//		StudyFile->number_point = 0;
		if(res==1) StudyFile->task_status = 3;
		
    event = osMessageGet( WireStudyEvent, osWaitForever );
    
		StudyFile->command = 1;//0-no operate, 1-start, 2-cancel
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case WIRESTUDY_START_EVENT:
				{
					// start test
					StudyFile->task_status = 1;	//0:waiting study command, 1:studying, 2:study ok, 3:study error, 4:optimize study file
					res = WireStudy_Process(SelfCheckItem.port_board_number * 64);	//0:ok, 1:study error, 2:user cancel; 
					if(res == 0)
					{
						StudyFile->task_status = 2;	//0:waiting study command, 1:studying, 2:study ok, 3:study error, 4:optimize study file
						LED4_OFF();
					}
					else
					{
						LED4_ON_R();
						StudyFile->task_status = 3;	//0:waiting study command, 1:studying, 2:study ok, 3:study error, 4:optimize study file
					}
					break;
				}
				
				case WIRESTUDY_OPTIMIZE_EVENT:
				{
					StudyFile->task_status = 4;	//0:waiting study command, 1:studying, 2:study ok, 3:study error, 4:optimize study file
					res = StudyFile_Optimize();
					break;
				}
				default:
					break;
      }
    }
  }
}





//void WT_Test(void)
//{
//	static uint16_t i=0;
//	
//	i++;
//	osMessagePut (WireStudyEvent, WIRESTUDY_START_EVENT, 0);
//}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
