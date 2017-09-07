/**
  ******************************************************************************
  * @file    wt_uart_Audio.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-12-09
  * @brief   This file contains all the functions prototypes for the uart_Audio.
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __WT_UART_Audio_H
#define  __WT_UART_Audio_H


/*
*********************************************************************************************************
*                                              EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_UART_Audio_GLOBALS
#define  WT_UART_Audio_EXT
#else
#define  WT_UART_Audio_EXT  extern
#endif




/*
*********************************************************************************************************
*                                               struct
*********************************************************************************************************
*/
typedef struct{
	
	uint8_t 	Power;			//0-Power OFF, 1-Power ON,
	uint8_t   Card;				//0-no card, 1-card Insert,
	uint8_t 	State;			//0-ready, 1-busy, 2-no TF card,
	uint16_t  TotalFile;	//0-2999:音频文件数量，>2999:error,
}
Module_AudioTypedef;  


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/
#define UART_Audio_RX_Bufer_Length			100
#define UART_Audio_RX_Timeout						100

#define UartAudio_RX_Event							1
#define UartAudioOK_TX_Event						2
#define UartAudioNG_TX_Event						3
#define UartAudio_VOLUME_Event					4
#define UartAudio_FindPoint_Event				5
#define UartAudioSTOP_TX_Event				  6
#define UartAudioOK_REPEAT_TX_Event			7


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

WT_UART_Audio_EXT uint8_t UART_Audio_Buffer_Rx[UART_Audio_RX_Bufer_Length];
WT_UART_Audio_EXT uint8_t UART_Audio_Cnt_Buffer_Rx;
//WT_UART_Audio_EXT uint8_t Is_UART_Audio_Rx_Come;
WT_UART_Audio_EXT Module_AudioTypedef ModuleAudio;


/*
*********************************************************************************************************
*                                              Functions
*********************************************************************************************************
*/

void UARTAudioThread(void const * argument);
void WT_UART_Audio_Init(void);
void 			BSP_UartAudio_Power_Init(void);
void 			BSP_UartAudio_BeepOn(uint8_t mode);
void UartAudio_SendCommand(uint8_t mode);

/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif
