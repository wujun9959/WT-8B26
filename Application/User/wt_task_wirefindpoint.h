/**
  ******************************************************************************
  * @file    wt_task_wirefindpoint.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-10-1
  * @brief   This file contains all the functions prototypes for wiretest
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_WINDOWS_WIREFINDPOINT_H
#define __WT_WINDOWS_WIREFINDPOINT_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include <stdint.h> 
 
	 

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_WINDOWS_WIREFINDPOINT_GLOBALS
#define  WT_WINDOWS_WIREFINDPOINT_EXT
#else
#define  WT_WINDOWS_WIREFINDPOINT_EXT  extern
#endif
	 
	 
	 
// OsEvent define
#define WIREFINDPOINT_START_EVENT	1
	 


/* Exported constants --------------------------------------------------------*/
 
//ÕÒµã×´Ì¬
typedef struct{
	uint8_t  task_status;	//0-waiting, 1-finding, 2-finding & update data	
	uint8_t  Items_count;
	uint8_t  Items_Point[256];
	uint8_t  command;	//0-no operate, 1-start, 2-cancel
}
WT_FindPointTypedef;  

   


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester Variables
  * @{
  */
WT_WINDOWS_WIREFINDPOINT_EXT WT_FindPointTypedef 	FindPoint;


/* Exported functions --------------------------------------------------------*/

void WIREFINDPOINTThread(void const * argument);



#ifdef __cplusplus
}
#endif
#endif /* __WT_WINDOWS_WIREFINDPOINT_H */

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */       
/************************ (C) COPYRIGHT CNDZ *****END OF FILE****/
