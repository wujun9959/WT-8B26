/**
  ******************************************************************************
  * @file    wt_bsp_ad.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-7-18
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_COMMON_H
#define __WT_BSP_COMMON_H

#ifdef __cplusplus
 extern "C" {
#endif
   
   
/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stddef.h>
#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

   
   
/** @defgroup LOW_LEVEL_Exported_Functions
  * @{
  */
void CLK_Delay (uint32_t Delay);




/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __WT_BSP_COMMON_H */
/**
  * @}
  */       
/************************ (C) COPYRIGHT CNDZ *****END OF FILE****/
