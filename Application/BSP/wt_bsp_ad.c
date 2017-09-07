/**
  ******************************************************************************
  * @progect LZY Wire Cube Tester
	* @file    wt_bsp_ad.c
  * @author  LZY Zhang Manxin
  * @version V1.0.0
  * @date    2014-07-18
  * @brief   This file provides the E2PROM functions
  ******************************************************************************
  */

#define WT_BSP_AD_GLOBALS

/* Includes ------------------------------------------------------------------*/
#include "wt_bsp_ad.h"


uint32_t debug_view;
extern uint8_t ack1_flag;
extern uint8_t ack2_flag;
extern uint8_t ack3_flag;
extern uint8_t ack4_flag;

/**
  * @brief  Configures AD IO GPIO.
  * @param  None
  * @retval None
  */
static void BSP_AD_IO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable the GPIO Clock */
    //AD_SOURSE_GPIO_CLK_ENABLE();
    AD_CTL_GPIO_CLK_ENABLE();
    AD_SIGNAL_GPIO_CLK_ENABLE();

    PS_MISO_ACK_GPIO_CLK_ENABLE();
    PS_MOSIRST_GPIO_CLK_ENABLE();
    PS_MOSI_INC_OUT_GPIO_CLK_ENABLE();
    PS_MOSI_INC_IN_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;


    /* Configure the AD_SIGNAL pin */
    GPIO_InitStruct.Pin = AD_LOGIC_COMPARE1_PIN | AD_LOGIC_COMPARE2_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(AD_SIGNAL_PORT, &GPIO_InitStruct);


    /* Configure the MOSI：板卡接收，主板发送*/
    GPIO_InitStruct.Pin = PS_MOSI_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MOSI_RST_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = PS_MOSI_INC_OUT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MOSI_INC_OUT_PORT, &GPIO_InitStruct);
    PS_MOSI_INC_OUT_H;
    
    GPIO_InitStruct.Pin = PS_MOSI_INC_IN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MOSI_INC_IN_PORT, &GPIO_InitStruct);
    PS_MOSI_INC_IN_H;
    
    /* Configure the MISO：板卡发送，主板接收*/
    GPIO_InitStruct.Pin = PS_MISO_ACK1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MISO_ACK_PORT, &GPIO_InitStruct);
    /* Enable and set GPIO EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(MISO_ACK1_EXTI), MISO_ACK1_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(MISO_ACK1_EXTI));
    
    GPIO_InitStruct.Pin = PS_MISO_ACK2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MISO_ACK_PORT, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority((IRQn_Type)(MISO_ACK2_EXTI), MISO_ACK2_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(MISO_ACK2_EXTI));
    
    GPIO_InitStruct.Pin = PS_MISO_ACK3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MISO_ACK_PORT, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority((IRQn_Type)(MISO_ACK3_EXTI), MISO_ACK3_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(MISO_ACK3_EXTI));
    
    GPIO_InitStruct.Pin = PS_MISO_ACK4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(PS_MISO_ACK_PORT, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority((IRQn_Type)(MISO_ACK4_EXTI), MISO_ACK4_INT_PREPRIO, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(MISO_ACK4_EXTI));

    //BSP_AD_ChangeMode(0);	//0-Normal Mode, 1-FindPoint Mode;
}



static void BSP_DA_Converter_Init(void)
{
    DAC_ChannelConfTypeDef sConfig;

    /*##-1- Configure the DAC peripheral #######################################*/
    DacHandle.Instance          = DAC_OUT;
      
    if(HAL_DAC_Init(&DacHandle) != HAL_OK)
    {
    /* Initiliazation Error */
    //Error_Handler(); 
    }
	
	/*##-2- Configure DAC regular channel ######################################*/  
    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;  
  
    if(HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_OUT1_CHANNEL) != HAL_OK)
    {
        /* Channel configuration Error */
        //Error_Handler();
    }
    
    if(HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_OUT2_CHANNEL) != HAL_OK)
    {
        /* Channel configuration Error */
        //Error_Handler();
    }
    //DAC_OUT_1  = 0.95v   DA = (0.95/3.3)*4095 = 1179  == 0x4A5
    //DAC_OUT_1  = 0.132v   DA = (0.132/3.3)*4095 = 164  == 0x0A4
    if(HAL_DAC_SetValue(&DacHandle, DAC_OUT1_CHANNEL, DAC_ALIGN_12B_R, 0x0A4) != HAL_OK)
    {
    /* Setting value Error */
    //Error_Handler();
    }
    //DAC_OUT_2  = 2.363v   DA = (2.363/3.3)*4095 = 2932  == 0xB74    2.2K 560组合
    //DAC_OUT_2  = 1.791v   DA = (1.791/3.28)*4095 = 2236  == 0x8BC    2.2K 560组合
    if(HAL_DAC_SetValue(&DacHandle, DAC_OUT2_CHANNEL, DAC_ALIGN_12B_R, 0x8BC) != HAL_OK)
    {
    /* Setting value Error */
    //Error_Handler();
    }

    /*##-4- Enable DAC Channel1 ################################################*/ 
    if(HAL_DAC_Start(&DacHandle, DAC_OUT1_CHANNEL) != HAL_OK)
    {
    /* Start Error */
    //Error_Handler();
    }
    if(HAL_DAC_Start(&DacHandle, DAC_OUT2_CHANNEL) != HAL_OK)
    {
    /* Start Error */
    //Error_Handler();
    }
  
}

