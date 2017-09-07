/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.4.5
  * @date    03-June-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#include "main.h"
#include "wt_bsp_key_led.h"
#include "wt_bsp_usart.h"
#include "wt_bsp_io.h"



extern void WT_UART_COM1_IRQHandler(UART_HandleTypeDef *huart);
//extern void WT_UART_COM2_IRQHandler(UART_HandleTypeDef *huart);
extern void WT_UART_Audio_IRQHandler(UART_HandleTypeDef *huart);
//extern void WT_UART_24GHz_IRQHandler(UART_HandleTypeDef *huart);
extern void WT_UART_Infr_IRQHandler(UART_HandleTypeDef *huart);

/** @addtogroup CORE
  * @{
  */

/** @defgroup 
  * @brief  
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern HCD_HandleTypeDef  hhcd;
extern LTDC_HandleTypeDef hltdc;

/* Private function prototypes -----------------------------------------------*/
extern void xPortSysTickHandler( void );
#if defined (STM32F429xx)
extern void LTDC_ISR_Handler(void);
#endif
extern void BSP_SD_DetectIT(void);
extern ADC_HandleTypeDef    AdcHandle;
extern I2C_HandleTypeDef 		I2cHandle;
extern SD_HandleTypeDef 		uSdHandle;

extern volatile uint32_t ulHighFrequencyTimerTicks;
extern TIM_HandleTypeDef    Tim6Handle;

uint8_t ack1_flag = 0;
uint8_t ack2_flag = 0;
uint8_t ack3_flag = 0;
uint8_t ack4_flag = 0;

//static uint8_t state_wheel = 0;	//0-init, 1- Wheel_1 Press, 2- Wheel_2 Press

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*             Cortex-M4 Processor Exceptions Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick(); 
  osSystickHandler(); 
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles USB-On-The-Go HS-FS global interrupt request.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_FS
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler(void)
#endif
{
  HAL_HCD_IRQHandler(&hhcd);
}


/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
  HAL_LTDC_IRQHandler(&hltdc);
}

/**
  * @brief  This function handles EXTI0 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    /* EXTI line interrupt detected,s1代表向上按键*/
    if(__HAL_GPIO_EXTI_GET_IT(KEY_S1_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(KEY_S1_PIN);
        
        if(HAL_GPIO_ReadPin(KEY_PORT,KEY_S1_PIN) == GPIO_PIN_RESET)//按键按下，GPIO为0
		{
            KeyLed_State.key = 1<<0;
        }
        else
        {
            KeyLed_State.key = 0;
        }
	}
    
}

/**
  * @brief  This function handles EXTI1 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
	/* EXTI line interrupt detected s2代表返回按键*/
    if(__HAL_GPIO_EXTI_GET_IT(KEY_S2_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(KEY_S2_PIN);
		if(HAL_GPIO_ReadPin(KEY_PORT,KEY_S2_PIN) == GPIO_PIN_RESET)//按键按下，GPIO为0
		{
            KeyLed_State.key = 1<<1;
        }
        else
        {
            KeyLed_State.key = 0;
        }
	}
    
}

/**
  * @brief  This function handles EXTI2 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
    /* EXTI line interrupt detected s3代表确认按键*/
    if(__HAL_GPIO_EXTI_GET_IT(KEY_S3_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(KEY_S3_PIN);
		if(HAL_GPIO_ReadPin(KEY_PORT,KEY_S3_PIN) == GPIO_PIN_RESET)//按键按下，GPIO为0
		{
            KeyLed_State.key = 1<<2;
        }
        else
        {
            KeyLed_State.key = 0;
        }
	}
    
}

/**
  * @brief  This function handles EXTI3 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
    //static uint32_t buf32 = 0;
    /* EXTI line interrupt detected s4代表向下按键*/
    if(__HAL_GPIO_EXTI_GET_IT(KEY_S4_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(KEY_S4_PIN);
		if(HAL_GPIO_ReadPin(KEY_PORT,KEY_S4_PIN) == GPIO_PIN_RESET)//按键按下，GPIO为0
		{
            KeyLed_State.key = 1<<3;
        }
        else
        {
            KeyLed_State.key = 0;
        }
	}
//    if(__HAL_GPIO_EXTI_GET_IT(KEY_S4_PIN) != RESET)
//    {
//        __HAL_GPIO_EXTI_CLEAR_IT(KEY_S4_PIN);
//        
//		if(HAL_GPIO_ReadPin(KEY_PORT,KEY_S4_PIN) != GPIO_PIN_RESET)//没有按下, 1
//		{
//            if((HAL_GetTick() - buf32) > 50 && (buf32 != 0)) //大于50ms
//            {
//                
//                KeyLed_State.key = 1<<3;
//            }
//            else 
//            {
//                KeyLed_State.key &= ~(1<<3);  
//            }                
//        }
//        else //按键按下，GPIO为0
//        {
//            buf32 = HAL_GetTick();
//           
//        }
//     
//	}
    
}

