/********************************************************************************
	Copyright (C), 2016-2026, Suzhou LZY Tech. Co., Ltd.
  File name:      wt_uart_audio.c
  Author: wujun      Version:  2.0      Date: 2016.7.28
  Description:    WT-8A46 main function
                  
  Others:          

	Function List:  
    1. ....
  History:        
    1. Date:
       Author:
       Modification:
    2. ...

******************************************************************************/

/* Define ------------------------------------------------------------------*/
#define  WT_UART_Audio_GLOBALS


/* Includes ------------------------------------------------------------------*/
#include "k_bsp.h"
#include "main.h"

//#include "wt_bsp_key_led.h"
//#include "wt_bsp_file.h"
//#include "k_rtc.h"
//#include "wt_task_wireselfcheck.h"


/* Private functions ---------------------------------------------------------*/
static void WT_UART_Audio_Rx_IT(uint8_t dat);
static void UART_Audio_Buffer_RxClear(void);
static void UartAudio_RX_Process(void);
static uint8_t UartAudio_SetVolume(uint8_t Volume);
void UartAudio_SendCommand(uint8_t mode);

static uint8_t audio_received = 0;	//audio_received |= (1<<6);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																		//bit4-return error, bit5-Command ack, bit6-others return,
																		//bit7-not use,



/**
  * @brief  Audio Play task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
void UARTAudioThread(void const * argument)
{
	osEvent event;
	
	WT_UART_Audio_Init();	//Init
	UART_Audio_Buffer_RxClear();
	
  for( ;; )
  {
    event = osMessageGet(UartAudioEvent, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      switch(event.value.v)
      {
				case UartAudio_RX_Event:
					UartAudio_RX_Process();
					break;
				
				case UartAudioOK_TX_Event:
					UartAudio_SendCommand(WT_Config.AudioOK);
					break;
				case UartAudioNG_TX_Event:
					UartAudio_SendCommand(WT_Config.AudioNG);
					break;
				case UartAudio_FindPoint_Event:
					UartAudio_SendCommand(0);
					break;
				case UartAudio_VOLUME_Event:
					UartAudio_SetVolume(WT_Config.AudioVolume);
					break;
				case UartAudioSTOP_TX_Event:
					UartAudio_SendCommand(100);
					break;
				case UartAudioOK_REPEAT_TX_Event:
					UartAudio_SendCommand(WT_Config.AudioOK+8);
					break;
				
				default:
					break;
      }
    }
		else	//error
		{
			osDelay(1000);
		}
  }
}

///**
//  * @brief  Configures Audio Power control GPIO.
//  * @param  None
//  * @retval None
//  */
//void BSP_UartAudio_Power_Init(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStruct;
//  
//	/* Enable the GPIO_LED Clock */
//  PowerSW_GPIO_CLK_ENABLE();

//  /* Configure the PowerSW_Audio pin */
//  GPIO_InitStruct.Pin = PowerSW_Audio_PIN;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
//  HAL_GPIO_Init(PowerSW_PORT, &GPIO_InitStruct);
//	
//	BSP_UartAudio_PowerOFF();
//}


/**
  * @brief  WT_UART_Audio_Init
  * @param  None
  * @retval None
  */
void WT_UART_Audio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	uint32_t i;
	
	for(i=0;i<UART_Audio_RX_Bufer_Length;i++) UART_Audio_Buffer_Rx[i]=0;
	UART_Audio_Cnt_Buffer_Rx = 0;
//	Is_UART_Audio_Rx_Come = 0;
	
	/* USART configuration */
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 19200 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle_Audio.Instance        = UART_AUDIO;
  UartHandle_Audio.Init.BaudRate   = 9600;
  UartHandle_Audio.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle_Audio.Init.StopBits   = UART_STOPBITS_1;
  UartHandle_Audio.Init.Parity     = UART_PARITY_NONE;
  UartHandle_Audio.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle_Audio.Init.Mode       = UART_MODE_TX_RX;
  HAL_UART_Init(&UartHandle_Audio);
	
	/* Enable the GPIO_LED Clock */
  PowerSW_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
	BSP_UartAudio_PowerOFF();
  GPIO_InitStruct.Pin = PowerSW_Audio_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(PowerSW_PORT, &GPIO_InitStruct);

	ModuleAudio.Card = 1;
	ModuleAudio.Power = 1;
	ModuleAudio.State = 0;
	ModuleAudio.TotalFile = 2999;
	BSP_UartAudio_PowerON();
	osDelay(2000);
	//UartAudio_SetVolume(6);
	UartAudio_SetVolume(WT_Config.AudioVolume);
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  huart: UART handle
  * @retval None
  */
