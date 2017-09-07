/**
  ******************************************************************************
  * @file    wt_task_gui.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-7-2
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_WINDOWS_GUI_H
#define __WT_WINDOWS_GUI_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include <stdint.h> 
#include "wt_fonts.h"
#include "WM.h"

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_WINDOWS_GUI_GLOBALS
#define  WT_WINDOWS_GUI_EXT
#else
#define  WT_WINDOWS_GUI_EXT  extern
#endif



//----------------------------------------------
// wire harness tester add,20150211
#define MY_MESSAGE_CLICK	     WM_USER+0
#define MY_MESSAGE_OK	         WM_USER+1
#define MY_MESSAGE_CANCEL	     WM_USER+2
#define MY_MESSAGE_WHEEL	     WM_USER+3
#define MY_MESSAGE_UP	         WM_USER+4
#define MY_MESSAGE_DOWN	         WM_USER+5
#define MY_MESSAGE_BUTTONOK	     WM_USER+6
#define MY_MESSAGE_BUTTONCANCEL	 WM_USER+7
#define MY_MESSAGE_BUTTONDELETE	 WM_USER+8
#define MY_MESSAGE_LOCK	         WM_USER+9
#define MY_MESSAGE_WHEELNEXT	 WM_USER+10
#define MY_MESSAGE_WHEELFORWD	 WM_USER+11
#define MY_MESSAGE_UNLOCK	     WM_USER+100
//----------------------------------------------



/** @defgroup WireTester Variables
  * @{
  */
WT_WINDOWS_GUI_EXT uint8_t Number_Windos;	//当前显示窗口编号
//WT_WINDOWS_GUI_EXT SystemSettingsTypeDef    settings;




/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */

/** 
  * @brief functions
  */
	
void GUIThread(void const * argument);
void wt_SetText_Title(const char * pTitle);
void wt_SetText_Menu(const char * pMenu);
void wt_SetText_Status(const char * pStatus);


#ifdef __cplusplus
}
#endif
#endif /* __WT_WINDOWS_GUI_H */

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
