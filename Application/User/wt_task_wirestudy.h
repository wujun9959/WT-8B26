/**
  ******************************************************************************
  * @file    wt_task_wiretest.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-8-5
  * @brief   This file contains all the functions prototypes for wiretest
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_WINDOWS_WIRESTUDY_H
#define __WT_WINDOWS_WIRESTUDY_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include <stdint.h> 
 
	 
	 
	 
	 
// OsEvent define
#define WIRESTUDY_START_EVENT									1
#define WIRESTUDY_OPTIMIZE_EVENT							2
	 
	 
	 
	 
	 
	 

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_WINDOWS_WIRESTUDY_GLOBALS
#define  WT_WINDOWS_WIRESTUDY_EXT
#else
#define  WT_WINDOWS_WIRESTUDY_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
/** @defgroup Exported_Constants
  * @{
  */ 

    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester Variables
  * @{
  */
WT_WINDOWS_WIRESTUDY_EXT uint16_t 	NumberStudyPort;


/* Exported functions --------------------------------------------------------*/

void WIRESTUDYThread(void const * argument);



#ifdef __cplusplus
}
#endif
#endif /* __WT_WINDOWS_WIRESTUDY_H */

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
