/**
  ******************************************************************************
  * @file    wt_windows_menu.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-6-30
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_MENU_H
#define __WT_MENU_H

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

#ifdef   WT_MENU_GLOBALS
#define  WT_MENU_EXT
#else
#define  WT_MENU_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
/** @defgroup Exported_Constants
  * @{
  */ 

    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester Variables
  * @{
  */
//WT_MENU_EXT E2PROM_DrvTypeDef     *E2PROM_Drv;





/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */

/** 
  * @brief AT24C02 Control functions
  */
	
void WT_Windows_Menu(uint32_t *ID_Select);




#ifdef __cplusplus
}
#endif
#endif /* __WT_MENU_H */

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
