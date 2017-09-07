/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_key_led.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-07-18
  * @brief   This file provides the E2PROM functions
  ******************************************************************************
  */

#define WT_BSP_KEY_LED_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_key_led.h"
#include "cmsis_os.h"
#include "wt_bsp.h"
/* Timer handler declaration */
TIM_HandleTypeDef    Encoder_Handle;

/* Timer Output Compare Configuration Structure declaration */
TIM_OC_InitTypeDef sConfig;

/* Timer Encoder Configuration Structure declaration */
TIM_Encoder_InitTypeDef sEncoderConfig;

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable the GPIO_LED Clock */
  LED_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = LED_RUN_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	LED_RUN_OFF;
}

/**
  * @brief TIM MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIM1 Peripheral clock enable */
   __HAL_RCC_TIM3_CLK_ENABLE();
    
  /* Enable GPIO Channels Clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  /*##-2- Configure I/Os #####################################################*/  
  /* Common configuration for all channels */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  
  /* Channel 1 configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  /* Channel 2 configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief  设置编码开关
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void TIM_Encoder_Init(void)
{
 /* -1- Initialize TIM3 to handle the encoder sensor */
  /* Initialize TIM1 peripheral as follow:
       + Period = 65535
       + Prescaler = 0
       + ClockDivision = 0
       + Counter direction = Up
  */
  Encoder_Handle.Instance = TIM3;  
  Encoder_Handle.Init.Period             = 65535;
  Encoder_Handle.Init.Prescaler          = 0;
  Encoder_Handle.Init.ClockDivision      = 0;
  Encoder_Handle.Init.CounterMode        = TIM_COUNTERMODE_UP;
  Encoder_Handle.Init.RepetitionCounter  = 0;
  
  sEncoderConfig.EncoderMode        = TIM_ENCODERMODE_TI1;//SMS:01
  
  sEncoderConfig.IC1Polarity        = TIM_ICPOLARITY_FALLING;   //极性反相(CC1P=1)
  sEncoderConfig.IC1Selection       = TIM_ICSELECTION_DIRECTTI;  
  sEncoderConfig.IC1Prescaler       = TIM_ICPSC_DIV1; 
  sEncoderConfig.IC1Filter          = 0;
  
  sEncoderConfig.IC2Polarity        = TIM_ICPOLARITY_RISING;   
  sEncoderConfig.IC2Selection       = TIM_ICSELECTION_DIRECTTI;  
  sEncoderConfig.IC2Prescaler       = TIM_ICPSC_DIV1; 
  sEncoderConfig.IC2Filter          = 0; 
  
  if(HAL_TIM_Encoder_Init(&Encoder_Handle, &sEncoderConfig) != HAL_OK)
  {
    /* Initialization Error */
    //Error_Handler();
  }
  
  /* Start the encoder interface */
  HAL_TIM_Encoder_Start(&Encoder_Handle, TIM_CHANNEL_1);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
//void BSP_LED_On(uint16_t Led)
//{
//  HAL_GPIO_WritePin(LED_PORT, Led, GPIO_PIN_RESET); 
//}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
//void BSP_LED_Off(uint16_t Led)
//{
//  HAL_GPIO_WritePin(LED_PORT, Led, GPIO_PIN_SET); 
//}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
//void BSP_LED_Toggle(uint16_t Led)
//{
//  HAL_GPIO_TogglePin(LED_PORT, Led);
//}

/**
  * @brief  Initialize KEY_LED & Wheel
  * @param  None
  * @retval None
  */