/**
  * @brief  This function handles EXTI4 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
	/* EXTI line interrupt detected, KEYWHEEL_2_PIN, GPIO_PIN_4	//PB4 */
  if(__HAL_GPIO_EXTI_GET_IT(PS_MISO_ACK1_PIN) != RESET)
  {
        __HAL_GPIO_EXTI_CLEAR_IT(PS_MISO_ACK1_PIN);
        ack1_flag = 1;
  }
}


/**
  * @brief  This function handles EXTI9_5 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
  /* EXTI line interrupt detected, PC5, USBOTG_POWER_OC_PIN, over current limit */
//  if(__HAL_GPIO_EXTI_GET_IT(USBOTG_POWER_OC_PIN) != RESET)
//  {
//    __HAL_GPIO_EXTI_CLEAR_IT(USBOTG_POWER_OC_PIN);
//		
//		// usb power current over limit	
//  }
    if(__HAL_GPIO_EXTI_GET_IT(WHEELKEY_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(WHEELKEY_PIN);
        if(HAL_GPIO_ReadPin(WHEELKEY_PORT,WHEELKEY_PIN) == GPIO_PIN_RESET)//旋钮键按下
        {
            KeyLed_State.key = 1<<5;
        }
        else
        {
            KeyLed_State.key = 0;
        }
    }
	if(__HAL_GPIO_EXTI_GET_IT(PS_MISO_ACK2_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(PS_MISO_ACK2_PIN);
        ack2_flag = 1;
	}
    if(__HAL_GPIO_EXTI_GET_IT(PS_MISO_ACK3_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(PS_MISO_ACK3_PIN);
        ack3_flag = 1;
	}
    if(__HAL_GPIO_EXTI_GET_IT(PS_MISO_ACK4_PIN) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(PS_MISO_ACK4_PIN);
        ack4_flag = 1;
	}

}

/**
  * @brief  This function handles EXTI15_10 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
  /* EXTI line interrupt detected, GPIO_PIN_13 */
  if(__HAL_GPIO_EXTI_GET_IT(SDIO_DETECT_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(SDIO_DETECT_PIN);
		
		// cndz, define
		BSP_SD_DetectIT();	
  }
//	
//	if(__HAL_GPIO_EXTI_GET_IT(DIO_IN1_PIN) != RESET)
//  {
//    __HAL_GPIO_EXTI_CLEAR_IT(DIO_IN1_PIN);
//		
//		// cndz, define
//		BSP_IO_DetectIT();
//  }
	
}

/**
  * @brief  This function handles DMA RX interrupt request.  
  * @param  None
  * @retval None    
  */
void USART1_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(UartHandle_COM1.hdmarx);
}

/**
  * @brief  This function handles DMA TX interrupt request.
  * @param  None
  * @retval None   
  */
void USART1_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(UartHandle_COM1.hdmatx);
}

/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  * @Note   None    
  */
void USART1_IRQHandler(void)	//COM1 串口打印
{
	WT_UART_COM1_IRQHandler(&UartHandle_COM1);
}

/**
  * @brief  This function handles USART2 interrupt request.
  * @param  None
  * @retval None
  * @Note   None    
  */
void USART2_IRQHandler(void)	//2.4G WireLess
{
	WT_UART_24GHz_IRQHandler(&UartHandle_24GHz);
}

/**
  * @brief  This function handles USART3 interrupt request.
  * @param  None
  * @retval None
  * @Note   None    
  */
void USART3_IRQHandler(void)	//COM2
{
    HAL_UART_IRQHandler(&UartHandle_COM2);
}

/**
  * @brief  This function handles UART4 interrupt request.
  * @param  None
  * @retval None
  * @Note   None    
  */
void UART4_IRQHandler(void)	//Audio
{
	WT_UART_Audio_IRQHandler(&UartHandle_Audio);
}

/**
  * @brief  This function handles USART6 interrupt request.
  * @param  None
  * @retval None
  * @Note   None    
  */
void USART6_IRQHandler(void)	//Infr
{
	WT_UART_Infr_IRQHandler(&UartHandle_Infr);
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&Tim6Handle);
}


/**
  * @brief  This function handles UART7 interrupt request.
  * @param  None
  * @retval None
  * @Note   None    
  */
//void UART7_IRQHandler(void)	//AD
//{
//    HAL_UART_IRQHandler(&UartHandle_AD);
//}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void ADCx_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(AdcHandle.DMA_Handle);
}

/**
  * @brief  This function handles ADC interrupt request.
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&AdcHandle);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void EEPROM_I2C_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(I2cHandle.hdmatx);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void EEPROM_I2C_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(I2cHandle.hdmarx);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
