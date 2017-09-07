/**
  ******************************************************************************
  * @file    wt_bsp_usart.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-7-18
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_USART_H
#define __WT_BSP_USART_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_common.h"
#include "wt_bsp_define.h"
#include "wt_bsp.h"


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_BSP_USART_GLOBALS
#define  WT_BSP_USART_EXT
#else
#define  WT_BSP_USART_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
//typedef struct
//{
//  uint8_t  input;
//	uint8_t  input_temp;
//  uint8_t  output; 
//}
//WT_BSP_IO_StateTypedef;
    

typedef enum 
{
  WT_UART_ID_COM1 	= 0,	//CN1
	WT_UART_ID_24GHZ	=	1,	//P4
	WT_UART_ID_COM2 	= 2,	//CN2
	WT_UART_ID_AUDO		= 3,	//P3
	WT_UART_ID_INFR		= 4,	//Infr
	//WT_UART_ID_AD			=	4		//AD Board
}WT_UART_TypeDef;



/* variables ---------------------------------------------------------*/

/** @defgroup WireTester_Variables
  * @{
  */
WT_BSP_USART_EXT    UART_HandleTypeDef     UartHandle_COM1;
WT_BSP_USART_EXT    UART_HandleTypeDef     UartHandle_COM2;
WT_BSP_USART_EXT    UART_HandleTypeDef     UartHandle_24GHz;
//WT_BSP_USART_EXT  UART_HandleTypeDef     UartHandle_AD;
WT_BSP_USART_EXT    UART_HandleTypeDef     UartHandle_Audio;
WT_BSP_USART_EXT    UART_HandleTypeDef     UartHandle_Infr;


/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */
void WT_UART_24GHz_Init(void);
void WT_UART_Test(void);
void WT_UART_24GHz_IRQHandler(UART_HandleTypeDef *huart);

void WT_UART_AD_IRQHandler(UART_HandleTypeDef *huart);
uint16_t Data_CRC16_MOSBUS(uint8_t* dataIn, uint16_t length);
uint16_t Data_CRC16_CCITT(uint8_t* dataIn, uint16_t length);
uint8_t Data_CheckSum(uint8_t* buffer, uint8_t length);


//extern function
extern HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status, uint32_t Timeout);



#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_USART_H */

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