void WT_UART_Audio_IRQHandler(UART_HandleTypeDef *huart)
{
  uint32_t tmp1 = 0, tmp2 = 0;

  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_PE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_PE);  
  /* UART parity error interrupt occurred ------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE);
    
    huart->ErrorCode |= HAL_UART_ERROR_PE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_FE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR);
  /* UART frame error interrupt occurred -------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
    
    huart->ErrorCode |= HAL_UART_ERROR_FE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_NE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR);
  /* UART noise error interrupt occurred -------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);
    
    huart->ErrorCode |= HAL_UART_ERROR_NE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_ORE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR);
  /* UART Over-Run interrupt occurred ----------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);
    
    huart->ErrorCode |= HAL_UART_ERROR_ORE;
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE);
  /* UART in mode Receiver ---------------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  { 
    //UART_Receive_IT(huart);
		WT_UART_Audio_Rx_IT((uint8_t)(huart->Instance->DR & (uint8_t)0x00FF));	//cndz, 20140723
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
  }
  
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_TC);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_TC);
  /* UART in mode Transmitter ------------------------------------------------*/
  if((tmp1 != RESET) && (tmp2 != RESET))
  {
    //UART_Transmit_IT(huart);
  }
  
  if(huart->ErrorCode != HAL_UART_ERROR_NONE)
  {
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
    
    HAL_UART_ErrorCallback(huart);
  }  
}

/**
  * @brief  UART_Audio_Buffer_RxClear
  * @param  None
  * @retval None
  */
static void UART_Audio_Buffer_RxClear(void)
{
	uint32_t i;
	
	for(i=0;i<UART_Audio_RX_Bufer_Length;i++) UART_Audio_Buffer_Rx[i]=0;
	UART_Audio_Cnt_Buffer_Rx = 0;
//	Is_UART_Audio_Rx_Come = 0;
}

/**
  * @brief  WT_UART_Audio_Rx
  * @param  uint8_t dat
  * @retval None
  */
uint8_t WT_UART_Audio_WrBuf(uint8_t* pData, uint8_t length)
{
	while(length--)
	{
		if(UART_WaitOnFlagUntilTimeout(&UartHandle_Audio, UART_FLAG_TXE, RESET, 100) != HAL_OK)
		{
			return 1;
		}
		UartHandle_Audio.Instance->DR = (*pData++ & (uint8_t)0xFF);
	}
	
	if(UART_WaitOnFlagUntilTimeout(&UartHandle_Audio, UART_FLAG_TXE, RESET, 100) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}

/**************************************************/
/*** Aplication ***********************************/
/**************************************************/

/**
  * @brief  WT_UART_Audio_Rx_IT
  * @param  uint8_t dat
  * @retval None
  */
static void WT_UART_Audio_Rx_IT(uint8_t dat)
{
//	uint8_t buf8;
	
	/* receiver data */
	UART_Audio_Buffer_Rx[UART_Audio_Cnt_Buffer_Rx] = dat;
	if(UART_Audio_Cnt_Buffer_Rx < (UART_Audio_RX_Bufer_Length-2)) UART_Audio_Cnt_Buffer_Rx++;
	
	//检测开始标志
	if(UART_Audio_Cnt_Buffer_Rx == 1)
	{
		//0x7E, $S
		if(UART_Audio_Buffer_Rx[0] != 0x7E) 
		{
			UART_Audio_Buffer_RxClear();
			return;
		}
	}
	else if(UART_Audio_Cnt_Buffer_Rx <= 3)
	{
		//Byte[1] -	版本
		//Byte[2]	-	长度

		if(UART_Audio_Cnt_Buffer_Rx == 3)
		{
			if(UART_Audio_Buffer_Rx[2] != 6) //长度错误
			{
				UART_Audio_Buffer_RxClear();
				return;
			}
		}
	}
	else //wait frame end
	{
		if(UART_Audio_Cnt_Buffer_Rx >= (UART_Audio_Buffer_Rx[2]+1+3))	// Head + Command
		{
			if(UART_Audio_Buffer_Rx[UART_Audio_Cnt_Buffer_Rx-1] != 0xEF) // end, $0
			{
				UART_Audio_Buffer_RxClear();
				return;
			}
			else
			{
				//osMessagePut(UartAudioEvent, UartAudio_RX_Event, 0);	//播放声音
				UartAudio_RX_Process();
			}
		}
	}
}

/******************************************************************************
- 功能描述：求和校验
- 和校验的思路如下：
发送的指令，去掉起始和结束。将中间的6 个字节进行累加，最后取反码。接收端就将
接收到的一帧数据，去掉起始和结束。将中间的数据累加，再加上接收到的校验字节。刚好
为0.这样就代表接收到的数据完全正确。
******************************************************************************/
uint16_t ModuleAudio_DoSum(uint8_t *Str, uint8_t len)
{
	uint16_t xorsum = 0;
	uint8_t i;

	for(i=0; i<len; i++)
	{
		xorsum = xorsum + Str[i];
	}
	xorsum = 0 -xorsum;
	return xorsum;
}


/**
  * @brief  UartAudio_SelectMedia
  * @param  2:SD card, others:sleep,
  * @retval 0-ok, 1-module error,
  */
static uint8_t UartAudio_SelectMedia(uint8_t media)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];

	// media select
	if(media != 2) media = 6;
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x09; //命令字节-指定播放设备
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = 0x00;	//
	TxBuffer[j++] = media;	//media
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			osDelay(5);
		}
	}
	return 1;
}

