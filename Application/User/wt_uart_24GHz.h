/**
  ******************************************************************************
  * @file    wt_uart_24GHz.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-7-23
  * @brief   This file contains all the functions prototypes for the uart_24GHz.
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __WT_UART_24GHZ_H
#define  __WT_UART_24GHZ_H


/*
*********************************************************************************************************
*                                              EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_UART_24GHZ_GLOBALS
#define  WT_UART_24GHZ_EXT
#else
#define  WT_UART_24GHZ_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


#define UART_24GHz_RX_Bufer_Length			        100
#define UART_24GHz_RX_Timeout						100

#define Uart24GHZ_RX_Event							1
#define Uart24GHZ_TXOK_Event						2
#define Uart24GHZ_TXNG_Event						3
#define Uart24GHZ_CONF_Event						4
#define Uart24GHZ_IMSTEST_Event					    5
#define Uart24GHZ_IMSREPAIR_Event				    6
#define Uart24GHZ_IMSTEST_REPLY_Event	            7
#define Uart24GHZ_IMSREPAIR_REPLY_Event         	8
#define Uart24GHZ_IMSPRINTOK_REPORT_Event	        9
#define Uart24GHZ_IMSPRINTNG_REPORT_Event	        10
#define Uart24GHZ_IMSID_REPORT_Event	            11
#define Uart24GHZ_IMSHEATBEAT_Event	                12
#define Uart24GHZ_BOARDID_REPORT_Event	            13
#define Uart24GHZ_WIFIRESET_Event	                14
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/
void UART24GHZThread(void const * argument);
void WT_UART_24GHz_Init(void);
//WT_UART_24GHZ_EXT uint8_t UART_24GHz_Buffer_Rx[UART_24GHz_RX_Bufer_Length] __attribute__(( at(0x10008000) ));
//WT_UART_24GHZ_EXT uint8_t UART_24GHz_Cnt_Buffer_Rx;
WT_UART_24GHZ_EXT uint16_t UART_24GHz_Cnt_Buffer_Rx;
WT_UART_24GHZ_EXT uint8_t Is_UART_24GHz_Rx_Come;

static uint8_t UART_24GHz_UpdateConfig(void);
static void UART_24GHz_Buffer_RxClear(void);
static void Uart24G_HeartBeat(void);


/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif
