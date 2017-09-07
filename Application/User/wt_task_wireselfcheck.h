/**
  ******************************************************************************
  * @file    wt_task_wireselfcheck.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-8-5
  * @brief   This file contains all the functions prototypes for wiretest
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_WINDOWS_WIRESELFCHECK_H
#define __WT_WINDOWS_WIRESELFCHECK_H

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

#ifdef   WT_WINDOWS_WIRESELFCHECK_GLOBALS
#define  WT_WINDOWS_WIRESELFCHECK_EXT
#else
#define  WT_WINDOWS_WIRESELFCHECK_EXT  extern
#endif
	 
	 
	 
// OsEvent define
#define WIRESELFCHECK_START_EVENT	1
	 


/* Exported constants --------------------------------------------------------*/
  
//×Ô¼ìÏîÄ¿×´Ì¬
typedef struct{
	uint8_t 	sd_card;					//sd¿¨×´Ì¬£¬		0:not init, 1:ok, 2:error, 3:not connect
	uint8_t 	usb_disc;					//u ÅÌ×´Ì¬£¬		0:not init, 1:ok, 2:error, 3:not connect
	uint8_t  	sdram;						//sdram×´Ì¬£¬		0:not init, 1:ok, 2:error,
	uint8_t 	i2c_e2prom;				//e2prom×´Ì¬£¬	0:not init, 1:ok, 2:error,
	uint8_t 	spi_flash[3];			//flash×´Ì¬£¬		(byte0)0:not init, 1:ok, 2:error, (byte1-2):ID0-1
	uint8_t 	port_board[4][3];	//À©Õ¹¿¨×´Ì¬(4¿é°å¿¨£¬¸÷3¸ö×Ö½Ú)
															//byte0, 	0:not init, 1:ok, 2:error, 3:not connect
															//byte1, 	FW Vision;
															//byte2,  Voltage 15V * 10
	uint8_t   port_board_number;//°å¿¨ÊýÁ¿£¬0-4
	uint8_t 	wireless;					//ÎÞÏßÄ£¿é×´Ì¬£¬0:not init, 1:ok, 2:error,3:not connect
	uint8_t 	board_state;			//Ä¸°å×´Ì¬£¬0:not init, 1:ok, 2:error,3:not connect
	uint8_t 	state;					//0:waiting, 1:testing
}
WT_SelfCheckItemTypedef;  
    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester Variables
  * @{
  */
WT_WINDOWS_WIRESELFCHECK_EXT WT_SelfCheckItemTypedef 	SelfCheckItem;


/* Exported functions --------------------------------------------------------*/

void WIRESELFCHECKThread(void const * argument);



#ifdef __cplusplus
}
#endif
#endif /* __WT_WINDOWS_WIRESELFCHECK_H */

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
