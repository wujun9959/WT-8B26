/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_io.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-07-18
  * @brief   This file provides the E2PROM functions
  ******************************************************************************
  */

#define WT_BSP_IO_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_io.h"
#include "main.h"


/**
  * @brief  Configures IO GPIO.
  * @param  None
  * @retval None
  */
void BSP_InOut_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable the GPIO IN & OUT Clock */
    DIO_IN_GPIO_CLK_ENABLE();
    DIO_IN_LOCK_GPIO_CLK_ENABLE();
    DIO_OUT_GPIO_CLK_ENABLE();

    /* Configure the GPIO_IN_LOCK pin */
    GPIO_InitStruct.Pin = DIO_IN_LOCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(DIO_IN_LOCK_PORT, &GPIO_InitStruct);

    /* Configure the GPIO_IN pin */
    GPIO_InitStruct.Pin = DIO_IN1_PIN | DIO_IN2_PIN | DIO_IN3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(DIO_IN_PORT, &GPIO_InitStruct);
    /* Enable and set GPIO EXTI Interrupt to the lowest priority */
    //  HAL_NVIC_SetPriority((IRQn_Type)(EXTI15_10_IRQn), 15, 0x00);
    //  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI15_10_IRQn));


    /* Configure the GPIO_OUT pin */
    GPIO_InitStruct.Pin = DIO_OUT1_PIN | DIO_OUT2_PIN | DIO_OUT3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(DIO_OUT_PORT, &GPIO_InitStruct);

    // Init
    IO_State.input = 0;
    IO_State.output = 0;
}

/**
  * @brief  BSP_Update_Input
  * @param  None
  * @retval None
  */
void BSP_Update_Input(void)
{
	uint8_t temp;
	
	//temp = (~HAL_GPIO_Read(DIO_IN_PORT) & 0x3800) >> 11;
	//temp = temp | HAL_GPIO_ReadPin(INFRARED_PORT,IO_INFRARED_RX_PIN) >> 3;
    temp = (HAL_GPIO_ReadPin(DIO_IN_PORT,DIO_IN1_PIN) << 0)
         + (HAL_GPIO_ReadPin(DIO_IN_PORT,DIO_IN2_PIN) << 1)
         + (HAL_GPIO_ReadPin(DIO_IN_PORT,DIO_IN3_PIN) << 2)
         + (HAL_GPIO_ReadPin(INFRARED_PORT,IO_INFRARED_RX_PIN) << 3);
	IO_State.input = temp;
}

/**
  * @brief  BSP_Update_Output
  * @param  None
  * @retval None
  */
void BSP_Update_Output(void)
{
	if((IO_State.output & (1<<0)) == 0)	DOUT_1_OFF;
	else																DOUT_1_ON;
	if((IO_State.output & (1<<1)) == 0)	DOUT_2_OFF;
	else																DOUT_2_ON;
	if((IO_State.output & (1<<2)) == 0)	DOUT_3_OFF;
	else																DOUT_3_ON;
}

/**
  * @brief  BSP_GetInput_State
  * @param  io
  * @retval value
  */
uint8_t BSP_GetInput_State(uint8_t io)
{
	if((IO_State.input & (1<<io)) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/** @brief  IO detect IT treatment
  * @param  None
  * @retval None
  */
void BSP_IO_DetectIT(void)
{

  osMessagePut(UartCOM1Event, UartCOM1_TX_Event, 0);//????
}

/**
  * @brief  BSP_Get_LOCK_Input_State
  * @param  io
	* @retval value: 0-unlock   1-lock
  */
uint8_t BSP_GetLock_State(void)
{
    if(HAL_GPIO_ReadPin(DIO_IN_LOCK_PORT,DIO_IN_LOCK_PIN) == 1)
    {
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief  Configures IO GPIO.
  * @param  None
  * @retval None
  */
void BSP_BOARD_SW_Init( void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable the GPIO Clock */
    BOARD_CTL_GPIO_CLK_ENABLE();

    /* Configure the GPIO_OUT pin */
    GPIO_InitStruct.Pin = TEST_BOARD_A0_PIN | TEST_BOARD_A1_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(DIO_OUT_PORT, &GPIO_InitStruct);

}