/**
  * @brief  UartAudio_SetVolume
  * @param  Volume:0-10
  * @retval 0-ok, 1-module error,
  */
static uint8_t UartAudio_SetVolume(uint8_t Volume)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];

	// media select
	if(Volume >= 10) Volume = 10;
	Volume = Volume *3;
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x06; //命令字节-指定音量
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = 0x00;	//
	TxBuffer[j++] = Volume;	//media
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			osDelay(5);
		}
	}
	return 1;
}


/**
  * @brief  UartAudio_PlayBy_ID
  * @param  None
  * @retval 0-ok, 1-MP3 ID or module error,
  */
static uint8_t UartAudio_PlayBy_ID(uint16_t id_mp3)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];
	
	// check mp3 ID
	if(id_mp3 > ModuleAudio.TotalFile) return 1;
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x03; //命令字节-指定歌曲播放指令
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = (id_mp3>>8)&0xFF;	//Para_H
	TxBuffer[j++] = (id_mp3>>0)&0xFF;	//Para_L
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			osDelay(5);
		}
	}
	return 1;
}

/**
  * @brief  UartAudio_RepeatSingle
  * @param  None
  * @retval 0-ok, 1-MP3 ID or module error,
  */
static uint8_t UartAudio_RepeatSingle(uint16_t id_mp3)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];
	
	// check mp3 ID
	if(id_mp3 > ModuleAudio.TotalFile) return 1;
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x08; //命令字节-单曲重复
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = (id_mp3>>8)&0xFF;	//Para_H
	TxBuffer[j++] = (id_mp3>>0)&0xFF;	//Para_L
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			osDelay(5);
		}
	}
	return 1;
}

/**
  * @brief  UartAudio_PlayBy_Folder
  * @param  None
  * @retval 0-ok, 1-module error,2-forder or mp3 id error,
  */
static uint8_t UartAudio_PlayBy_Folder(uint8_t folder, uint8_t id_mp3)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];
	
	// check folder number
	if(folder > ModuleAudio.TotalFile) return 1;
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x0F; //命令字节-指定文件夹播放指令
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = folder;	//folder
	TxBuffer[j++] = id_mp3;	//id
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			if((audio_received & (1<<4)) != 0) {return 2;}	//forder error
			osDelay(5);
		}
	}
	return 1;
}

/**
  * @brief  UartAudio_PlayBy_Folder_MP3
  * @param  None
  * @retval 0-ok, 1-module error,2-mp3 id error,
  */
static uint8_t UartAudio_PlayBy_Folder_MP3(uint16_t id_mp3)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];
	
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x12; //命令字节-指定歌曲播放指令
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = (id_mp3>>8)&0xFF;	//Para_H
	TxBuffer[j++] = (id_mp3>>0)&0xFF;	//Para_L
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			if((audio_received & (1<<4)) != 0) {return 2;}	//forder error
			osDelay(5);
		}
	}
	return 1;
}

/**
  * @brief  UartAudio_Stop
  * @param  None
  * @retval 0-ok, 1-module error,
  */