/**
  * @brief  Configures AD Converter.
  * @param  None
  * @retval None
  */
static void BSP_AD_Converter_Init(void)
{
	ADC_ChannelConfTypeDef sConfig;
	
	/*##-1- Configure the ADC peripheral #######################################*/
  AdcHandle.Instance          = ADCx;
  
  AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;	//30Mhz(TAP), 36MHz(MAX) --- 19.5MHz
  //AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
  AdcHandle.Init.ScanConvMode = DISABLE;
  AdcHandle.Init.ContinuousConvMode = DISABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion = 0;
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.NbrOfConversion = 1;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
  AdcHandle.Init.EOCSelection = DISABLE;
      
  if(HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* Initiliazation Error */
    //Error_Handler(); 
  }
	
	/*##-2- Configure ADC regular channel ######################################*/  
  sConfig.Channel = ADCx_CHANNEL;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  sConfig.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    //Error_Handler(); 
  }

}


/**
  * @brief  Configures AD GPIO.
  * @param  None
  * @retval None
  */
void BSP_DA_Init(void)
{
//    uint8_t buf8;
//    uint32_t buf32;

    //BSP_DA_IO_Init();
    BSP_DA_Converter_Init();
        
}


/**
  * @brief  Configures AD GPIO.
  * @param  None
  * @retval None
  */
void BSP_AD_Init(void)
{
    uint8_t buf8 = 0;
 
    BSP_AD_IO_Init();
    BSP_AD_Converter_Init();
        
    // Init
    //发送板卡复位信号，通过查询ACK信号，获得板卡连接数量信息
    PS_MOSI_RST_L;
    CLK_Delay(168/6);	//1us == 168/3	
    PS_MOSI_RST_H;
    CLK_Delay(168/6);
    
    if(ack1_flag == 1)
    {
        buf8 |= 1<<0;
        ack1_flag = 0;
    }
    if(ack2_flag == 1)
    {
        buf8 |= 1<<1;
        ack2_flag = 0;
    }
    if(ack3_flag == 1)
    {
        buf8 |= 1<<2;
        ack3_flag = 0;
    }
    if(ack4_flag == 1)
    {
        buf8 |= 1<<3;
        ack4_flag = 0;
    }

    //AD_State.PortBoard_Connected = (~buf8) & 0x0F;
    AD_State.PortBoard_Connected = (buf8) & 0x0F;
    AD_State.ChannelAB_Addr_State = AD_ChannelAddr_NULL;
    AD_State.ChannelCD_Addr_State = AD_ChannelAddr_NULL;
    AD_State.SourceA_Addr = AD_SourceAddr_GNDR;
    AD_State.SourceC_Addr = AD_SourceAddr_GNDR;
    AD_State.Channel_Addr_Error = 0;

    //Update Init Value
    //PortBoard_Update_ChannelAddr(AD_State.ChannelAB_Addr_State, AD_State.ChannelCD_Addr_State);
    //AD_Update_SourceAddr(AD_SourceAddr_GNDR, AD_SourceAddr_GNDR);
    //PortBoard_Read_BoardInfo(&buf32);
    //PortBoard_Read_ChannelSetting(&buf32);
}


