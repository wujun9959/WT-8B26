/**
  ******************************************************************************
  * @file    k_bsp.c
  * @author  MCD Application Team
  * @version V1.4.4
  * @date    06-May-2016   
  * @brief   This file provides the kernel bsp functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "wt_bsp.h"
#include "main.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup KERNEL_BSP
  * @brief Kernel BSP routines
  * @{
  */


/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes LEDs, SDRAM, touch screen, CRC and SRAM.
  * @param  None 
  * @retval None
  */
void k_BspInit(void)
{
	/* Configure KEY & LED (595) */
	BSP_KEY_LED_Init();
	
	// Configure Input & Output
	BSP_InOut_Init();
    
    /* Configure LED1 & LED2 */
    BSP_LED_Init();
    
    /* Configure wheel key Encoder */    
    TIM_Encoder_Init();
	
	/* Configure INFRARED */
    //BSP_INFRARED_Init();
	//Infra_pwm_Init();
    
    // Configure Input & Output
	BSP_BOARD_SW_Init();
	
	/* Configure UartAudio_Power */
	//BSP_UartAudio_Power_Init();
	
	/* Configure AD */
	BSP_AD_Init();
    
    /* Configure DA */
	BSP_DA_Init();
	
	/* Configure E2PROM & FLASH */
	BSP_EEPROM_Init();
	sFLASH_Init();
	
	/* Configure USART2 - 2.4GHz */
	WT_UART_24GHz_Init();
  
  /* Initialize the SDRAM */
  BSP_SDRAM_Init();
  
  /* Initialize the Touch screen */
  //BSP_TS_Init(240, 320);
  
  /* Enable CRC to Unlock GUI */
  __HAL_RCC_CRC_CLK_ENABLE();
  
  /* Enable Back up SRAM */
  __HAL_RCC_BKPSRAM_CLK_ENABLE();
  
}


/**
  * @brief  Read the coordinate of the point touched and assign their
  *         value to the variables u32_TSXCoordinate and u32_TSYCoordinate
  * @param  None
  * @retval None
  */
//void k_TouchUpdate(void)
//{
//  GUI_PID_STATE TS_State;
//  static TS_StateTypeDef prev_state;
//  __IO TS_StateTypeDef  ts;
//  uint16_t xDiff, yDiff;  
//  
//  BSP_TS_GetState((TS_StateTypeDef *)&ts);
  
//  TS_State.Pressed = ts.TouchDetected;

//  xDiff = (prev_state.X > ts.X) ? (prev_state.X - ts.X) : (ts.X - prev_state.X);
//  yDiff = (prev_state.Y > ts.Y) ? (prev_state.Y - ts.Y) : (ts.Y - prev_state.Y);
//  
//  if((prev_state.TouchDetected != ts.TouchDetected )||
//     (xDiff > 3 )||
//       (yDiff > 3))
//  {
//    prev_state.TouchDetected = ts.TouchDetected;
//    
//    if((ts.X != 0) &&  (ts.Y != 0)) 
//    {
//      prev_state.X = ts.X;
//      prev_state.Y = ts.Y;
//    }
//      
//    if(k_CalibrationIsDone())
//    {
//      TS_State.Layer = 1;
//      TS_State.x = k_CalibrationGetX (prev_state.X);
//      TS_State.y = k_CalibrationGetY (prev_state.Y);
//    }
//    else
//    {
//      TS_State.Layer = 1;
//      TS_State.x = prev_state.X;
//      TS_State.y = prev_state.Y;
//    }
//    
//    GUI_TOUCH_StoreStateEx(&TS_State);
//  }
//}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
