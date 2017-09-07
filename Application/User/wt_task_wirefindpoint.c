/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_task_wireselfcheck.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-8-5
  * @brief   This file provides the wire test functions
  ******************************************************************************
  */

#define WT_WINDOWS_WIREFINDPOINT_GLOBALS



/* Includes ------------------------------------------------------------------*/
#include "wt_task_wirefindpoint.h"
#include "main.h"
#include "wt_ad_app.h"
#include "wt_bsp.h"
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
uint8_t WireFindPoint_Process(uint16_t PortNumber);


/**
  * @brief  wire self check task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void WIREFINDPOINTThread(void const * argument)
{
	osEvent event;
  uint8_t res;
	uint32_t i;
	
	//init the value
	FindPoint.task_status = 0;	//0-waiting, 1-finding
	FindPoint.Items_count = 0;
	FindPoint.command = 0;	//0-no operate, 1-start, 2-cancel
	for(i=0;i<sizeof(FindPoint.Items_Point);i++) FindPoint.Items_Point[i] = 0;

	
  for( ;; )
  {
    event = osMessageGet(WireFindPointEvent, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case WIREFINDPOINT_START_EVENT:
					// start self check
					FindPoint.task_status = 1;	//0:waiting, 1:testing
					res = WireFindPoint_Process(SelfCheckItem.port_board_number * 64);	//0-ok, 1-error, 2-user cancel
					if(res == 1) 	
					{
						LED4_ON_R(); //led4_on - red
					}
					else					
					{
						LED4_OFF(); //led4_off
					}
					FindPoint.task_status = 0;	//0:waiting, 1:testing
					break;
				
				default:
					break;
      }
    }
  }
}



/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
