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
#ifndef __WT_BSP_AD_H
#define __WT_BSP_AD_H

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

#ifdef   WT_BSP_AD_GLOBALS
#define  WT_BSP_AD_EXT
#else
#define  WT_BSP_AD_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
typedef struct
{
  uint16_t ChannelAB_Addr_State;
	uint16_t ChannelCD_Addr_State;
	uint8_t  Channel_Addr_Error;
	uint8_t  PortBoard_Connected;	//1-已连接，0-未连接
	uint8_t  SourceA_Addr;
	uint8_t  SourceC_Addr;
}
WT_BSP_AD_StateTypedef;



/* AD_Channel_Addr define ---------------------------------------------------------*/

//#define PortBoard_01						0
//#define PortBoard_02						1
//#define PortBoard_03						2
//#define PortBoard_04						3



/* AD_Channel_Addr define ---------------------------------------------------------*/

#define AD_ChannelAddr_NULL			0x01FF
//#define AD_PortBoardAddr_NULL		64


/* AD_Source_Addr define ---------------------------------------------------------*/

#define AD_SourceAddr_U45V			7	// 0->7, ULN2803反向
#define AD_SourceAddr_I8mA			6	// 1->6, ULN2803反向
#define AD_SourceAddr_I1mA			5	// 2->5, ULN2803反向
#define AD_SourceAddr_I100uA		4	// 3->4, ULN2803反向
#define AD_SourceAddr_W400Hz		3	// 4->3, ULN2803反向
#define AD_SourceAddr_U12V			2	// 5->2, ULN2803反向
#define AD_SourceAddr_GNDR			1	// 6->1, ULN2803反向
#define AD_SourceAddr_GND				0	// 7->0, ULN2803反向




/* IO Input & Output define ---------------------------------------------------------*/

//#define AD_TestRDC_RD()					HAL_GPIO_WritePin(AD_SOURSE_PORT, AD_SOURSE_RDC_PIN, GPIO_PIN_SET)
//#define AD_TestRDC_C()					HAL_GPIO_WritePin(AD_SOURSE_PORT, AD_SOURSE_RDC_PIN, GPIO_PIN_RESET)

#define AD_InputState						(AD_SIGNAL_PORT->IDR & 0x000F)
#define AD_InputV01							(1<<1)
#define AD_InputV10							(1<<2)
#define AD_InputCBD							(1<<3)






#define UART_AD_RX_Bufer_Length			12
#define ADC_Bufer_Length						20
#define UART_AD_RX_Timeout					10
#define AD_Voltage_MUL							1000000


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester_Variables
  * @{
  */
WT_BSP_AD_EXT WT_BSP_AD_StateTypedef     	                AD_State;
WT_BSP_AD_EXT uint8_t 										UART_AD_Buffer_Rx[UART_AD_RX_Bufer_Length];
WT_BSP_AD_EXT uint8_t 										UART_AD_Cnt_Buffer_Rx;
WT_BSP_AD_EXT uint8_t 										Is_UART_AD_Rx_Come;
WT_BSP_AD_EXT ADC_HandleTypeDef    				            AdcHandle;
WT_BSP_AD_EXT DAC_HandleTypeDef                             DacHandle;
WT_BSP_AD_EXT uint16_t 										BufADC_Value[ADC_Bufer_Length];	/* Variable used to get converted value */
WT_BSP_AD_EXT uint16_t 										AD_IsConvertFinished;	//1-finished, 0-waiting




/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */
void 			BSP_AD_Init(void);
void 			BSP_DA_Init(void);
void 			AD_Update_SourceAddr(uint8_t addrSourceA, uint8_t addrSourceC);
//uint8_t 	PortBoard_Update_ChannelAddr(uint16_t addrAB, uint16_t addrCD);
//uint8_t 	PortBoard_Read_BoardInfo(uint32_t *info);
//uint8_t 	PortBoard_Read_ChannelSetting(uint32_t *info);
uint8_t 	AD_ReadValue(uint32_t cnt, uint16_t * buf16);
uint8_t     GetADValue( uint16_t * buf16 );
uint8_t     GetResValue( uint16_t adval, uint32_t * resval );
uint64_t 	AD_GetVoltage_AutoStep(uint16_t value, uint8_t mode);
uint32_t    AD_GetRes_FromDCU4V5(uint16_t value);
uint16_t    Voltage_GetValue_FromBuffer(uint16_t* pData, uint32_t Length);
uint32_t 	AD_GetCAP_FromDCU4V5(uint16_t VoltageValue);
uint8_t     SetCmpVoltage(uint16_t cmp1,uint16_t cmp2);
//uint8_t 	AD_UART_ReadBoardInfo(uint8_t board_id, uint8_t * buf);
//void 			BSP_AD_ChangeMode(uint8_t mode);	//0-Normal Mode, 1-FindPoint Mode;
//extern function


#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_AD_H */

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