/**
  * @brief  Get AD Value For AD Buffer
  * @param  AD Buffer
  * @retval AD Value
  * 对缓冲区数据升序排列,
  * 然后去掉最低和最高LOST_VAL个数,取平均值
  */
#define LOST_VAL 5	  //丢弃参数，共丢弃5*2=10个

uint16_t AD_GetValue_FromBuffer(uint16_t* pData, uint32_t Length)
{
	uint16_t i, j;
	uint16_t sum=0;
	uint16_t temp;
		    
	for(i=0;i<Length-1; i++)//排序
	{
		for(j=i+1;j<Length;j++)
		{
			if(pData[i]>pData[j])//升序排列
			{
				temp=pData[i];
				pData[i]=pData[j];
				pData[j]=temp;
			}
		}
	}
	
	sum=0;
	for(i=LOST_VAL;i<Length-LOST_VAL;i++) sum+=pData[i];
	temp=sum/(Length-2*LOST_VAL);
	return temp;  
}

/**
  * @brief  Get AD Value For AD Buffer
  * @param  AD Buffer
  * @retval AD Value
  * 对缓冲区数据升序排列,
  * 然后去掉最低和最高LOST_VAL个数,取平均值
  */
#define LOST_VAL_Voltage 100	  //丢弃参数，共丢弃200个

uint16_t Voltage_GetValue_FromBuffer(uint16_t* pData, uint32_t Length)
{
	uint16_t i, j;
	uint32_t sum=0;
	uint16_t temp;
		    
	for(i=0;i<Length-1; i++)//排序
	{
		for(j=i+1;j<Length;j++)
		{
			if(pData[i]>pData[j])//升序排列
			{
				temp=pData[i];
				pData[i]=pData[j];
				pData[j]=temp;
			}
		}
	}
	
	sum=0;
	for(i=LOST_VAL;i<Length-LOST_VAL;i++) sum+=pData[i];
	temp=sum/(Length-2*LOST_VAL);
	return temp;  
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and 
  *         you can add your own implementation.    
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle_0)
{
	AD_IsConvertFinished = 1;	//1-finished, 0-waiting
	//HAL_ADC_Stop_DMA(AdcHandle_0);
}

/**
  * @brief  Configures AD GPIO.
  * @param  None
	* @retval 0:ok, 1:error
  */
uint8_t AD_WaitFinishConvert(uint32_t cnt)
{
	while(cnt--)
	{
		if(AD_IsConvertFinished == 1) return 0; //1-finished, 0-waiting
	}
	HAL_ADC_Stop_DMA(&AdcHandle);
	return 1;
}



/**
  * @brief  Configures AD GPIO.
  * @param  None
	* @retval 0:ok, 1:error
  */
uint8_t AD_ReadValue(uint32_t cnt, uint16_t * buf16)
{
	uint8_t res;
	uint32_t i;
	
	AD_IsConvertFinished = 0;	//1-finished, 0-waiting
	for(i=0;i<ADC_Bufer_Length;i++) BufADC_Value[i]=0;	//reset buffer
	//HAL_ADC_Start_DMA(&AdcHandle, (uint32_t *)BufADC_Value, ADC_Bufer_Length);	//satart converter
    HAL_ADC_Start_IT(&AdcHandle);

	res = AD_WaitFinishConvert(100*1000);	//timeout 1ms
	if(res != 0) 
    {
        return 1;
    }
	//*buf16 = AD_GetValue_FromBuffer(BufADC_Value, ADC_Bufer_Length);
    *buf16 = HAL_ADC_GetValue(&AdcHandle);
	return 0;
}