static uint8_t UartAudio_Stop(void)
{
	uint16_t i;
	uint8_t j=0;
	uint8_t  TxBuffer[10];
	
	//Send to Audio module
	/**********************************************************/
	TxBuffer[j++] = 0x7E;	//起始命令
	TxBuffer[j++] = 0xFF; //版本信息
	TxBuffer[j++] = 0x06; //数据长度
	//---------------------------------------------------------
	TxBuffer[j++] = 0x16; //命令字节-停止播放
	TxBuffer[j++] = 0x01;	//0:不应答，1：应答；
	TxBuffer[j++] = 0x00;	//
	TxBuffer[j++] = 0x00;	//
	/******求和校验 *********************************************/
	i = ModuleAudio_DoSum(&TxBuffer[1], TxBuffer[2]); //求和校验
	TxBuffer[j++] = (i>>8)&0xFF; 	//校验高字节
	TxBuffer[j++] = i&0xFF; 			//校验低字节
  TxBuffer[j++] = 0xEF; //结束命令
	/****** Send ************************************************/
	for(j=0;j<3;j++)	//Up to three attempts to send
	{
		audio_received = 0;	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
		WT_UART_Audio_WrBuf(TxBuffer, TxBuffer[2]+4);
		for(i=0;i<20;i++)
		{
			if((audio_received & (1<<5)) != 0) {return 0;}	//ack
			osDelay(5);
		}
	}
	return 1;
}

/**
  * @brief  UartAudio_RX_Process
  * @param  None
  * @retval None
  */
static void UartAudio_RX_Process(void)
{
	//Check CRC-16
	
	//Process
	switch(UART_Audio_Buffer_Rx[3])
	{
		case 0x3A:	//设备插入消息
			audio_received |= (1<<0);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;
		
		case 0x3B:	//设备拔出消息
			audio_received |= (1<<1);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;
		
		case 0x3D:	//TF卡播放结束
			audio_received |= (1<<2);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;
		
		case 0x3F:	//模块上电返回数据
			audio_received |= (1<<3);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;
		
		case 0x40:	//模块错误返回数据
			audio_received |= (1<<4);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;
		
		case 0x41:	//收到命令应答
			audio_received |= (1<<5);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;

		default:
			audio_received |= (1<<6);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, 
																//bit4-return error, bit5-Command ack, bit6-others return,
																//bit7-not use,
			break;
	}
	
	// clear rx buffer
	UART_Audio_Buffer_RxClear();
}


/**
  * @brief  UartAudio_SendCommand
	* @param  0-3:OK Audio   4-7:NG Audio  8-11 OK Audio Repeat
  * @retval None
  */
void UartAudio_SendCommand(uint8_t mode)
{
	uint8_t buf8;
	uint8_t i;
	
	switch(mode)
	{
		case 0:	//test OK
			UartAudio_PlayBy_ID(1);
			break;
		
		case 1:	//test OK
			UartAudio_PlayBy_ID(2);
			break;
		
		case 2:	//test OK
			UartAudio_PlayBy_ID(3);
			break;
		
		case 3:	//test OK
			UartAudio_PlayBy_ID(4);
			break;
		
		case 4:	//test NG
			UartAudio_RepeatSingle(5);
			break;
		
		case 5:	//test NG
			UartAudio_RepeatSingle(6);
			break;
		
		case 6:	//test NG
			UartAudio_RepeatSingle(7);
			break;
		case 7:	//test NG
			UartAudio_RepeatSingle(8);
			break;
		case 8:	//test OK repeat
			UartAudio_RepeatSingle(1);
			break;
		case 9:	//test OK repeat
			UartAudio_RepeatSingle(2);
			break;
		case 10:	//test OK repeat
			UartAudio_RepeatSingle(3);
			break;
		case 11:	//test OK repeat
			UartAudio_RepeatSingle(4);
			break;
		case 12:	//
			UartAudio_PlayBy_Folder_MP3(1);
			break;
		case 13:	//
			UartAudio_RepeatSingle(11);
			break;
		case 14:	//
			UartAudio_PlayBy_Folder(1,1);
			break;
		case 15:	//
			UartAudio_SelectMedia(1);
			break;
		case 100:
			for(i=0;i<3;i++)
			{
				buf8 = UartAudio_Stop();
				//if(buf8 == 0) break;
				//osDelay(100);
			}		
			break;
		case 200:	//
			audio_received |= (1<<6);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
			UartAudio_PlayBy_ID(1);
			buf8=100; while((audio_received & (1<<2)) == 0) {osDelay(10); if(buf8-- == 0) break;}
			
			audio_received |= (1<<6);	//bit0-Insert, bit1-Pull Out, bit2-End Play, bit3-Power On, bit4-return error, bit5-Command ack, bit6-others return, bit7-not use;
			UartAudio_PlayBy_ID(2);
			buf8=100; while((audio_received & (1<<2)) == 0) {osDelay(10); if(buf8-- == 0) break;}
			break;		
		
		default:
			
			for(i=0;i<3;i++)
			{
				buf8 = UartAudio_Stop();
				if(buf8 == 0) break;
			}		
			break;
	}
}
