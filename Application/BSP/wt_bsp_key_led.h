/**
  ******************************************************************************
  * @file    wt_bsp_key_led.h
  * @author  zhang manxin
  * @version V1.0.0
  * @date    2014-7-18
  * @brief   This file contains all the functions prototypes for the E2PROM driver.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WT_BSP_KEY_LED_H
#define __WT_BSP_KEY_LED_H

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

#ifdef   WT_BSP_KEY_LED_GLOBALS
#define  WT_BSP_KEY_LED_EXT
#else
#define  WT_BSP_KEY_LED_EXT  extern
#endif


/* Exported constants --------------------------------------------------------*/
  
typedef struct
{
  uint8_t  key;
  uint8_t  led; 
  int32_t  wheel;
  uint8_t  rotate;   //??¡Á?¡¤???1¡ê??3?¡À??¡ê?2¡ê????¡À??
}
wt_KEY_LED_StateTypedef;
    


/* variables ---------------------------------------------------------*/

/** @defgroup WireTester_Variables
  * @{
  */
WT_BSP_KEY_LED_EXT wt_KEY_LED_StateTypedef     KeyLed_State;


// key define
#define	KeyUp				0		//Up
#define	KeyDown			3		//Down
#define	KeyOK				2		//OK
#define	KeyCancle		1		//Cancle
#define KeyWheel		5		//Wheel btn



// Led define
#define Led1				0
#define Led2				2
#define Led3				4
#define Led4				6


#define LED1_OFF()			KeyLed_State.led &= ~(3<<Led1)
#define LED1_ON_G()			KeyLed_State.led &= ~(3<<Led1); KeyLed_State.led |= 1<<Led1
#define LED1_ON_R()			KeyLed_State.led &= ~(3<<Led1); KeyLed_State.led |= 2<<Led1
#define LED1_ON_RG()		KeyLed_State.led |= 3<<Led1

#define LED2_OFF()			KeyLed_State.led &= ~(3<<Led2)
#define LED2_ON_G()			KeyLed_State.led &= ~(3<<Led2); KeyLed_State.led |= 1<<Led2
#define LED2_ON_R()			KeyLed_State.led &= ~(3<<Led2); KeyLed_State.led |= 2<<Led2
#define LED2_ON_RG()		KeyLed_State.led |= 3<<Led2

#define LED3_OFF()			KeyLed_State.led &= ~(3<<Led3)
#define LED3_ON_G()			KeyLed_State.led &= ~(3<<Led3); KeyLed_State.led |= 1<<Led3
#define LED3_ON_R()			KeyLed_State.led &= ~(3<<Led3); KeyLed_State.led |= 2<<Led3
#define LED3_ON_RG()		KeyLed_State.led |= 3<<Led3

#define LED4_OFF()			KeyLed_State.led &= ~(3<<Led4)
#define LED4_ON_G()			KeyLed_State.led &= ~(3<<Led4); KeyLed_State.led |= 1<<Led4
#define LED4_ON_R()			KeyLed_State.led &= ~(3<<Led4); KeyLed_State.led |= 2<<Led4
#define LED4_ON_RG()		KeyLed_State.led |= 3<<Led4



/* Exported functions --------------------------------------------------------*/
  
/** @defgroup Exported_Functions
  * @{
  */
void      BSP_LED_Init(void);
//void      BSP_LED_On(uint16_t Led);
//void      BSP_LED_Off(uint16_t Led);
//void      BSP_LED_Toggle(uint16_t Led);
void 			BSP_KEY_LED_Init(void);
void 			BSP_Update_KEY_LED(void);
uint8_t 	BSP_GetKEY_State(uint8_t key);
void      TIM_Encoder_Init(void);
void      Wheel_Encoder_Write(int32_t cnt);
int16_t   Wheel_Encoder_Read(void);
//void      Wheel_Encoder_clear(void);
void      Wheel_Encoder_Clear(void);
void      BSP_Update_Wheel(void);

//extern function


#ifdef __cplusplus
}
#endif
#endif /* __WT_BSP_KEY_LED_H */

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