/**
  * @brief  冒泡法排序
  * @param  None
	* @retval 
  */
void bubble(uint16_t *a,int n) 
{ 
	int i,j,temp; 

	for(i=0;i<n-1;i++)
	{	
		for(j=i+1;j<n;j++)
		{
			if(a[i]>a[j]) 
			{ 
				temp=a[i]; 
				a[i]=a[j]; 
				a[j]=temp; 
			} 
		}
	}
} 

/**
  * @brief  compute AD value.
  * @param  None
	* @retval 0:ok, 1:error
	* 连续读取AD值20次，取20个值的平均值
  */
uint8_t GetADValue( uint16_t * buf16 )
{
	uint8_t i = 0;
	uint8_t res;
	uint16_t readval;
	uint16_t adval[20];
	uint32_t sum = 0;
	
	for(i=0 ; i< 20;i++)
	{
		res = AD_ReadValue(10*1000,&readval);
		if(res != 0) return 1;
		adval[i] = readval;
	}
	
	//排序
	//bubble(adval,20);
	
	for(i=0;i<20;i++)
	{
		sum += adval[i];
	}
	
	*buf16 = sum /20;
	return 0;
}

/**
  * @brief  根据AD值计算电阻值
  * @param  adval:AD值   resval:电阻值
  * @retval 0:ok, 1:error
  */
uint8_t GetResValue( uint16_t adval, uint32_t * resval )
{
    if( adval >= 1700)// < 500
    {
        * resval = 300;
    }
    else if(adval >= 1550 && adval < 1700)
    {
        * resval = 400;
    }
    else if(adval >= 1400 && adval < 1550)
    {
        * resval = 500;
    }
    else if(adval >= 1350 && adval < 1400)
    {
        * resval = 600;
    }
    else if(adval >= 1250 && adval < 1350)
    {
        * resval = 700;
    }
    else if(adval >= 1150 && adval < 1250)
    {
        * resval = 800;
    }
    else if(adval >= 1100 && adval < 1150)
    {
        * resval = 900;
    }
    else if(adval >= 1000 && adval < 1100)
    {
        * resval = 1000;
    }
    else if(adval >= 600 && adval < 1000)
    {
        * resval = 2000;
    }
    else if(adval >= 500 && adval < 600)
    {
        * resval = 3000;
    }
    else if(adval >= 400 && adval < 500)
    {
        * resval = 4000;
    }
    else if(adval >= 330 && adval < 400)
    {
        * resval = 5000;
    }
    else if(adval >= 290 && adval < 330)
    {
        * resval = 6000;
    }
    else if(adval >= 260 && adval < 290)
    {
        * resval = 7000;
    }
    else if(adval >= 230 && adval < 260)
    {
        * resval = 8000;
    }
    else if(adval >= 220 && adval < 230)
    {
        * resval = 9000;
    }
    else if(adval >= 200 && adval < 220)
    {
        * resval = 10000;
    }
    else
    {
        * resval = 11000;
    }
	

	return 0;
}

/**
  * @brief  设置参考电压值
  * @param  cmp1:低电压参考值   cmp2:高电压参考值
  * @retval 0:ok, 1:error
  */
uint8_t SetCmpVoltage(uint16_t cmp1,uint16_t cmp2)
{
    if(HAL_DAC_SetValue(&DacHandle, DAC_OUT1_CHANNEL, DAC_ALIGN_12B_R, cmp1) != HAL_OK)
    {
        return 1;
    }
    //DAC_OUT_2  = 2.363v   DA = (2.363/3.3)*4095 = 2932  == 0xB74    2.2K 560组合
    //DAC_OUT_2  = 2.544v   DA = (2.544/3.3)*4095 = 3175  == 0xC55    2K 360组合
    if(HAL_DAC_SetValue(&DacHandle, DAC_OUT2_CHANNEL, DAC_ALIGN_12B_R, cmp2) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}
