/**
  ******************************************************************************
  * @file    wt_bsp_storage.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-6-28
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_STORAGE_H
#define __WT_BSP_STORAGE_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_common.h"
#include "wt_bsp_define.h"
  
typedef struct
{  
  void       (*Init)(void);//(uint16_t);
//  uint16_t   (*ReadID)(uint16_t); 
//  void       (*Reset)(uint16_t); 
//  void       (*Start)(uint16_t);
//  uint8_t    (*DetectTouch)(uint16_t);  
//  void       (*GetXY)(uint16_t, uint16_t*, uint16_t*);  
//  void       (*EnableIT)(uint16_t);
//  void       (*ClearIT)(uint16_t);  
//  uint8_t    (*GetITStatus)(uint16_t);    
//  void       (*DisableIT)(uint16_t);            
}E2PROM_DrvTypeDef;


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   WT_BSP_STORAGE_H_GLOBALS
#define  WT_BSP_STORAGE_EXT
#else
#define  WT_BSP_STORAGE_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
/** @defgroup AT24C02_Exported_Constants
  * @{
  */ 

/* chip Address */   
#define AT24C02_Addr                    0xA0
    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester_E2PROM_Variables
  * @{
  */
WT_BSP_STORAGE_EXT E2PROM_DrvTypeDef     *E2PROM_Drv;





/* Exported functions --------------------------------------------------------*/
  
/** @defgroup AT24C02_Exported_Functions
  * @{
  */

/** 
  * @brief AT24C02 Control functions
  */
void     AT24C02_Init(void);



//extern function
void                      EEPROM_IO_Init(void);
HAL_StatusTypeDef         EEPROM_IO_WriteData(uint16_t DevAddress, uint32_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_IO_ReadData(uint16_t DevAddress, uint32_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);


void                      IOE_Init(void);
void                      IOE_ITConfig (void);
void                      IOE_Delay(uint32_t Delay);
void                      IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t                   IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t                  IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);
void                      IOE_WriteMultiple (uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);


#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_STORAGE_H */

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
