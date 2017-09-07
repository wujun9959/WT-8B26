/**
  ******************************************************************************
  * @file    wt_bsp_io.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-7-18
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_IO_H
#define __WT_BSP_IO_H

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

#ifdef   WT_BSP_IO_GLOBALS
#define  WT_BSP_IO_EXT
#else
#define  WT_BSP_IO_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
typedef struct
{
  uint8_t  input;
//	uint8_t  input_temp;
  uint8_t  output; 
}
WT_BSP_IO_StateTypedef;
    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester_Variables
  * @{
  */
WT_BSP_IO_EXT WT_BSP_IO_StateTypedef     IO_State;



/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */
void 			BSP_InOut_Init(void);
void 			BSP_Update_Input(void);
void			BSP_Update_Output(void);
void      BSP_IO_DetectIT(void);
void       BSP_BOARD_SW_Init(void);
uint8_t 	BSP_GetInput_State(uint8_t io);
uint8_t   BSP_GetLock_State(void);



//extern function


#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_IO_H */

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