void BSP_KEY_LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/* Enable the GPIO Clock */
    KEYLED_DATx_GPIO_CLK_ENABLE();
	KEYLED_CTL_GPIO_CLK_ENABLE();
	KEYLED_CTL_LCH_GPIO_CLK_ENABLE();
	KEYWHEEL_GPIO_CLK_ENABLE();
    KEY_GPIO_CLK_ENABLE();

  /* Configure the GPIO_DAT pin */
    GPIO_InitStruct.Pin = KEYLED_DAT0_PIN | KEYLED_DAT1_PIN | KEYLED_DAT2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(KEYLED_DATx_PORT, &GPIO_InitStruct);
	
	/* Configure the GPIO_CTL pin */
    GPIO_InitStruct.Pin = KEYLED_CLK_PIN | KEYLED_DAT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(KEYLED_CTL_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = KEYLED_LCH_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(KEYLED_CTL_LCH_PORT, &GPIO_InitStruct);
	
	KL_CLK_L;
	KL_LCH_L;
	KL_DAT_L;
  
	/* Configure the WHEELKEY_PIN*/
    GPIO_InitStruct.Pin = WHEELKEY_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(WHEELKEY_PORT, &GPIO_InitStruct);
	/* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(WHEELKEY_INT_EXTI), WHEELKEY_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(WHEELKEY_INT_EXTI));
    
    /* Configure the KEY_S1_PIN*/
    GPIO_InitStruct.Pin = KEY_S1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);
	/* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(KEY_S1_EXTI), KEY_S1_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(KEY_S1_EXTI));
    
    /* Configure the KEY_S2_PIN*/
    GPIO_InitStruct.Pin = KEY_S2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);
	/* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(KEY_S2_EXTI), KEY_S2_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(KEY_S2_EXTI));
    
    /* Configure the KEY_S3_PIN*/
    GPIO_InitStruct.Pin = KEY_S3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);
	/* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(KEY_S3_EXTI), KEY_S3_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(KEY_S3_EXTI));
    
    /* Configure the KEY_S4_PIN*/
    GPIO_InitStruct.Pin = KEY_S4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);
	/* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(KEY_S4_EXTI), KEY_S4_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(KEY_S4_EXTI));
    
	//Init
	KeyLed_State.led = 0;
	KeyLed_State.key = 0;
	KeyLed_State.wheel = 0;
    KeyLed_State.rotate = 0;
	//TIM_Encoder_Init();
	
}

/**
  * @brief  Read KEY & wheel, set led
  * @param  None
  * @retval None
  */
void BSP_Update_KEY_LED(void)
{
	//uint32_t buf_key = 0;
	uint32_t cnt_delay = 10;	//9014 - 至少50, 2N7002 - 至少为5
	uint8_t i;
	//uint8_t temp;
	
	// Init state
	KL_CLK_L;
	KL_LCH_L;
	CLK_Delay(cnt_delay);
	
	//push led data
	for(i=8;i>0;i--)
	{
		if((KeyLed_State.led & (1<<(i-1))) != 0)	KL_DAT_H;
		else										KL_DAT_L;
		CLK_Delay(cnt_delay);
		KL_CLK_H;
		CLK_Delay(cnt_delay);
		KL_CLK_L;
	}
	
	//update led state 发送锁存信号
	KL_LCH_H;
	CLK_Delay(cnt_delay);
	KL_LCH_L;
}

/**
  * @brief  update wheel value
  * @param  None
  * @retval None
  */
void BSP_Update_Wheel(void)
{
		static int32_t wheelval = 0;	
    int32_t cnt = (TIM3->CNT)/2;
    if(wheelval < cnt)
    {
        KeyLed_State.rotate = 1;//旋转方向1：顺时针，2：逆时针
        wheelval = cnt;
    }
    else if(wheelval > cnt)
    {
        KeyLed_State.rotate = 2;
        wheelval = cnt;
    }
    else
    {
        KeyLed_State.rotate = 0;
    }
   
}

/**
  * @brief  BSP_GetKEY_State
  * @param  key
  * @retval None
  */
uint8_t BSP_GetKEY_State(uint8_t key)
{
	if((KeyLed_State.key & (1<<key)) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief  TIM1_Encoder_Write
  * @param  cnt
  * @retval None
  */
void Wheel_Encoder_Write(int32_t cnt)
{
	TIM3->CNT = cnt;
}

/**
  * @brief  TIM1_Encoder_Read
  * @param  void
  * @retval 
  */
int16_t Wheel_Encoder_Read(void)
{
    int16_t cnt = 0;
    cnt = TIM3->CNT;
	return cnt/2;
}

/**
  * @brief  编码器数值清零
  * @param  cnt
  * @retval None
  */
void  Wheel_Encoder_Clear(void)
{
    Wheel_Encoder_Write(0);
}

