/**
  ******************************************************************************
  * @file    ili6480.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file includes the LCD driver for ILI6480 LCD.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_ili6480.h"
#include "wt_bsp.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Component
  * @{
  */ 
  
/** @addtogroup ili6480
  * @brief     This file provides a set of functions needed to drive the 
  *            ILI6480 LCD.
  * @{
  */

/** @defgroup ILI6480_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ILI6480_Private_Defines
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup ILI6480_Private_Macros
  * @{
  */
     
/**
  * @}
  */  

/** @defgroup ILI6480_Private_Variables
  * @{
  */ 

LCD_DrvTypeDef   ili6480_drv = 
{
  ili6480_Init,
  0,//ili6480_ReadID,
  ili6480_DisplayOn,
  ili6480_DisplayOff,
  0,
  0,
  0,
  0,
  0,
  0,
  ili6480_GetLcdPixelWidth,
  ili6480_GetLcdPixelHeight,
  0,
  0,    
};

static uint8_t Is_ili6480_Initialized = 0;

/**
  * @}
  */ 
  
/** @defgroup ILI6480_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup ILI6480_Private_Functions
  * @{
  */   

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
void ili6480_Init(void)
{
  if(Is_ili6480_Initialized == 0)
  {
    Is_ili6480_Initialized = 1;    
    /* Initialise ILI6480 low level bus layer --------------------------------*/
    LCD_IO_Init();
  }
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval LCD Register Value.
  */
//uint16_t ili6480_ReadID(void)
//{
//  if(Is_ili6480_Initialized == 0)
//  {
//   ili6480_Init();
//  }

//  return ((uint16_t)ili6480_ReadData(LCD_READ_ID4, LCD_READ_ID4_SIZE));
//}


/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ili6480_DisplayOn(void)
{
  /* Display On */
	LCD_DISP_ON();
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili6480_DisplayOff(void)
{
  /* Display Off */
  LCD_DISP_OFF();
}

/**
  * @brief  Writes  to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
//void ili6480_WriteReg(uint8_t LCD_Reg)
//{
//  LCD_IO_WriteReg(LCD_Reg);
//}

/**
  * @brief  Writes data to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
//void ili6480_WriteData(uint16_t RegValue)
//{
//  LCD_IO_WriteData(RegValue);
//}

/**
  * @brief  Reads the selected LCD Register.
  * @param  RegValue Address of the register to read
  * @param  ReadSize Number of bytes to read
  * @retval LCD Register Value.
  */
//uint32_t ili6480_ReadData(uint16_t RegValue, uint8_t ReadSize)
//{
//  /* Read a max of 4 bytes */
//  return (LCD_IO_ReadData(RegValue, ReadSize));
//}

/**
  * @brief  Get LCD PIXEL WIDTH.
  * @param  None
  * @retval LCD PIXEL WIDTH.
  */
uint16_t ili6480_GetLcdPixelWidth(void)
{
  /* Return LCD PIXEL WIDTH */
  return ILI6480_LCD_PIXEL_WIDTH;
}

/**
  * @brief  Get LCD PIXEL HEIGHT.
  * @param  None
  * @retval LCD PIXEL HEIGHT.
  */
uint16_t ili6480_GetLcdPixelHeight(void)
{
  /* Return LCD PIXEL HEIGHT */
  return ILI6480_LCD_PIXEL_HEIGHT;
}

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
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
