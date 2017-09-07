/**
  ******************************************************************************
  * @file    wt_bsp_print.h
  * @author  wujun
  * @version V1.0.0
  * @date    2016-8-18
  * @brief   This file contains all the functions prototypes for the Print driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_PRINT_H
#define __WT_BSP_PRINT_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_file.h"

	 
/* Exported functions --------------------------------------------------------*/
void WT_PrintFolder_Init(void);
uint8_t WT_PrintFiles_Init(char * filename,char * wire_mode);
uint8_t WT_PrintFileInfo_Write2Flash(void);
uint8_t WT_PrintFileInfo_ReadFlash(void);
uint8_t WT_ModeName_read(void);
uint8_t WT_ModeName_Write(void);
uint8_t WT_PrintModeName_Init(char * filename);
uint8_t WT_PrintSN_Write(uint16_t printsn);
uint16_t WT_PrintSN_Read(void);
uint8_t WT_ModeName_Clear(void);
uint8_t WT_PrintConfig_Init(void);

#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_FILE_H */

