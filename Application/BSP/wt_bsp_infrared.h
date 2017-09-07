/**
  ******************************************************************************
  * @file    wt_bsp_infrared.h
  * @author  wu jun
  * @version V1.0.0
  * @date    2015-3-30
  * @brief   This file contains all the functions prototypes for the Infrared driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_INFRARED_H
#define __WT_BSP_INFRARED_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_common.h"
#include "wt_bsp_define.h"

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_BSP_INFRARED_GLOBALS
#define  WT_BSP_INFRARED_EXT
#else
#define  WT_BSP_INFRARED_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
#define UART_Infr_RX_Bufer_Length			100
#define UART_Infr_RX_Timeout					100

#define UartInfr_RX_Event							1
#define UartInfr_TX_Event							2
#define UartInfr_TX_STOP_Event				3

/* variables ---------------------------------------------------------*/

WT_BSP_INFRARED_EXT uint8_t UART_Infr_Buffer_Rx[UART_Infr_RX_Bufer_Length];
WT_BSP_INFRARED_EXT uint8_t UART_Infr_Cnt_Buffer_Rx;

WT_BSP_INFRARED_EXT uint8_t UART_Infr_Switch; //0-stop 1-start
/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */
void UARTINFRThread(void const * argument);
void BSP_INFRARED_Init(void);
void UartInfr_Send_StartInfr_Cmd(void);

//extern function


#ifdef __cplusplus
}
#endif
#endif

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
