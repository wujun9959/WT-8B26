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
#ifndef __WT_WINDOWS_WIRETEST_H
#define __WT_WINDOWS_WIRETEST_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include <stdint.h> 
 
	 
	 
	 
	 
// OsEvent define
#define WIRETEST_START_EVENT	1
	 
	 
	 
	 
	 
	 
	 
	 

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_WINDOWS_WIRETEST_GLOBALS
#define  WT_WINDOWS_WIRETEST_EXT
#else
#define  WT_WINDOWS_WIRETEST_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
/** @defgroup Exported_Constants
  * @{
  */ 

    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester Variables
  * @{
  */
//WT_WINDOWS_WIRETEST_EXT uint8_t Number_Windos;	//当前显示窗口编号
//WT_WINDOWS_WIRETEST_EXT SystemSettingsTypeDef    settings;




/* Exported functions --------------------------------------------------------*/

void WIRETESTThread(void const * argument);



#ifdef __cplusplus
}
#endif
#endif /* __WT_WINDOWS_WIRETEST_H */

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
